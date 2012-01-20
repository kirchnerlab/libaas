/*
 * Residue-test.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Residue.hpp>
#include <libaas/Error.hpp>

#include "vigra/unittest.hxx"

#include <iostream>

using namespace libaas;
using namespace libaas::aminoAcids;
using namespace libaas::modifications;

/** Short description.
 * Long description.
 */
struct ResidueTestSuite : vigra::test_suite
{
    /** Constructor.
     * The ResidueTestSuite constructor adds all Residue tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    ResidueTestSuite() :
            vigra::test_suite("Residue")
    {
        add(testCase(&ResidueTestSuite::testResidue));
        add(testCase(&ResidueTestSuite::testResidueStoichiometry));
    }

    void testResidue()
    {

        RawAminoAcidImpl::RawAminoAcidImplKeyType aa_k = 'A';
        AminoAcid aa(aa_k);
        RawModificationImpl::RawModificationImplKeyType m_k = "Phospho";
        RawModificationImpl::RawModificationImplKeyType l_k = "ESP";
        Modification m(m_k);
        Modification l(l_k);

        Residue r(aa);

        shouldEqual(r.isCTerm(), false);
        shouldEqual(r.isNTerm(), false);
        shouldEqual(r.isModified(), false);
        shouldEqual(r.isLabeled(), false);

        r.changeType(aa);
        shouldEqual(r.getAminoAcid(), aa);

        r.changeType(aa_k);
        shouldEqual(r.getAminoAcid(), aa);

        libaas::Bool thrown = false;
        try {
            r.setModification(l);
        } catch (libaas::errors::LogicError& e) {
            thrown = true;
        }shouldEqual(thrown, true);

        r.setModification(m);
        shouldEqual(r.getModification(), m);
        shouldEqual(r.isModified(), true);
        shouldEqual(r.hasModification(m), true);
        shouldEqual(r.hasModification(Modification("Oxidation")), false);

        thrown = false;
        try {
            r.setIsotopicLabel(m);
        } catch (libaas::errors::LogicError& e) {
            thrown = true;
        }shouldEqual(thrown, true);

        r.setIsotopicLabel(l);
        shouldEqual(r.getIsotopicLabel(), l);
        shouldEqual(r.isLabeled(), true);
        shouldEqual(r.hasLabel(l), true);
        shouldEqual(r.hasLabel(l.getModificationId()), true);
        shouldEqual(r.hasLabel(Modification("Oxidation")), false);

        r.setIsotopicLabel(l.getModificationId());
        shouldEqual(r.getIsotopicLabel(), l);
        shouldEqual(r.isLabeled(), true);
        shouldEqual(r.hasLabel(l), true);
        shouldEqual(r.hasLabel(Modification("Oxidation")), false);

        r.removeIsotopicLabel();
        shouldEqual(r.getIsotopicLabel(), modifications::Modification(""));
        shouldEqual(r.isLabeled(), false);
        shouldEqual(r.hasLabel(l), false);

        r.changeType(RawAminoAcidImpl::PEPTIDE_C_TERM);
        shouldEqual(r.isCTerm(), true);
        r.changeType(RawAminoAcidImpl::PROTEIN_C_TERM);
        shouldEqual(r.isCTerm(), true);
        r.changeType(RawAminoAcidImpl::PEPTIDE_N_TERM);
        shouldEqual(r.isNTerm(), true);
        r.changeType(RawAminoAcidImpl::PROTEIN_N_TERM);
        shouldEqual(r.isNTerm(), true);

        Residue r1 = r;
        r1.changeType('C');
        r1.removeModification();
        r1.removeIsotopicLabel();

        shouldEqual(r != r1, true);
        shouldEqual(r == r1, false);
    }

    void testResidueStoichiometry()
    {
        elements::Element H(1);
        elements::Element C(6);
        elements::Element N(7);
        elements::Element O(8);
        elements::Element S(16);

        Residue r('M');

        Stoichiometry expectedS;
        expectedS.set(H, 9);
        expectedS.set(C, 5);
        expectedS.set(N, 1);
        expectedS.set(O, 1);
        expectedS.set(S, 1);

        shouldEqual(r.getStoichiometry(), expectedS);
        r.setModification("Oxidation");
        expectedS.add(O, 1);
        shouldEqual(r.getStoichiometry(), expectedS);

        std::vector<elements::Isotope> cHi;
        elements::Element cH(
            elements::ElementImpl(elements::ElementImpl::getNextId(), "H", 1,
                cHi));
        StoichiometryConfigImpl sci("test1");
        sci.insertElement(cH);
        StoichiometryConfig sc(sci);

        r.applyAminoAcidStoichiometryConfig(
            StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG);

        shouldEqual(r.getStoichiometry(), expectedS);

        r.applyAminoAcidStoichiometryConfig(sc);

        expectedS.set(H, 0);
        expectedS.set(cH, 9);

        shouldEqual(r.getStoichiometry(), expectedS);

        std::vector<elements::Isotope> cOi;
        elements::Element cO(
            elements::ElementImpl(elements::ElementImpl::getNextId(), "O", 8,
                cOi));
        StoichiometryConfigImpl scim("test2");
        scim.insertElement(cO);
        StoichiometryConfig scm(scim);
        r.applyModificationStoichiometryConfig("test2");

        expectedS.set(O, 1);
        expectedS.set(cO, 1);

        shouldEqual(r.getStoichiometry(), expectedS);

        r.setIsotopicLabel("ESP");
        expectedS.add(H, 26);
        expectedS.add(C, 16);
        expectedS.add(N, 4);
        expectedS.add(O, 2);
        expectedS.add(S, 1);

        shouldEqual(r.getStoichiometry(), expectedS);

        r.applyIsotopicLabelStoichiometryConfig(
            StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG);
        shouldEqual(r.getStoichiometry(), expectedS);

        std::vector<elements::Isotope> cSi;
        elements::Element cS(
            elements::ElementImpl(elements::ElementImpl::getNextId(), "S", 16,
                cSi));
        StoichiometryConfigImpl scil("test3");
        scil.insertElement(cS);
        StoichiometryConfig scl(scil);
        r.applyIsotopicLabelStoichiometryConfig(scl);

        expectedS.add(S, -1);
        expectedS.add(cS, 1);
        shouldEqual(r.getStoichiometry(), expectedS);
    }

};

/** The main function that runs the tests for class Residue.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ResidueTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

