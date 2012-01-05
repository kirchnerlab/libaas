/*
 * Residue-test.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Residue.hpp>

#include "vigra/unittest.hxx"

#include <iostream>

using namespace libaas;
using namespace libaas::aminoAcids;
using namespace libaas::modifications;

/** Short description.
 * Long description.
 */
struct ResidueTestSuite: vigra::test_suite {
	/** Constructor.
	 * The ResidueTestSuite constructor adds all Residue tests to
	 * the test suite. If you write an additional test, add the test
	 * case here.
	 */
	ResidueTestSuite() :
			vigra::test_suite("Residue") {
		add(testCase(&ResidueTestSuite::testResidue));
	}

	void testResidue() {

		AminoAcidImpl::AminoAcidImplKeyType aa_k = 'A';
		AminoAcid aa(aa_k);
		RawModificationImpl::RawModificationImplKeyType m_k = "Phospho";
		Modification m(m_k);

		Residue r(aa);

		shouldEqual(r.isCTerm(), false);
		shouldEqual(r.isNTerm(), false);
		shouldEqual(r.isModified(), false);

		r.changeType(aa);
		shouldEqual(r.getAminoacid(), aa);

		r.changeType(aa_k);
		shouldEqual(r.getAminoacid(), aa);

		r.setModification(m);
		shouldEqual(r.getModification(), m);
		shouldEqual(r.isModified(), true);
		shouldEqual(r.hasModification(m), true);
		shouldEqual(r.hasModification(Modification("Oxidation")), false);

		r.changeType(AminoAcidImpl::PEPTIDE_C_TERM);
		shouldEqual(r.isCTerm(), true);
		r.changeType(AminoAcidImpl::PROTEIN_C_TERM);
		shouldEqual(r.isCTerm(), true);
		r.changeType(AminoAcidImpl::PEPTIDE_N_TERM);
		shouldEqual(r.isNTerm(), true);
		r.changeType(AminoAcidImpl::PROTEIN_N_TERM);
		shouldEqual(r.isNTerm(), true);
	}

};

/** The main function that runs the tests for class Residue.
 * Under normal circumstances you need not edit this.
 */
int main() {
	ResidueTestSuite test;
	int success = test.run();
	std::cout << test.report() << std::endl;
	return success;
}

