/*
 * Modification-test.cpp
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
struct ModificationTestSuite : vigra::test_suite
{
    /** Constructor.
     * The ModificationTestSuite constructor adds all Modification tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    ModificationTestSuite() :
        vigra::test_suite("Modification")
    {
        add(testCase(&ModificationTestSuite::fail));
    }

    /** Test that is guaranteed to fail.
     * Leave this in until the complete Modification class has tests.
     */
    void fail()
    {
        failTest("No unit tests for class Modification!");
    }
};

/** The main function that runs the tests for class Modification.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ModificationTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

