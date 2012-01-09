/*
 * RawRawAminoAcid-test.cpp
 *
 * Copyright (c) 2012 Mathias Wilhelm
 * Copyright (c) 2012 Marc Kirchner
 *
 */

#include <libaas/RawAminoAcid.hpp>
#include <libaas/Stoichiometry.hpp>
#include <libaas/Element.hpp>

#include "vigra/unittest.hxx"

#include <iostream>
#include <algorithm>

using namespace libaas::aminoAcids;
/** Short description.
 * Long description.
 */
struct RawRawAminoAcidTestSuite : vigra::test_suite
{
    /** Constructor.
     * The RawRawAminoAcidTestSuite constructor adds all RawRawAminoAcid tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    RawRawAminoAcidTestSuite() :
        vigra::test_suite("RawRawAminoAcid")
    {
		add(testCase(&RawRawAminoAcidTestSuite::testRawAminoAcid));
		add(testCase(&RawRawAminoAcidTestSuite::testStaticParser));
		add(testCase(&RawRawAminoAcidTestSuite::testRawAminoAcidRef));
		add(testCase(&RawRawAminoAcidTestSuite::testAddRawAminoAcid));
		add(testCase(&RawRawAminoAcidTestSuite::testAddRawAminoAcidRef));
		add(testCase(&RawRawAminoAcidTestSuite::testOverrideUninitializedRawAminoAcid));
		add(testCase(&RawRawAminoAcidTestSuite::testOverrideInitializedRawAminoAcid));
    }

	void testRawAminoAcid() {
		libaas::elements::Element H(1);
		libaas::elements::Element C(6);
		libaas::elements::Element N(7);
		libaas::elements::Element O(8);

		RawAminoAcidImpl::RawAminoAcidImplKeyType k = 'C';
		libaas::Char symbol = 'T';
		libaas::String three = "Cys";
		libaas::String full = "Cysteine";
		libaas::Stoichiometry ts;
		ts.set(H, 6);
		ts.set(C, 2);
		ts.set(O, 1);
		RawAminoAcidImpl aa_c(k, symbol, ts);
		aa_c.setThreeLetterCode(three);
		aa_c.setFullName(full);

		shouldEqual(aa_c.getId(), k);
		shouldEqual(aa_c.getSymbol(), symbol);
		shouldEqual(aa_c.getThreeLetterCode(), three);
		shouldEqual(aa_c.getFullName(), full);
		shouldEqual(aa_c.getStoichiometry(), ts);
		shouldEqual(aa_c.isCTerm(), false);
		shouldEqual(aa_c.isNTerm(), false);
		RawAminoAcidImpl aa_c_c = aa_c;
		shouldEqual(aa_c, aa_c_c);

		shouldEqual(RawAminoAcidImpl(RawAminoAcidImpl::PEPTIDE_C_TERM).isCTerm(),
				true);
		shouldEqual(RawAminoAcidImpl(RawAminoAcidImpl::PROTEIN_C_TERM).isCTerm(),
				true);
		shouldEqual(RawAminoAcidImpl(RawAminoAcidImpl::PEPTIDE_N_TERM).isNTerm(),
				true);
		shouldEqual(RawAminoAcidImpl(RawAminoAcidImpl::PROTEIN_N_TERM).isNTerm(),
				true);

		// test a standard amino acid
		RawAminoAcidImpl::RawAminoAcidImplKeyType k1 = 'A';
		RawAminoAcidImpl aa(k1);

		libaas::Stoichiometry s;
		s.set(H, 5);
		s.set(C, 3);
		s.set(N, 1);
		s.set(O, 1);

		shouldEqual(aa.getId(), k1);
		shouldEqual(aa.getSymbol(), 'A');
		shouldEqual(aa.getStoichiometry(), s);
		shouldEqual(aa.getThreeLetterCode(), "Ala");
		shouldEqual(aa.getFullName(), "Alanine");
		shouldEqual(aa_c == aa, false);
		shouldEqual(aa_c != aa, true);
	}

	void testStaticParser() {
		libaas::String toparse[] = { "A", "a", "Ala", "ALA", "Alanine",
				"ALAninE", "N-term", "Peptide N-Term" };
		RawAminoAcidImpl::RawAminoAcidImplKeyType expectedRawAminoAcid[] = { 'A', 'A',
				'A', 'A', 'A', 'A', RawAminoAcidImpl::PROTEIN_N_TERM,
				RawAminoAcidImpl::PEPTIDE_N_TERM };
		size_t n = 8;

		for (size_t i = 0; i < n; ++i) {
			shouldEqual(RawAminoAcidImpl::getKeyForAminoAcidString(toparse[i]),
					expectedRawAminoAcid[i]);
		}

		bool thrown = false;
		try {
			RawAminoAcidImpl::getKeyForAminoAcidString("unknown");
		} catch (std::out_of_range& e) {
			thrown = true;
		}
		shouldEqual(thrown, true);
	}

	void testRawAminoAcidRef() {
		RawAminoAcidImpl::RawAminoAcidImplKeyType k1 = 'L', k2 = 'G';

		// create two different amino acids without using the factory
		RawAminoAcidImpl e_2(k1);
		RawAminoAcidImpl e_3(k2);

		// create the same amino acids again, but using the flyweight implementation
		RawAminoAcid er_2(k1);
		RawAminoAcid er_3(k2);

		// testing equality
		shouldEqual(e_2, er_2.get());
		shouldEqual(e_3, er_3.get());

		// testing whether the id extractor works correctly
		shouldEqual(er_2.get_key(), er_2.get().getId());
		shouldEqual(er_3.get_key(), er_3.get().getId());

		// retrieve the amino acids again
		RawAminoAcid er_t2(k1);
		RawAminoAcid er_t3(k2);

		// test whether the old references and new references point to the same
		// object
		shouldEqual(&er_2.get(), &er_t2.get());
		shouldEqual(&er_3.get(), &er_t3.get());
	}

	// testing static function to add an amino acid
	void testAddRawAminoAcid() {
		// setting up test data
		libaas::elements::Element H(1);
		libaas::elements::Element C(6);
		libaas::elements::Element O(8);

		RawAminoAcidImpl::RawAminoAcidImplKeyType k = 'Z';
		libaas::Char symbol = 'e';
		libaas::Char symbol2 = 't';
		libaas::String three = "Zet";
		libaas::String full = "Zetet";
		libaas::Stoichiometry ts;
		ts.set(H, 6);
		ts.set(C, 2);
		ts.set(O, 1);

		// adding not existing element
		shouldEqual(addRawAminoAcid(k, symbol, three, full, ts), true);
		RawAminoAcidImpl e(k, symbol, ts);
		e.setThreeLetterCode(three);
		e.setFullName(full);
		RawAminoAcid e_r(k);
		shouldEqual(e, e_r);

		// a second try to add an element with the same id should fail
		shouldEqual(addRawAminoAcid(k, symbol2, three, full, ts), false);
		// and the amino acid added in the frist place should stay the same
		shouldEqual(RawAminoAcid(k), e);
		RawAminoAcidImpl e2(k, symbol2, ts);
		shouldEqual(RawAminoAcid(k) == e2, false);
	}

	void testAddRawAminoAcidRef() {
		// first test should result in an out_of_range exceptions since the
		// default amino acid table does no contain an amino acid with char 'z'
		bool thrown = false;
		try {
			RawAminoAcid test('z');
		} catch (std::out_of_range& e) {
			thrown = true;
		}shouldEqual(thrown, true);

		// create an arbitrary amino acid
		RawAminoAcidImpl::RawAminoAcidImplKeyType k1 = 'z';
		libaas::Char name = 'z';
		libaas::Stoichiometry ts;
		RawAminoAcidImpl t(k1, name, ts);
		// add amino acid to the flyweight table
		RawAminoAcid tr(t);

		// test equality of the original amino acid and the const ref
		shouldEqual(t, tr);
		shouldEqual(t.getId(), tr.get_key());

		// retrieve the amino acid directly from the flyweight table
		RawAminoAcid tr_t(k1);

		// test equality of two const refs of the same amino acids
		shouldEqual(tr, tr_t);
		// test reference pointer to ensure it is the same object
		shouldEqual(&tr.get(), &tr_t.get());

		RawAminoAcidImpl::RawAminoAcidImplKeyType kk = 'Q';
		RawAminoAcid wt;
		wt = kk;
		shouldEqual(RawAminoAcid('Q'), wt);
	}

	void testOverrideUninitializedRawAminoAcid() {
		// create different amino acid T
		RawAminoAcidImpl::RawAminoAcidImplKeyType k1 = 'S';
		libaas::Char symbol = 'Q';
		libaas::Stoichiometry ts;
		RawAminoAcidImpl t(k1, symbol, ts);
		// store it in flyweight table
		RawAminoAcid tr(t);
		// retrieve element id k1
		RawAminoAcid tr_t(k1);

		// getSymbol returns Q instead of T
		shouldEqual(tr_t.get().getSymbol(), symbol);
		shouldEqual(tr_t.get().getSymbol() != RawAminoAcidImpl(k1).getSymbol(),
				true);
	}

	void testOverrideInitializedRawAminoAcid() {
		RawAminoAcidImpl::RawAminoAcidImplKeyType k1 = 'A';
		RawAminoAcid tr_1(k1);

		RawAminoAcidImpl t(k1, 'T', libaas::Stoichiometry());
		// flyweight checks the id of the amino acid t and recognizes it, since it
		// was retrieved(initialized) earlier
		// as a consequence, the flyweight factory returns the known object
		// instead of overriding it with the given one!
		RawAminoAcid tr_2(t);

		shouldEqual(tr_2.get().getSymbol() != 'T', true);
	}
};

/** The main function that runs the tests for class RawRawAminoAcid.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    RawRawAminoAcidTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

