/*
 * Specificity-test.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Specificity.hpp>

#include "vigra/unittest.hxx"

#include <iostream>

using namespace libaas::modifications;

/** Short description.
 * Long description.
 */
struct SpecificityTestSuite: vigra::test_suite {
	/** Constructor.
	 * The SpecificityTestSuite constructor adds all Specificity tests to
	 * the test suite. If you write an additional test, add the test
	 * case here.
	 */
	SpecificityTestSuite() :
			vigra::test_suite("Specificity") {
		add(testCase(&SpecificityTestSuite::testSpecificity));
		add(testCase(&SpecificityTestSuite::testStaticParser));
	}

	// testing getter/setter
	void testSpecificity() {
		libaas::aminoAcids::AminoAcid aa('A');
		Specificity::Position pos = Specificity::ANYWHERE;
		Specificity::Classification clas = Specificity::ARTEFACT;
		libaas::String comment = "Comment a";
		Specificity spec(aa, pos, clas);
		spec.setComment(comment);

		shouldEqual(spec.getSite(), aa);
		shouldEqual(spec.getClassification(), clas);
		shouldEqual(spec.getPosition(), pos);
		shouldEqual(spec.getComment(), comment);

		libaas::elements::Element H(1);
		libaas::elements::Element C(6);
		libaas::elements::Element N(7);
		libaas::elements::Element O(8);
		libaas::elements::Element S(16);

		libaas::Stoichiometry st1;
		st1.set(H, 1);
		st1.set(C, 2);
		st1.set(N, 3);

		libaas::Stoichiometry st2;
		st2.set(H, 1);
		st2.set(O, 2);
		st2.set(N, 3);

		libaas::Stoichiometry st3;
		st3.set(H, 1);
		st3.set(C, 2);
		st3.set(S, 3);

		libaas::Stoichiometry st4;
		st4.set(H, 1);
		st4.set(O, 2);
		st4.set(S, 3);

		std::vector<libaas::Stoichiometry> emptyLoss;
		std::vector<libaas::Stoichiometry> neutralLoss;
		neutralLoss.push_back(st1);
		neutralLoss.push_back(st2);
		std::vector<libaas::Stoichiometry> pepNeutralLoss;
		pepNeutralLoss.push_back(st3);
		pepNeutralLoss.push_back(st4);

		spec.addNeutralLoss(st1);
		spec.addNeutralLoss(st2);
		shouldEqual(spec.getNeutralLosses(), neutralLoss);

		spec.addPepNeutralLoss(st3);
		spec.addPepNeutralLoss(st4);
		shouldEqual(spec.getPepNeutralLosses(), pepNeutralLoss);

		spec.setNeutralLosses(neutralLoss);
		shouldEqual(spec.getNeutralLosses(), neutralLoss);

		spec.setPepNeutralLosses(pepNeutralLoss);
		shouldEqual(spec.getPepNeutralLosses(), pepNeutralLoss);

		spec.clearNeutralLosses();
		shouldEqual(spec.getNeutralLosses(), emptyLoss);

		spec.clearPepNeutralLosses();
		shouldEqual(spec.getPepNeutralLosses(), emptyLoss);

		Specificity spec1("A", "Anywhere", "Artefact");
		spec1.setComment(comment);
		shouldEqual(spec1, spec);
	}

	// testing static parser for position and classification
	void testStaticParser() {
		// both should fail in case of an invalid position/classification
		libaas::Bool thrown = false;
		try {
			Specificity::parsePositionString("ASD");
		} catch (std::out_of_range& e) {
			thrown = true;
		}

		shouldEqual(thrown, true);

		thrown = false;
		try {
			Specificity::parseClassificationString("ASD");
		} catch (std::out_of_range& e) {
			thrown = true;
		}

		shouldEqual(thrown, true);

		// testing all currently known positions + correct enum value
		const libaas::Char* positions[] = { "Any N-term", "Any C-term",
				"Protein N-term", "Protein C-term", "Anywhere" };

		thrown = false;
		try {
			for (libaas::Size i = 0; i < 5; ++i) {
				shouldEqual(
						(libaas::Size) Specificity::parsePositionString(positions[i]),
						i);
			}
		} catch (std::out_of_range& e) {
			thrown = true;
		}

		shouldEqual(thrown, false);

		// testing all currently known classifications + correct enum value
		const libaas::Char* classifications[] = { "-", "Post-translational",
				"Co-translational", "Pre-translational", "Chemical derivative",
				"Artefact", "N-linked glycosylation", "O-linked glycosylation",
				"Other glycosylation", "Synth. pep. protect. gp.",
				"Isotopic label", "Non-standard residue", "Multiple", "Other" };

		thrown = false;
		try {
			for (libaas::Size i = 0; i < 13; ++i) {
				shouldEqual(
						(libaas::Size) Specificity::parseClassificationString(classifications[i]),
						i);
			}
		} catch (std::out_of_range& e) {
			thrown = true;
		}

		shouldEqual(thrown, false);
	}

};

/** The main function that runs the tests for class Specificity.
 * Under normal circumstances you need not edit this.
 */
int main() {
	SpecificityTestSuite test;
	int success = test.run();
	std::cout << test.report() << std::endl;
	return success;
}

