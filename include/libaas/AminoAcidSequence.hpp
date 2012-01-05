/*
 * AminoAcidSequence.hpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2011,2012 Marc Kirchner
 * Copyright (c) 2010 Nathan Huesken
 * Copyright (c) 2009 Marc Kirchner
 * Copyright (c) 2008 Thorben Kroeger
 *
 */

#ifndef __LIBAAS_INCLUDE_LIBAAS_AMINOACIDSEQUENCE_HPP__
#define __LIBAAS_INCLUDE_LIBAAS_AMINOACIDSEQUENCE_HPP__

#include <libaas/Residue.hpp>
#include <libaas/Collection.hpp>
#include <libaas/Types.hpp>

#include <iostream>

namespace libaas {

/** AminoAcidSequence
 * A sequence of amino acids, convenient for peptide representation.
 *
 * AminoAcidSequence holds an ordered list of \a AminoAcid, including their
 * \a AminoAcidModification.
 * Two fake amino acids ('0' and '1') are placed at the beginning and end of
 * each amino acid sequence to represent N and C terminals. When new amino
 * acids are added to the sequence, they are pushed before the C terminal.
 * The begin() and end() functions, stack operators, etc, all take into account
 * the terminals.
 * So the first amino acid is really sequence[1].
 * @ingroup ASAP
 *
 *
 * TODO look at all functions altering the sequence, such as append etc. There might be some specific "mistakes"
 * TODO I have to check all "apply modification" functions, since the "mechanics" changed from asap to libaas
 *
 */
class AminoAcidSequence: public libaas::Collection<libaas::Residue> {

public:

	typedef std::vector<modifications::Modification> ModificationList;

	AminoAcidSequence(const libaas::String& aminoAcidSequence);
	AminoAcidSequence(const libaas::String& aminoAcidSequence,
			const String& modificationString);
	/** Construct an amino acid sequence from another sequence.
	 */
	AminoAcidSequence(const_iterator first, const_iterator last);

	/**
	 * Modified stack operations, to push in front of the C-terminal
	 * but after N-terminal
	 */
	virtual void push_back(const Residue& value);
	virtual void pop_back(void);
	/** Access operators.
	 * If you want to access the N-terminal, call it with pos = 0
	 * If you want to access the first amino acid, call it with pos = 1
	 * If you want to access the n-th amino acid, call it with pos = n
	 * If you want to access the C-terminal, call it with pos = size()-1
	 */
	Residue& operator[](size_t pos) {
		return c_[pos];
	}

	/**
	 * Change the C-term of the sequence to a Peptide C-term.
	 */
	void makePeptideCTerm();

	/**
	 * Change the N-term of the sequence to a Peptide N-term.
	 */
	void makePeptideNTerm();

	/**
	 * Change the C-term of the sequence to a Peptide C-term.
	 */
	void makeProteinCTerm();

	/**
	 * Change the N-term of the sequence to a Peptide N-term.
	 */
	void makeProteinNTerm();

	/** Apply modifications encoded in a string.
	 *  The format of the string is
	 *
	 *  mod1(aminoAcid1)@pos1; mod2(aminoAcid2)@pos2
	 *
	 *  Where pos<n> is a number indicating at which position in the sequence
	 *  the modificaiton with name mod<n> is to be applied. A semicolon behind
	 *  the last position/modification pair is not required.
	 *
	 *  @param[in] modificationString ...
	 */
	void applyModificationString(const std::string& modificationString);

	/**
	 * Remove the modification \mod from all applicable amino acids
	 */
	void remove(const modifications::Modification& mod);

	/**
	 * Append the Sequence \a s at the end of this sequence
	 *
	 * possible modifications of the C-terminal of the first sequence get lost here
	 */
	void append(const AminoAcidSequence& s);

	libaas::AminoAcidSequence::iterator apply(
			const modifications::Modification& mod,
			libaas::AminoAcidSequence::iterator begin,
			libaas::AminoAcidSequence::iterator end) const;

	std::vector<AminoAcidSequence> applyVariableModifications(
			const std::vector<
					modifications::RawModificationImpl::RawModificationImplKeyType>& mods,
			unsigned int maxModificationsPerPeptide = 0) const;
	std::vector<AminoAcidSequence> applyVariableModifications(
			const std::vector<modifications::RawModification>& mods,
			unsigned int maxModificationsPerPeptide = 0) const;
	/**
	 * Apply variable modfications
	 */
	std::vector<AminoAcidSequence> applyVariableModifications(
			const ModificationList& mods,
			unsigned int maxModificationsPerPeptide = 0) const;

	void applyFixedModifications(
			const std::vector<
					modifications::RawModificationImpl::RawModificationImplKeyType>& mods);
	void applyFixedModifications(
			const std::vector<modifications::RawModification>& mods);
	/**
	 * Apply fixed modfications
	 * This function actually changes this sequence
	 */
	void applyFixedModifications(const ModificationList& mods);

	void applyModificationAtPosition(
			const modifications::RawModificationImpl::RawModificationImplKeyType& mod,
			const Size& pos);
	void applyModificationAtPosition(const modifications::RawModification& mod,
			const Size& pos);
	void applyModificationAtPosition(const modifications::Modification& mod,
			const Size& pos);

	Stoichiometry getStoichiometry() const;

	String toUnmodifiedSequenceString() const;
	String toString(const Bool showTerminals = false) const;
	String getModificationString() const;

//    bool operator==(const AminoAcidSequence& s) const;
//    bool operator!=(const AminoAcidSequence& s) const;
//    AminoAcidSequence& operator=(const AminoAcidSequence& rhs);

private:

	void initAminoAcidSequence(const String& sequence);

};
// class AminoAcidSequence

std::ostream& operator<<(std::ostream&, const AminoAcidSequence&);

} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_AMINOACIDSEQUENCE_HPP__ */
