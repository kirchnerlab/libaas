/*
 * Specificity-test.cpp
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
        add(testCase(&SpecificityTestSuite::fail));
    }

    /** Test that is guaranteed to fail.
     * Leave this in until the complete Specificity class has tests.
     */
    void fail()
    {
        failTest("No unit tests for class Specificity!");
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

