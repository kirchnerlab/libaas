/*
 * Residue-test.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Residue.hpp>

#include "vigra/unittest.hxx"

#include <iostream>

using namespace libaas;

/** Short description.
 * Long description.
 */
struct ResidueTestSuite: vigra::test_suite {
    /** Constructor.
     * The ResidueTestSuite constructor adds all Residue tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    ResidueTestSuite() :
        vigra::test_suite("Residue")
    {
        add(testCase(&ResidueTestSuite::testResidue));
    }

    void testResidue()
    {

        libaas::aminoAcids::AminoAcidImpl::AminoAcidImplKeyType aa_k = 'A';
        libaas::aminoAcids::AminoAcid aa(aa_k);
        libaas::modifications::ModificationImpl::ModificationImplKeyType m_k =
                1;
        libaas::modifications::Modification m(m_k);

        Residue r(aa);
        r.setAminoacid(aa);
        shouldEqual(r.getAminoacid(), aa);

        r.setModification(m);
        shouldEqual(r.getModification(), m);
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

