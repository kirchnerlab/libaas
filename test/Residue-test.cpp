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
        add(testCase(&ResidueTestSuite::fail));
    }

    /** Test that is guaranteed to fail.
     * Leave this in until the complete Residue class has tests.
     */
    void fail()
    {
        failTest("No unit tests for class Residue!");
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

