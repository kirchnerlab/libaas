/*
 * Stoichiometry-test.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Stoichiometry.hpp>
#include <libaas/Element.hpp>

#include "vigra/unittest.hxx"

#include <iostream>

using namespace libaas;

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
        add(testCase(&StoichiometryTestSuite::testApplyStoichiometryConfig));
    }

    void testStoichiometry()
    {
        elements::Element H(1);
        elements::Element C(6);
        elements::Element N(7);
        elements::Element O(8);
        elements::Element S(16);

        Stoichiometry tmp;

        // testing size/empty/zero/nonNegative
        Size expectedSize = 0;
        shouldEqual(tmp.size(), expectedSize);
        shouldEqual(tmp.empty(), true);
        shouldEqual(tmp.nonNegative(), true);

        // testing set/get annotation id
        Int id = 123;
        tmp.setAnnotationId(id);
        shouldEqual(id, tmp.getAnnotationId());

        // testing set/add element count
        tmp.set(H, -3);
        tmp.add(H, 2);
        tmp.add(C, 2);
        tmp.set(N, 3);
        tmp.add(N, -3);
        tmp.add(O, 0);
        shouldEqual(tmp.get(H), -1);
        shouldEqual(tmp.get(C), 2);
        shouldEqual(tmp.get(N), 0);
        shouldEqual(tmp.get(O), 0);
        shouldEqual(tmp.get(S), 0);

        // testing size/empty/zero/nonNegative
        expectedSize = 2;
        shouldEqual(tmp.size(), expectedSize);
        shouldEqual(tmp.empty(), false);
        shouldEqual(tmp.nonNegative(), false);

        // testing iterator
        // ?

        // testing clear
        tmp.clear();
        shouldEqual(tmp.get(H), 0);
        shouldEqual(tmp.get(C), 0);
        shouldEqual(tmp.get(N), 0);
        shouldEqual(tmp.get(O), 0);
        shouldEqual(tmp.get(S), 0);
    }

    void testStoichiometryArithmetic()
    {
        elements::Element H(1);
        elements::Element C(6);
        elements::Element N(7);
        elements::Element O(8);
        elements::Element S(16);

        Stoichiometry s1;
        s1.set(H, 2);
        s1.set(C, 4);
        s1.set(N, 8);
        Stoichiometry s2;
        s2.set(H, 16);
        s2.set(C, 8);
        s2.set(N, 4);
        s2.set(O, 2);

        Stoichiometry s1_minus_s2;
        s1_minus_s2.set(H, -14);
        s1_minus_s2.set(C, -4);
        s1_minus_s2.set(N, 4);
        s1_minus_s2.set(O, -2);

        Stoichiometry s2_minus_s1;
        s2_minus_s1.set(H, 14);
        s2_minus_s1.set(C, 4);
        s2_minus_s1.set(N, -4);
        s2_minus_s1.set(O, 2);

        Stoichiometry s1_plus_s2;
        s1_plus_s2.set(H, 18);
        s1_plus_s2.set(C, 12);
        s1_plus_s2.set(N, 12);
        s1_plus_s2.set(O, 2);

        Stoichiometry s2_plus_s1;
        s2_plus_s1.set(H, 18);
        s2_plus_s1.set(C, 12);
        s2_plus_s1.set(N, 12);
        s2_plus_s1.set(O, 2);

        Stoichiometry s1_si = s1;
        Stoichiometry s2_si = s2;
        {
            Stoichiometry tmp1 = s1 - s2;
            Stoichiometry tmp2 = s1;
            tmp2 -= s2;

            shouldEqual(tmp1, s1_minus_s2);
            shouldEqual(tmp1, tmp2);
            shouldEqual(tmp2 != s1, true);
            shouldEqual(s1, s1_si);
            shouldEqual(s2, s2_si);
        }

        {
            Stoichiometry tmp1 = s2 - s1;
            Stoichiometry tmp2 = s2;
            tmp2 -= s1;

            shouldEqual(tmp1, s2_minus_s1);
            shouldEqual(tmp1, tmp2);
            shouldEqual(tmp2 != s2, true);
            shouldEqual(s1, s1_si);
            shouldEqual(s2, s2_si);
        }

        {
            Stoichiometry tmp1 = s1 + s2;
            Stoichiometry tmp2 = s1;
            tmp2 += s2;

            shouldEqual(tmp1, s1_plus_s2);
            shouldEqual(tmp1, tmp2);
            shouldEqual(s1, s1_si);
            shouldEqual(s2, s2_si);
            shouldEqual(tmp2 != s1, true);
        }

        {
            Stoichiometry tmp1 = s2 + s1;
            Stoichiometry tmp2 = s2;
            tmp2 += s1;

            shouldEqual(tmp1, s2_plus_s1);
            shouldEqual(tmp1, tmp2);
            shouldEqual(s1, s1_si);
            shouldEqual(s2, s2_si);
            shouldEqual(tmp2 != s2, true);
        }

    }

    void testApplyStoichiometryConfig() {
    	failTest("not implemented yet");
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

