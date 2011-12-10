/*
 * AminoAcid-test.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/AminoAcid.hpp>

#include "vigra/unittest.hxx"

#include <iostream>

using namespace libaas::aminoAcids;

/** Short description.
 * Long description.
 */
struct AminoAcidTestSuite: vigra::test_suite {
    /** Constructor.
     * The AminoAcidTestSuite constructor adds all AminoAcid tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    AminoAcidTestSuite() :
        vigra::test_suite("AminoAcid")
    {
        add(testCase(&AminoAcidTestSuite::testAminoAcid));
        add(testCase(&AminoAcidTestSuite::testAminoAcidRef));
        add(testCase(&AminoAcidTestSuite::testAddAminoAcid));
        add(testCase(&AminoAcidTestSuite::testAddAminoAcidRef));
        add(testCase(&AminoAcidTestSuite::testOverrideUninitializedAminoAcid));
        add(testCase(&AminoAcidTestSuite::testOverrideInitializedAminoAcid));
    }

    void testAminoAcid()
    {
        failTest("No unit tests for class Modification!");
    }

    void testAminoAcidRef()
    {
        failTest("No unit tests for class Modification!");
    }

    void testAddAminoAcid()
    {
        failTest("No unit tests for class Modification!");
    }

    void testAddAminoAcidRef()
    {
        failTest("No unit tests for class Modification!");
    }

    void testOverrideUninitializedAminoAcid()
    {
        failTest("No unit tests for class Modification!");
    }

    void testOverrideInitializedAminoAcid()
    {
        failTest("No unit tests for class Modification!");
    }

};

/** The main function that runs the tests for class AminoAcid.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    AminoAcidTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

