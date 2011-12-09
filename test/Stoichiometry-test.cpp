/*
 * Stoichiometry-test.cpp
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
struct StoichiometryTestSuite: vigra::test_suite {
    /** Constructor.
     * The StoichiometryTestSuite constructor adds all Stoichiometry tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    StoichiometryTestSuite() :
        vigra::test_suite("Stoichiometry")
    {
        add(testCase(&StoichiometryTestSuite::testStoichiometry));
        add(testCase(&StoichiometryTestSuite::testStoichiometryArithmetic));
    }

    void testStoichiometry()
    {
        failTest("No unit tests for class Stoichiometry!");
    }

    void testStoichiometryArithmetic()
    {
        failTest("No unit tests for class Stoichiometry!");
    }

};

/** The main function that runs the tests for class Stoichiometry.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    StoichiometryTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

