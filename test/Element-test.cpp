/*
 * Element-test.cpp
 *
 * Copyright (c) 2011 AUTHOR
 *
 */

#include <libaas/Element.hpp>

#include "vigra/unittest.hxx"

#include <iostream>

/** Short description.
 * Long description.
 */
struct ElementTestSuite : vigra::test_suite
{
    /** Constructor.
     * The ElementTestSuite constructor adds all Element tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    ElementTestSuite() :
        vigra::test_suite("Element")
    {
        add(testCase(&ElementTestSuite::testElement));
        add(testCase(&ElementTestSuite::testElementRef));
    }

    void testElement() {
        libaas::Element::ElementKeyType k1 = 16;
        libaas::Element e(k1);
        std::cout << e << std::endl;
        failTest("Unit tests for class Element not completed!");
    }

    void testElementRef() {
        libaas::Element::ElementKeyType k1 = 2, k2 = 3;

        libaas::Element e_2(k1);
        libaas::Element e_3(k2);

        libaas::Element::ElementRef er_2(k1);
        libaas::Element::ElementRef er_3(k2);

        shouldEqual(e_2, er_2.get());
        shouldEqual(e_3, er_3.get());

        shouldEqual(er_2.get_key(), er_2.get().getId());
        shouldEqual(er_3.get_key(), er_3.get().getId());

        libaas::Element::ElementRef er_t2(k1);
        libaas::Element::ElementRef er_t3(k2);

        shouldEqual(&er_2.get(), &er_t2.get());
        shouldEqual(&er_3.get(), &er_t3.get());
    }

};

/** The main function that runs the tests for class Element.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ElementTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

