/*
 * FILENAME
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
struct CLASSNAMETestSuite : vigra::test_suite
{
    /** Constructor.
     * The CLASSNAMETestSuite constructor adds all CLASSNAME tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    CLASSNAMETestSuite() :
        vigra::test_suite("CLASSNAME")
    {
        add(testCase(&CLASSNAMETestSuite::fail));
    }

    /** Test that is guaranteed to fail.
     * Leave this in until the complete CLASSNAME class has tests.
     */
    void fail()
    {
        failTest("No unit tests for class CLASSNAME!");
    }
};

/** The main function that runs the tests for class CLASSNAME.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    CLASSNAMETestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

