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
        add(testCase(&ModificationTestSuite::fail));
        add(testCase(&ModificationTestSuite::testModification));
    }

    void testModification() {
    	// creating default modification
    	Modification m1("Phos");
    	std::cout << m1 << std::endl;

    	// creating custom stoichiometry config
    	std::vector<libaas::elements::Isotope> is;
    	libaas::elements::addElement(142, "13C", 12, is);
    	libaas::elements::addElement(143, "18O", 16, is);

    	libaas::StoichiometryConfigImpl sc("Experiment 1");
    	sc.insert(libaas::StoichiometryConfigImpl::EntryType("13C", 142));
    	sc.insert(libaas::StoichiometryConfigImpl::EntryType("19O", 143));
    	libaas::addStoichiometryConfig(sc);

    	// creating default modification
    	Modification m2("Phos");
    	// changing stoichiometry config
    	m2.setStoichiometryConfig("Experiment 1");
    	std::cout << m2 << std::endl;

    	// creating custom modification
    	Modification m3("13CArg", "Experiment 1");
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

