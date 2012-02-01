/*
 * Error-test.cpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2011,2012 Marc Kirchner
 *
 */

#include <aas/Error.hpp>

#include "vigra/unittest.hxx"

#include <iostream>

using namespace aas::errors;

/** Short description.
 * Long description.
 */
struct ErrorTestSuite : vigra::test_suite
{
    /** Constructor.
     * The ErrorTestSuite constructor adds all Error tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    ErrorTestSuite() :
            vigra::test_suite("Error")
    {
        add(testCase(&ErrorTestSuite::testError));
        add(testCase(&ErrorTestSuite::testErrorDefines));
    }

    void testError()
    {
        {
            Exception e1("test");
            aas::String e1msg = e1.what();
            shouldEqual(e1msg, "test");

            aas::String msg = "other test";
            Exception e2(msg);
            shouldEqual(e2.what(), msg);
        }
        {
            LogicError e1("test");
            aas::String e1msg = e1.what();
            shouldEqual(e1msg, "test");

            aas::String msg = "other test";
            LogicError e2(msg);
            shouldEqual(e2.what(), msg);
        }
        {
            RuntimeError e1("test");
            aas::String e1msg = e1.what();
            shouldEqual(e1msg, "test");

            aas::String msg = "other test";
            RuntimeError e2(msg);
            shouldEqual(e2.what(), msg);
        }
        {
            OutOfRange e1("test");
            aas::String e1msg = e1.what();
            shouldEqual(e1msg, "test");

            aas::String msg = "other test";
            OutOfRange e2(msg);
            shouldEqual(e2.what(), msg);
        }
    }

    void testErrorDefines()
    {
        aas::String msg = "error";
        aas::Bool thrown = false;
        try {
            aas_logic_error_cond(false, msg.c_str());
        } catch (LogicError& e) {
            shouldEqual(e.what(), msg);
            thrown = true;
        }shouldEqual(thrown, true);

        thrown = false;
        try {
            aas_logic_error_cond(true, msg.c_str());
        } catch (LogicError& e) {
            shouldEqual(e.what(), msg);
            thrown = true;
        }shouldEqual(thrown, false);

        thrown = false;
        try {
            aas_logic_error(msg.c_str());
        } catch (LogicError& e) {
            shouldEqual(e.what(), msg);
            thrown = true;
        }shouldEqual(thrown, true);

        thrown = false;
        try {
            aas_outofrange_cond(false, msg.c_str());
        } catch (OutOfRange& e) {
            shouldEqual(e.what(), msg);
            thrown = true;
        }shouldEqual(thrown, true);

        thrown = false;
        try {
            aas_outofrange_cond(true, msg.c_str());
        } catch (OutOfRange& e) {
            shouldEqual(e.what(), msg);
            thrown = true;
        }shouldEqual(thrown, false);

        thrown = false;
        try {
            aas_outofrange(msg.c_str());
        } catch (OutOfRange& e) {
            shouldEqual(e.what(), msg);
            thrown = true;
        }shouldEqual(thrown, true);

        thrown = false;
        try {
            aas_fail(msg.c_str());
        } catch (RuntimeError& e) {
            shouldEqual(e.what(), msg);
            thrown = true;
        }
        shouldEqual(thrown, true);
    }

};

/** The main function that runs the tests for class Error.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ErrorTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

