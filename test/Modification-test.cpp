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
//        add(testCase(&ModificationTestSuite::fail));
        add(testCase(&ModificationTestSuite::testModification));
    }

    void testModification() {
    	// creating default modification
    	libaas::String k1 = "Acetyl";
    	Modification m1(k1);
    	std::cout << m1 << std::endl;

    	// creating custom stoichiometry config
    	std::vector<libaas::elements::Isotope> is;
    	is.push_back(libaas::elements::Isotope(99.99, 1.11111111));
    	libaas::elements::addElement(142, "H", 1, is);
    	libaas::elements::addElement(143, "18O", 16, is);

    	libaas::StoichiometryConfigImpl sc("Experiment 1");
    	// inserting element manually by symbol and id
    	sc.insert(libaas::StoichiometryConfigImpl::EntryType("H", 142));
    	// inserting element "automatically" by fw<ElementImpl>
    	sc.insertElement(libaas::elements::Element(143));
    	// free function to add stoichiometry config
    	libaas::addStoichiometryConfig(sc);

    	// creating default modification
    	Modification m2(k1);
    	// changing stoichiometry config
    	m2.setStoichiometryConfig("Experiment 1");
    	std::cout << m2 << std::endl;

    	// creating custom modification
    	libaas::String k2 = "Amidated";
    	Modification m3(k2, "Experiment 1");
    	std::cout << m3 << std::endl;
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

