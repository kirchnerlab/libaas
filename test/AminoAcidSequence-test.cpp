/*
 * AminoAcidSequence-test.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"

/** Short description.
 * Long description.
 */
struct AminoAcidSequenceTestSuite : vigra::test_suite
{
    /** Constructor.
     * The AminoAcidSequenceTestSuite constructor adds all AminoAcidSequence tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    AminoAcidSequenceTestSuite() :
        vigra::test_suite("AminoAcidSequence")
    {
        add(testCase(&AminoAcidSequenceTestSuite::fail));
    }

    /** Test that is guaranteed to fail.
     * Leave this in until the complete AminoAcidSequence class has tests.
     */
    void fail()
    {
        failTest("No unit tests for class AminoAcidSequence!");
    }
};

/** The main function that runs the tests for class AminoAcidSequence.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    AminoAcidSequenceTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

