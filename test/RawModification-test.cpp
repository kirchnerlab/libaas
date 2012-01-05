/*
 * RawModification-test.cpp
 *
 * Copyright (c) 2012 Mathias Wilhelm
 * Copyright (c) 2012 Marc Kirchner
 *
 */

#include <libaas/RawModification.hpp>
#include <libaas/AminoAcid.hpp>

#include "vigra/unittest.hxx"

#include <iostream>
#include <vector>

using namespace libaas;
using namespace libaas::modifications;
using namespace libaas::aminoAcids;

/** Short description.
 * Long description.
 */
struct RawModificationTestSuite: vigra::test_suite {
	/** Constructor.
	 * The RawModificationTestSuite constructor adds all RawModification tests to
	 * the test suite. If you write an additional test, add the test
	 * case here.
	 */
	RawModificationTestSuite() :
			vigra::test_suite("RawModification") {
		add(testCase(&RawModificationTestSuite::testRawModification));
		add(testCase(&RawModificationTestSuite::testRawModificationRef));
		add(testCase(&RawModificationTestSuite::testAddRawModification));
		add(testCase(&RawModificationTestSuite::testAddRawModificationRef));
		add(
				testCase(&RawModificationTestSuite::testOverrideUninitializedRawModification));
		add(
				testCase(&RawModificationTestSuite::testOverrideInitializedRawModification));
	}

	void testRawModification() {
		RawModificationImpl::RawModificationImplKeyType k = "Deamidated";
		RawModificationImpl deamidated(k);

		shouldEqual(deamidated.getId(), k);
		shouldEqual(deamidated.getName(), "Deamidated");
		shouldEqual(deamidated.getFullName(), "Deamidation");
		shouldEqual(deamidated.isVerified(), true);
		std::vector<String> altNames = deamidated.getAltNames();
		size_t altNameSize = 2;
		shouldEqual(altNames.size(), altNameSize);
		shouldEqual(altNames[0], "phenyllactyl from N-term Phe");
		shouldEqual(altNames[1], "Citrullination");

		libaas::elements::Element H(1);
		libaas::elements::Element N(7);
		libaas::elements::Element O(8);
		Stoichiometry s = deamidated.getStoichiometry(), expected_s;
		expected_s.set(H, -1);
		expected_s.set(N, -1);
		expected_s.set(O, 1);
		shouldEqual(s, expected_s);

		std::vector<Specificity> specificities = deamidated.getSpecificities();
		size_t numberOfSpecificities = 4;
		shouldEqual(specificities.size(), numberOfSpecificities);
		Specificity spec0(AminoAcid('Q'), Specificity::ANYWHERE,
				Specificity::ARTEFACT);
		Specificity spec1(AminoAcid('R'), Specificity::ANYWHERE,
				Specificity::POST_TRANSLATIONAL);
		Specificity spec2(AminoAcid('N'), Specificity::ANYWHERE,
				Specificity::ARTEFACT);
		Specificity spec3(AminoAcid('F'), Specificity::PROTEIN_N_TERM,
				Specificity::POST_TRANSLATIONAL);
		shouldEqual(specificities[0], spec0);
		shouldEqual(specificities[1], spec1);
		shouldEqual(specificities[2], spec2);
		shouldEqual(specificities[3], spec3);

		RawModificationImpl test("id", "name", "fullname", false);
		String name = "test name";
		String fullName = "test full name";
		Bool verified = false;
		Stoichiometry st;
		st.set(H, 10);
		st.set(N, 5);
		st.set(O, 2);
		std::vector<Specificity> specs;
		specs.push_back(
				Specificity(AminoAcid('A'), Specificity::ANYWHERE,
						Specificity::CHEMICAL_DERIVATIVE));
		std::vector<String> alts;
		alts.push_back("Alt name");

		test.setName(name);
		shouldEqual(test.getName(), name);
		test.setFullName(fullName);
		shouldEqual(test.getName(), name);
		test.setVerified(verified);
		shouldEqual(test.isVerified(), verified);
		test.setStoichiometry(st);
		shouldEqual(test.getStoichiometry(), st);
		test.setSpecificities(specs);
		shouldEqual(test.getSpecificities(), specs);
		test.setAltNames(alts);
		shouldEqual(test.getAltNames().size(), alts.size());
		shouldEqual(test.getAltNames()[0], alts[0]);

	}

	void testRawModificationRef() {
		RawModificationImpl::RawModificationImplKeyType k1 = "Carbamyl", k2 =
				"Carboxymethyl";

		// create two different raw modifications without using the factory
		RawModificationImpl e_2(k1);
		RawModificationImpl e_3(k2);

		// create the same raw modifications again, but using the flyweight implementation
		RawModification er_2(k1);
		RawModification er_3(k2);

		// testing equality
		shouldEqual(e_2, er_2);
		shouldEqual(e_3, er_3);

		// testing whether the id extractor works correctly
		shouldEqual(er_2.get_key(), er_2.get().getId());
		shouldEqual(er_3.get_key(), er_3.get().getId());

		// retrieve the amino acids again
		RawModification er_t2(k1);
		RawModification er_t3(k2);

		// test whether the old references and new references point to the same
		// object
		shouldEqual(&er_2.get(), &er_t2.get());
		shouldEqual(&er_3.get(), &er_t3.get());
	}

	void testAddRawModification() {
		// setting up test data
		libaas::elements::Element H(1);
		libaas::elements::Element C(6);
		libaas::elements::Element O(8);

		// create raw modification
		RawModificationImpl::RawModificationImplKeyType k = "customID";
		String name = "Name";
		String name2 = "Othername";
		String fullName = "fullName";
		Bool verified = false;
		std::vector<String> altNames;
		Stoichiometry stoichiometry;
		std::vector<Specificity> specificities;

		// adding not existing element
		shouldEqual(
				addRawModification(k, name, fullName, altNames, stoichiometry, specificities, verified),
				true);
		RawModificationImpl e(k, name, fullName, verified);
		e.setAltNames(altNames);
		e.setStoichiometry(stoichiometry);
		e.setSpecificities(specificities);

		RawModification e_r(k);
		shouldEqual(e, e_r);

		// a second try to add a raw modification with the same id but different properties should fail
		shouldEqual(
				addRawModification(k, name2, fullName, altNames, stoichiometry, specificities, verified),
				false);
		// and the raw modification added in the first place should stay the same
		shouldEqual(RawModification(k), e);
		RawModificationImpl e2(k, name2, fullName, verified);
		e2.setAltNames(altNames);
		e2.setStoichiometry(stoichiometry);
		e2.setSpecificities(specificities);
		shouldEqual(RawModification(k) == e2, false);
	}

	void testAddRawModificationRef() {
		// first test should result in an out_of_range exceptions since the
		// default raw modification table does no contain a raw modification with id "unkown"
		bool thrown = false;
		try {
			RawModification test("unkown");
		} catch (std::out_of_range& e) {
			thrown = true;
		};

		shouldEqual(thrown, true);

		// create an arbitrary raw modification
		RawModificationImpl::RawModificationImplKeyType k1 = "unkown";
		String name = "Name";
		String fullName = "fullName";
		Bool verified = false;
		RawModificationImpl t(k1, name, fullName, verified);
		// add raw modification to the flyweight table
		RawModification tr(t);

		// test equality of the original amino acid and the const ref
		shouldEqual(t, tr);
		shouldEqual(t.getId(), tr.get_key());

		// retrieve the raw modification directly from the flyweight table
		RawModification tr_t(k1);

		// test equality of two const refs of the same raw modification
		shouldEqual(tr, tr_t);
		// test reference pointer to ensure it is the same object
		shouldEqual(&tr.get(), &tr_t.get());
	}

	void testOverrideUninitializedRawModification() {
		// create different raw modification "Deamidated"
		RawModificationImpl::RawModificationImplKeyType k1 = "Phospho";
		String name = "Name";
		String fullName = "fullName";
		Bool verified = false;
		RawModificationImpl t(k1, name, fullName, verified);
		// store it in flyweight table
		RawModification tr(t);
		// retrieve element id k1
		RawModification tr_t(k1);

		// getSymbol returns "Name" instead of "Phospho"
		shouldEqual(tr_t.get().getName(), name);
		shouldEqual(tr_t.get().getName() != RawModificationImpl(k1).getName(),
				true);

	}

	void testOverrideInitializedRawModification() {
		RawModificationImpl::RawModificationImplKeyType k1 = "Phospho";
		RawModification tr_1(k1);

		RawModificationImpl t(k1, "other name", "full name", false);
		// flyweight checks the id of the raw modification t and recognizes it, since it
		// was retrieved(initialized) earlier
		// as a consequence, the flyweight factory returns the known object
		// instead of overriding it with the given one!
		RawModification tr_2(t);

		shouldEqual(tr_2.get().getName() != "other name", true);
	}

};

/** The main function that runs the tests for class RawModification.
 * Under normal circumstances you need not edit this.
 */
int main() {
	RawModificationTestSuite test;
	int success = test.run();
	std::cout << test.report() << std::endl;
	return success;
}

