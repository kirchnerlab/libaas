/*
 * AminoAcidSequence-test.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/AminoAcidSequence.hpp>

#include "vigra/unittest.hxx"

#include <iostream>

using namespace libaas;

/** Short description.
 * Long description.
 */
struct AminoAcidSequenceTestSuite: vigra::test_suite {
	/** Constructor.
	 * The AminoAcidSequenceTestSuite constructor adds all AminoAcidSequence tests to
	 * the test suite. If you write an additional test, add the test
	 * case here.
	 */
	AminoAcidSequenceTestSuite() :
			vigra::test_suite("AminoAcidSequence") {
		add(testCase(&AminoAcidSequenceTestSuite::testAminoAcidSequence));
	}

	void testAminoAcidSequence() {
		String aass = "AACCCQ";
		String mods = "Phospho(C)@3; Oxidation(C)@5";

		AminoAcidSequence aas(aass);
		aas.applyModificationString(mods);

		std::cout << aas << std::endl;

		// TODO test whether the mod for c and n term work correctly
		// TODO test whether the initial c and n term declaration works correctly

		std::cout << aas.toString(true) << std::endl;
		std::cout << aas.toUnmodifiedSequenceString() << std::endl;
		std::cout << aas.getModificationString() << std::endl;

		AminoAcidSequence::ModificationList modlist;
		modlist.push_back(modifications::Modification("Phospho"));
		std::vector<AminoAcidSequence> list = aas.applyVariableModifications(modlist);
		std::cout << list.size() << std::endl;

		std::cout << aas.getStoichiometry() << std::endl;
		std::cout << aas.getStoichiometry().toString() << std::endl;
	}

};

/** The main function that runs the tests for class AminoAcidSequence.
 * Under normal circumstances you need not edit this.
 */
int main() {
	AminoAcidSequenceTestSuite test;
	int success = test.run();
	std::cout << test.report() << std::endl;
	return success;
}

