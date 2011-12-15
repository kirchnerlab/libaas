/*
 * Modification-test.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Modification.hpp>
#include <libaas/Element.hpp>
#include <libaas/StoichiometryConfig.hpp>

#include "vigra/unittest.hxx"

#include <iostream>

using namespace libaas::modifications;

/** Short description.
 * Long description.
 */
struct ModificationTestSuite: vigra::test_suite {
    /** Constructor.
     * The ModificationTestSuite constructor adds all Modification tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    ModificationTestSuite() :
        vigra::test_suite("Modification")
    {
        add(testCase(&ModificationTestSuite::testModification));
        add(testCase(&ModificationTestSuite::testSpecificityModification));
        add(testCase(&ModificationTestSuite::testStoichiometryModification));
    }

    // testing getter/setter
    void testModification() {
    	failTest("Not implemented yet!");
    }

    // testing specificities of a modification (not rawmodification!)
    void testSpecificityModification() {
    	failTest("Not implemented yet!");
    }

    // testing stoichiometry and stoichiometryconfig
    void testStoichiometryModification() {
    	// setting up elements
		libaas::elements::Element H(1);
		libaas::elements::Element C(6);
		libaas::elements::Element N(7);
		libaas::elements::Element O(8);
		libaas::elements::Element S(16);

    	// creating default modification
    	libaas::String k1 = "Acetyl";
    	Modification m1(k1);
    	shouldEqual(m1.getStoichiometryConfig(), libaas::StoichiometryConfig(libaas::StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG));
    	libaas::Stoichiometry st1;
    	st1.set(H, 2);
    	st1.set(C, 2);
    	st1.set(O, 1);
    	shouldEqual(m1.getStoichiometry(), st1);

    	// creating custom stoichiometry config
    	std::vector<libaas::elements::Isotope> is;
    	is.push_back(libaas::elements::Isotope(99.99, 1.11111111));
    	libaas::Size freeID = libaas::elements::ElementImpl::getNextId();
    	libaas::elements::addElement(freeID, "H", 1, is);

    	libaas::StoichiometryConfigImpl sc("Experiment 1");
    	// inserting element "automatically" by fw<ElementImpl>
    	sc.insertElement(libaas::elements::Element(freeID));
    	// free function to add stoichiometry config
    	libaas::addStoichiometryConfig(sc);

    	// creating default modification
    	Modification m2(k1);
    	shouldEqual(m2.getStoichiometry(), st1);
    	// changing stoichiometry config
    	m2.setStoichiometryConfig("Experiment 1");
    	shouldEqual(m2.getStoichiometryConfig(), sc);
    	libaas::Stoichiometry st2;
    	st2.set(libaas::elements::Element(freeID), 2);
    	st2.set(C, 2);
    	st2.set(O, 1);
    	shouldEqual(m2.getStoichiometry(), st2);

    	// creating custom modification
    	libaas::String k2 = "Amidated";
    	Modification m3(k2, "Experiment 1");
    	libaas::Stoichiometry st3;
    	st3.set(libaas::elements::Element(freeID), 1);
    	st3.set(N, 1);
    	st3.set(O, -1);
    	shouldEqual(m3.getStoichiometry(), st3);
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

