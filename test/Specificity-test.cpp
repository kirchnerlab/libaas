/*
 * Specificity-test.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Specificity.hpp>
#include <libaas/Error.hpp>

#include "vigra/unittest.hxx"

#include <iostream>
#include <algorithm>

using namespace libaas::modifications;

/** Short description.
 * Long description.
 */
struct SpecificityTestSuite : vigra::test_suite
{
    /** Constructor.
     * The SpecificityTestSuite constructor adds all Specificity tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    SpecificityTestSuite() :
            vigra::test_suite("Specificity")
    {
        add(testCase(&SpecificityTestSuite::testSpecificity));
        add(testCase(&SpecificityTestSuite::testStaticParser));
        add(testCase(&SpecificityTestSuite::testSpecificityApplicable));
    }

    // testing getter/setter
    void testSpecificity()
    {

        libaas::aminoAcids::RawAminoAcid aa('A');
        Specificity::Position pos = Specificity::ANYWHERE;
        Specificity::Classification clas = Specificity::ARTEFACT;
        libaas::String comment = "Comment a";
        Specificity spec(aa, pos, clas);
        spec.setComment(comment);

        shouldEqual(spec.getSite(), aa);
        shouldEqual(spec.getClassification(), clas);
        shouldEqual(spec.getPosition(), pos);
        shouldEqual(spec.getComment(), comment);

        libaas::aminoAcids::RawAminoAcid aan('C');
        Specificity::Position posn = Specificity::ANY_C_TERM;
        Specificity::Classification clasn = Specificity::POST_TRANSLATIONAL;
        spec.setSite(aan);
        spec.setPosition(posn);
        spec.setClassification(clasn);
        shouldEqual(spec.getSite(), aan);
        shouldEqual(spec.getPosition(), posn);
        shouldEqual(spec.getClassification(), clasn);

        libaas::elements::Element H(1);
        libaas::elements::Element C(6);
        libaas::elements::Element N(7);
        libaas::elements::Element O(8);
        libaas::elements::Element S(16);

        libaas::Stoichiometry st1;
        st1.set(H, 1);
        st1.set(C, 2);
        st1.set(N, 3);

        libaas::Stoichiometry st2;
        st2.set(H, 1);
        st2.set(O, 2);
        st2.set(N, 3);

        libaas::Stoichiometry st3;
        st3.set(H, 1);
        st3.set(C, 2);
        st3.set(S, 3);

        libaas::Stoichiometry st4;
        st4.set(H, 1);
        st4.set(O, 2);
        st4.set(S, 3);

        std::vector<libaas::Stoichiometry> emptyLoss;
        std::vector<libaas::Stoichiometry> neutralLoss;
        neutralLoss.push_back(st1);
        neutralLoss.push_back(st2);
        std::vector<libaas::Stoichiometry> pepNeutralLoss;
        pepNeutralLoss.push_back(st3);
        pepNeutralLoss.push_back(st4);

        spec.addNeutralLoss(st1);
        spec.addNeutralLoss(st2);
        shouldEqual(spec.getNeutralLosses(), neutralLoss);

        spec.addPepNeutralLoss(st3);
        spec.addPepNeutralLoss(st4);
        shouldEqual(spec.getPepNeutralLosses(), pepNeutralLoss);

        spec.setNeutralLosses(neutralLoss);
        shouldEqual(spec.getNeutralLosses(), neutralLoss);

        spec.setPepNeutralLosses(pepNeutralLoss);
        shouldEqual(spec.getPepNeutralLosses(), pepNeutralLoss);

        spec.clearNeutralLosses();
        shouldEqual(spec.getNeutralLosses(), emptyLoss);

        spec.clearPepNeutralLosses();
        shouldEqual(spec.getPepNeutralLosses(), emptyLoss);

        Specificity spec1("C", "Any c-term", "post-translational");
        spec1.setComment(comment);
        shouldEqual(spec1, spec);

        Specificity spec2("G", "Any N-term", "artefact");
        Specificity& spec3 = spec1;
        spec3 = spec1;
        spec2 = spec1;
        shouldEqual(spec1, spec2);
        shouldEqual(spec1, spec3);
        shouldEqual(spec1 != spec2, false);
    }

    // testing static parser for position and classification
    void testStaticParser()
    {
        // both should fail in case of an invalid position/classification
        libaas::Bool thrown = false;
        try {
            Specificity::parsePositionString("ASD");
        } catch (libaas::errors::LogicError& e) {
            thrown = true;
        }

        shouldEqual(thrown, true);

        thrown = false;
        try {
            Specificity::parseClassificationString("ASD");
        } catch (libaas::errors::LogicError& e) {
            thrown = true;
        }

        shouldEqual(thrown, true);

        // testing all currently known positions + correct enum value
        libaas::String positions[] = { "Any N-term", "Any C-term",
                                       "Protein N-term", "Protein C-term",
                                       "Anywhere" };

        thrown = false;
        try {
            for (libaas::Size i = 0; i < 5; ++i) {
                shouldEqual(
                    (libaas::Size) Specificity::parsePositionString(positions[i]),
                    i);
                std::transform(positions[i].begin(), positions[i].end(),
                    positions[i].begin(), ::toupper);
                shouldEqual(
                    (libaas::Size) Specificity::parsePositionString(positions[i]),
                    i);
            }
        } catch (std::out_of_range& e) {
            thrown = true;
        }

        shouldEqual(thrown, false);

        // testing all currently known classifications + correct enum value
        libaas::String classifications[] = { "-", "Post-translational",
                                             "Co-translational",
                                             "Pre-translational",
                                             "Chemical derivative", "Artefact",
                                             "N-linked glycosylation",
                                             "O-linked glycosylation",
                                             "Other glycosylation",
                                             "Synth. pep. protect. gp.",
                                             "Isotopic label",
                                             "Non-standard residue",
                                             "Multiple", "Other" };

        thrown = false;
        try {
            for (libaas::Size i = 0; i < 13; ++i) {
                shouldEqual(
                    (libaas::Size) Specificity::parseClassificationString(classifications[i]),
                    i);
                std::transform(classifications[i].begin(),
                    classifications[i].end(), classifications[i].begin(),
                    ::toupper);
                shouldEqual(
                    (libaas::Size) Specificity::parseClassificationString(classifications[i]),
                    i);
            }
        } catch (std::out_of_range& e) {
            thrown = true;
        }

        shouldEqual(thrown, false);
    }

    void testSpecificityApplicable()
    {
        libaas::aminoAcids::RawAminoAcid prev1('C');
        libaas::aminoAcids::RawAminoAcid prev2(
            libaas::aminoAcids::RawAminoAcidImpl::PEPTIDE_N_TERM);
        libaas::aminoAcids::RawAminoAcid prev3(
            libaas::aminoAcids::RawAminoAcidImpl::PROTEIN_N_TERM);
        libaas::aminoAcids::RawAminoAcid current('C');
        libaas::aminoAcids::RawAminoAcid next1('C');
        libaas::aminoAcids::RawAminoAcid next2(
            libaas::aminoAcids::RawAminoAcidImpl::PEPTIDE_C_TERM);
        libaas::aminoAcids::RawAminoAcid next3(
            libaas::aminoAcids::RawAminoAcidImpl::PROTEIN_C_TERM);
        Specificity spec(current, Specificity::ANY_N_TERM,
            Specificity::ARTEFACT);

        shouldEqual(spec.isApplicable(prev1, current, next1), false);
        shouldEqual(spec.isApplicable(prev2, current, next2), true);
        shouldEqual(spec.isApplicable(prev3, current, next3), false);

        spec.setPosition(Specificity::ANY_C_TERM);
        shouldEqual(spec.isApplicable(prev1, current, next1), false);
        shouldEqual(spec.isApplicable(prev2, current, next2), true);
        shouldEqual(spec.isApplicable(prev3, current, next3), false);

        spec.setPosition(Specificity::PROTEIN_N_TERM);
        shouldEqual(spec.isApplicable(prev1, current, next1), false);
        shouldEqual(spec.isApplicable(prev2, current, next2), false);
        shouldEqual(spec.isApplicable(prev3, current, next3), true);

        spec.setPosition(Specificity::PROTEIN_C_TERM);
        shouldEqual(spec.isApplicable(prev1, current, next1), false);
        shouldEqual(spec.isApplicable(prev2, current, next2), false);
        shouldEqual(spec.isApplicable(prev3, current, next3), true);
    }

};

/** The main function that runs the tests for class Specificity.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    SpecificityTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

