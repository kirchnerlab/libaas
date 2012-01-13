/*
 * AminoAcidSequence-test.cpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2011,2012 Marc Kirchner
 *
 */

#include <libaas/AminoAcidSequence.hpp>

#include "vigra/unittest.hxx"

#include <iostream>
#include <set>

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
		add(
				testCase(&AminoAcidSequenceTestSuite::testAminoAcidSequenceSequenceAltering));
		add(
				testCase(&AminoAcidSequenceTestSuite::testAminoAcidSequenceApplyModifications));
		add(
				testCase(&AminoAcidSequenceTestSuite::testAminoAcidSequenceAminoAcidStoichiometry));
		add(testCase(&AminoAcidSequenceTestSuite::testAminoAcidSequenceApplyVariableModifications));
	}

	void testAminoAcidSequence() {
		String aass = "AACCCQ";
		String mods = "Phospho(C)@3; Oxidation(C)@5";
		String aassm = "AAC(Phospho)CC(Oxidation)Q";

		AminoAcidSequence aas(aass);
		shouldEqual(aas.toString(), aass);
		shouldEqual(aas.toString(true), "0" + aass + "1");
		shouldEqual(aas.toUnmodifiedSequenceString(), aass);

		aas.applyModificationAtPosition("Phospho", 3);
		aas.applyModificationAtPosition("Oxidation", 5);

		shouldEqual(aas.toString(), aassm);
		shouldEqual(aas.toString(true), "0" + aassm + "1");
		shouldEqual(aas.getModificationString(), mods);

		shouldEqual(aas[3].isModified(), true);
		shouldEqual(aas[3].hasModification("Phospho"), true);
		shouldEqual(aas[5].isModified(), true);
		shouldEqual(aas[5].hasModification("Oxidation"), true);

		AminoAcidSequence aasc(aas.begin(), aas.end());
		shouldEqual(aasc, aas);

		// remove oxidation
		shouldEqual(aasc[5].isModified(), true);
		aasc.remove("Oxidation");
		shouldEqual(aasc[5].isModified(), false);

		modifications::Modification cphospho("Phospho");
		StoichiometryConfig sc(StoichiometryConfigImpl("test"));
		cphospho.setStoichiometryConfig(sc);
		aasc.applyModificationAtPosition("Phospho", 4);
		aasc.applyModificationAtPosition(cphospho, 5);
		shouldEqual(aasc[4].isModified(), true);
		shouldEqual(aasc[5].isModified(), true);
		// remove default phospho but not the custom phospho since the stoichiometry config is different
		aasc.remove(modifications::Modification("Phospho"));
		shouldEqual(aasc[3].isModified(), false);
		shouldEqual(aasc[4].isModified(), false);
		shouldEqual(aasc[5].isModified(), true);

		// test apply stoichiometry config
		StoichiometryConfig dsc(
				StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG);
		aas.applyAminoAcidStoichiometryConfig(sc);
		typedef AminoAcidSequence::const_iterator IT;
		for (IT it = aas.begin(); it != aas.end(); ++it) {
			shouldEqual(it->getAminoAcid().getStoichiometryConfig(), sc);
			shouldEqual(it->getModification().getStoichiometryConfig(), dsc);
		}
		aas.applyModificationStoichiometryConfig(sc);
		aas.applyAminoAcidStoichiometryConfig(dsc);
		typedef AminoAcidSequence::const_iterator IT;
		for (IT it = aas.begin(); it != aas.end(); ++it) {
			shouldEqual(it->getAminoAcid().getStoichiometryConfig(), dsc);
			shouldEqual(it->getModification().getStoichiometryConfig(), sc);
		}
	}

	void testAminoAcidSequenceSequenceAltering() {
		AminoAcidSequence ass("");
		size_t expectedSize = 0;
		shouldEqual(ass.size(), expectedSize);

		bool thrown = false;
		try {
			ass.makePeptideCTerm();
		} catch (std::out_of_range& e) {
			thrown = true;
		}shouldEqual(thrown, true);

		thrown = false;
		try {
			ass.makePeptideNTerm();
		} catch (std::out_of_range& e) {
			thrown = true;
		}shouldEqual(thrown, true);

		thrown = false;
		try {
			ass.makeProteinCTerm();
		} catch (std::out_of_range& e) {
			thrown = true;
		}shouldEqual(thrown, true);

		thrown = false;
		try {
			ass.makeProteinNTerm();
		} catch (std::out_of_range& e) {
			thrown = true;
		}shouldEqual(thrown, true);
		// testing different situation of push back and pop_back
		ass.push_back('A');
		expectedSize = 3;
		shouldEqual(ass[0], Residue('0'));
		shouldEqual(ass[1], Residue('A'));
		shouldEqual(ass[2], Residue('1'));
		shouldEqual(ass.size(), expectedSize);

		ass.makeProteinNTerm();
		shouldEqual(ass[0], Residue('2'));
		ass.makeProteinCTerm();
		shouldEqual(ass[2], Residue('3'));
		ass.makePeptideNTerm();
		shouldEqual(ass[0], Residue('0'));
		ass.makePeptideCTerm();
		shouldEqual(ass[2], Residue('1'));

		ass.push_back('C');
		expectedSize = 4;
		shouldEqual(ass[0], Residue('0'));
		shouldEqual(ass[1], Residue('A'));
		shouldEqual(ass[2], Residue('C'));
		shouldEqual(ass[3], Residue('1'));
		shouldEqual(ass.size(), expectedSize);

		ass.pop_back();
		expectedSize = 3;
		shouldEqual(ass[0], Residue('0'));
		shouldEqual(ass[1], Residue('A'));
		shouldEqual(ass[2], Residue('1'));
		shouldEqual(ass.size(), expectedSize);

		ass.push_back(Residue('3'));
		expectedSize = 3;
		shouldEqual(ass[0], Residue('0'));
		shouldEqual(ass[1], Residue('A'));
		shouldEqual(ass[2], Residue('3'));
		shouldEqual(ass.size(), expectedSize);

		// push back N term to empty aas
		AminoAcidSequence ass2("");
		ass2.push_back(Residue('2'));
		expectedSize = 2;
		shouldEqual(ass2[0], Residue('2'));
		shouldEqual(ass2[1], Residue('1'));
		shouldEqual(ass2.size(), expectedSize);

		// TODO see pop_back to do
//		ass2.pop_back();
//		std::cout << ass2.toString(true) << std::endl;
//		expectedSize = 1;
//		shouldEqual(ass2[0], Residue('2'));
//		shouldEqual(ass2.size(),expectedSize);

// push back C term to empty ass
		AminoAcidSequence ass3("");
		ass3.push_back(Residue('3'));
		expectedSize = 2;
		shouldEqual(ass3[0], Residue('0'));
		shouldEqual(ass3[1], Residue('3'));
		shouldEqual(ass3.size(), expectedSize);

		// testing append in various situations
		AminoAcidSequence s1("ACA");
		AminoAcidSequence s2("GTG");
		s2.makeProteinCTerm();
		s2.makeProteinNTerm();
		AminoAcidSequence s3("");
		AminoAcidSequence s4("");

		s1.append(s2);
		shouldEqual(s1.toString(true), "0ACAGTG3");
		s2.append(s2);
		shouldEqual(s2.toString(true), "2GTGGTG3");

		s2.append(s3);
		shouldEqual(s2.toString(true), "2GTGGTG3");

		s3.append(s1);
		shouldEqual(s3.toString(true), "0ACAGTG3");

		s4.append(s4);
		shouldEqual(s4.toString(true), "");

		s4.append(s2);
		shouldEqual(s4.toString(true), "2GTGGTG3");
	}

	void testAminoAcidSequenceAminoAcidStoichiometry() {
		String aass = "ACQT";
		AminoAcidSequence ass(aass);

		elements::Element H(1);
		elements::Element C(6);
		elements::Element N(7);
		elements::Element O(8);
		elements::Element S(16);

		Stoichiometry expectedS;
		expectedS.set(H, 27);
		expectedS.set(C, 15);
		expectedS.set(N, 5);
		expectedS.set(O, 7);
		expectedS.set(S, 1);

		std::vector<elements::Isotope> cHi;
		elements::Element cH(
				elements::ElementImpl(elements::ElementImpl::getNextId(), "H",
						1, cHi));

		shouldEqual(ass.getStoichiometry(), expectedS);

		StoichiometryConfigImpl sci("test1");
		sci.insertElement(cH);
		StoichiometryConfig sc(sci);
		ass.applyAminoAcidStoichiometryConfig(sc);

		expectedS.set(H, 0);
		expectedS.set(cH, 27);

		shouldEqual(ass.getStoichiometry(), expectedS);

		ass.applyModificationAtPosition("Oxidation", 2);
		expectedS.set(O, 8);

		shouldEqual(ass.getStoichiometry(), expectedS);

		std::vector<elements::Isotope> cOi;
		elements::Element cO(
				elements::ElementImpl(elements::ElementImpl::getNextId(), "O",
						8, cOi));
		StoichiometryConfigImpl scim("test2");
		scim.insertElement(cO);
		StoichiometryConfig scm(scim);
		ass.applyModificationStoichiometryConfig(scm);

		expectedS.set(O, 7);
		expectedS.set(cO, 1);

		shouldEqual(ass.getStoichiometry(), expectedS);
	}

	void testAminoAcidSequenceApplyModifications() {
		String aass = "AACCGQQSSG";
		AminoAcidSequence aas(aass);

		modifications::Modification mod("Oxidation");
		aas.applyModificationAtPosition(mod, 3);
		shouldEqual(aas[3].isModified(), true);
		shouldEqual(aas[3].hasModification(mod), true);

		bool thrown = false;
		try {
			aas.applyModificationAtPosition(mod, 1);
		} catch (std::out_of_range& e) {
			thrown = true;
		}shouldEqual(thrown, true);

		aas.remove(mod);
		aas.applyModificationAtPosition("Oxidation", 3);
		shouldEqual(aas[3].isModified(), true);
		shouldEqual(aas[3].hasModification(mod), true);

		aas.remove(mod);
		aas.applyModificationAtPosition(
				modifications::RawModification("Oxidation"), 3);
		shouldEqual(aas[3].isModified(), true);
		shouldEqual(aas[3].hasModification(mod), true);

		AminoAcidSequence::ModificationList ml;
		modifications::Modification mod1("Phospho");
		modifications::Modification mod2("Trimethyl");
		ml.push_back(mod);
		ml.push_back(mod1);
		ml.push_back(mod2);
		aas.makeProteinNTerm();
		aas.applyFixedModifications(ml);

		// N-term
		shouldEqual(aas[0].isModified(), false);
		// A
		shouldEqual(aas[1].hasModification(mod2), true);
		// A
		shouldEqual(aas[2].isModified(), false);
		// C
		shouldEqual(aas[3].hasModification(mod), true);
		// C
		shouldEqual(aas[4].hasModification(mod), true);
		// G
		shouldEqual(aas[5].isModified(), false);
		// Q
		shouldEqual(aas[6].isModified(), false);
		// Q
		shouldEqual(aas[7].isModified(), false);
		// S
		shouldEqual(aas[8].hasModification(mod1), true);
		// S
		shouldEqual(aas[9].hasModification(mod1), true);
		// G
		shouldEqual(aas[10].hasModification(mod), true);
		// C-term
		shouldEqual(aas[11].isModified(), false);
	}

	void testAminoAcidSequenceApplyVariableModifications() {
		failTest("not implemented yet");
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
