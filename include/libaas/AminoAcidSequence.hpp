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
#include <libaas/StoichiometryConfig.hpp>
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
 * Questions:
 *  A amino acid sequence should consists of only one amino acid stoichiometry config?
 *   If so: store default and use it every time a residue is added?
 *  A amino acid sequence has more than one mod stoichiometry config?
 */
class AminoAcidSequence : public libaas::Collection<libaas::Residue>
{

public:

    /**Convenience typedef.
     */
    typedef std::vector<modifications::Modification> ModificationList;

    /**Default constructor of the amino acid sequence.
     *
     * The amino acid sequence string may contain the appropriate N- and C-
     * terminal symbol. In case it does not, a peptide N- and peptide C-term
     * is added automatically.
     *
     * @param[in] aminoAcidSequence The amino acid sequence
     * mod1(aminoAcid1)\@pos1; mod2(aminoAcid2)\@pos2
     * @param[in] aminoAcidConfig The default stoichiometry configuration used
     * for all amino acids
     *
     * @throw Throws an exception if at least one modification is not
     * applicable at the specified position
     */
    AminoAcidSequence(
        const libaas::String& aminoAcidSequence,
        const StoichiometryConfig& aminoAcidConfig = StoichiometryConfig(
            StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG));

    /**Construct an amino acid sequence from another sequence.
     * The constructor automatically adds a peptide N- and peptide C-term
     * if the given sequence does not contain one.
     * @param[in] first Iterator pointing to the beginning in another sequence
     * @param[in] last Iterator pointing to the end of another sequence
     */
    AminoAcidSequence(const_iterator first, const_iterator last);

    /**
     * Modified stack operations, to push in front of the C-terminal
     * but after N-terminal
     *
     * case stack is empty -> this function automatically creates a Pepitde N-Term and Peptide C-term
     *  else ->
     *   case last residue is c-term -> copy last, pop, push_back value, push_back last
     *   else -> push_back value, push_back peptide c-term
     * but: if c-term is passed, prev c-Term is replaced by it
     *
     * @param[in] value Residue to add at the end
     */
    virtual void push_back(const Residue& value);

    /**Removes the last element in the vector, effectively reducing the vector size by one and invalidating all iterators and references to it.
     *
     * This calls the removed element's destructor.
     *
     * but: pop_back will skip any c-term elements
     *  -> save last
     *  -> pop_back
     *  -> pop_back
     *  -> push_back last
     *
     */
    virtual void pop_back(void);

    /** Access operators.
     *
     * Returns a reference to the element at position n in the vector container.
     *
     * If you want to access the N-terminal, call it with pos = 0
     * If you want to access the first amino acid, call it with pos = 1
     * If you want to access the n-th amino acid, call it with pos = n
     * If you want to access the C-terminal, call it with pos = size()-1
     *
     * @param[in] pos Position of an element in the vector
     * @returns A reference to the element at position pos
     */
    Residue& operator[](size_type pos)
    {
        return c_[pos];
    }

    /** Access operators.
     *
     * Returns a const reference to the element at position n in the vector container.
     *
     * If you want to access the N-terminal, call it with pos = 0
     * If you want to access the first amino acid, call it with pos = 1
     * If you want to access the n-th amino acid, call it with pos = n
     * If you want to access the C-terminal, call it with pos = size()-1
     *
     * @param[in] pos Position of an element in the vector
     * @returns A const reference to the element at position pos
     */
    const Residue& operator[](size_type pos) const
    {
        return c_[pos];
    }

    /**Change the C-term of the sequence to a Peptide C-term.
     *
     * @throws Throws an exception if the last residue is not a C-term.
     */
    void makePeptideCTerm();

    /**Change the N-term of the sequence to a Peptide N-term.
     *
     * @throws Throws an exception if the first residue in not a N-term.
     */
    void makePeptideNTerm();

    /**Change the C-term of the sequence to a Protein C-term.
     *
     * @throws Throws an exception if the last residue is not a C-term.
     */
    void makeProteinCTerm();

    /**Change the N-term of the sequence to a Protein N-term.
     *
     * @throws Throws an exception if the first residue is not a N-term.
     */
    void makeProteinNTerm();

    /**Removes all modifications with the key modKey from all residues.
     * @param[in] modKey Modification
     */
    void remove(
        const modifications::RawModificationImpl::RawModificationImplKeyType& modKey);

    /**Removes the modification mod from all residues.
     * Note: Modifications are removed if the modification exactly matches the given one, including the stoichiometry. A modification with the same key but a different stoichiometry configuration will not be removed!
     * @param[in] mod Modification
     */
    void remove(const modifications::Modification& mod);

    /**Append the sequence \a sequence at the end of this sequence.
     *
     * The C-terminal is taken from the second sequence, so the possible
     * modifications of the C-terminal of the first sequence get lost here
     *
     * case this sequence in not sequence ->
     * 		this sequence is empty -> a new peptide n-term is prepended at the beginning
     * 		pop_back c-term of this sequence
     * 		copy sequence.begin()-1 to sequence.end() at the end of this sequence
     * else ->
     * 		case back is c-term -> save last, this sequence pop_back
     * 		else -> last is new peptide c-term
     * 		copy sequence.begin()-1 to sequence.end() at the end of this sequence
     * 		push_back last
     *
     * @param[in] sequence Sequence which is appended at the end of the current
     * sequence
     */
    void append(const AminoAcidSequence& sequence);

    /**Applies the modification to the first applicable position and returns an
     * iterator to this position.
     * @param[in] mod Modification which is applied to the first applicable
     * position
     * @param[in] begin Iterator pointing to the first viable position in a
     * amino acid sequence
     * @param[in] end Iterator pointing to the last position at which the
     * modification should be applied
     * @return Iterator at which die modifications was first applicable. In
     * case no applicable position was found, it returns end.
     *
     * TODO this method was in AminoAcidModification but this is not possible
     * in our case. Maybe we want this a static function? Or free function?
     */
    libaas::AminoAcidSequence::iterator apply(
        const modifications::Modification& mod,
        const libaas::AminoAcidSequence::iterator& begin,
        const libaas::AminoAcidSequence::iterator& end) const;

    /**Convenience function forwarding to
     * applyVariableModifications(const ModificationList& mods, unsigned int maxModificationsPerPeptide)
     * @param[in] mods List of modification keys
     * @param[in] maxModificationsPerPeptide maximum number of modifications per peptide
     * @returns List of amino acid sequences
     */
    std::vector<AminoAcidSequence> applyVariableModifications(
        const std::vector<
                modifications::RawModificationImpl::RawModificationImplKeyType>& mods,
        unsigned int maxModificationsPerPeptide = 0) const;

    /**Convenience function forwarding to
     * applyVariableModifications(const ModificationList& mods, unsigned int maxModificationsPerPeptide)
     * @param[in] mods List of raw modifications
     * @param[in] maxModificationsPerPeptide maximum number of modifications per peptide
     * @returns List of amino acid sequences
     */
    std::vector<AminoAcidSequence> applyVariableModifications(
        const std::vector<modifications::RawModification>& mods,
        unsigned int maxModificationsPerPeptide = 0) const;

    /**Combinatorically applies all variable modifications.
     * TODO what is this function supposed to do?
     * TODO also: we can only apply one modificaiton per peptide
     * @param[in] mods List of modifications
     * @param[in] maxModificationsPerPeptide maximum number of modifications per peptide
     * @returns List of amino acid sequences
     */
    std::vector<AminoAcidSequence> applyVariableModifications(
        const ModificationList& mods, unsigned int maxModificationsPerPeptide =
                0) const;

    /**Convenience function forwarding to
     * applyFixedModifications(const ModificationList& mods)
     * @param[in] mods List of modification keys which should be applied to this
     */
    void applyFixedModifications(
        const std::vector<
                modifications::RawModificationImpl::RawModificationImplKeyType>& mods);

    /**Convenience function forwarding to
     * applyFixedModifications(const ModificationList& mods)
     * @param[in] mods List of raw modifications which should be applied to this
     */
    void applyFixedModifications(
        const std::vector<modifications::RawModification>& mods);

    /**Apply fixed modifications to all applicable positions.
     * This function actually changes this sequence.
     *
     * @param[in] mods List of modifications which should be applied to this
     * amino acid sequence
     */
    void applyFixedModifications(const ModificationList& mods);

    /**Convenience function forwarding to
     * applyModificationAtPosition(const modifications::Modification& mod, const Size& pos)
     * @param[in] mod Modification key which should be applied
     * @param[in] pos Position at which the modification should be applied.
     * @throws Throws an exception if the modification is not applicable to the
     * specified position
     */
    void applyModificationAtPosition(
        const modifications::RawModificationImpl::RawModificationImplKeyType& mod,
        const Size& pos);

    /**Convenience function forwarding to
     * applyModificationAtPosition(const modifications::Modification& mod, const Size& pos)
     * @param[in] mod Raw modification which should be applied
     * @param[in] pos Position at which the modification should be applied.
     * @throws Throws an exception if the modification is not applicable to the
     * specified position
     */
    void applyModificationAtPosition(const modifications::RawModification& mod,
        const Size& pos);

    /**Apply a modification to the amino acid at a specific position.
     * Note that position 0 is the N-term and 1 the first amino acid.
     * @param[in] mod Modification which should be applied
     * @param[in] pos Position at which the modification should be applied.
     * @throws Throws an exception if the modification is not applicable to the
     * specified position
     */
    void applyModificationAtPosition(const modifications::Modification& mod,
        const Size& pos);

    /**Sets the default amino acid stoichiometry configuration.
     * This method will also apply the configuration to all present amino acids.
     * @param[in] aminoAcidConfigKey Default stoichiomtery configuration key for
     * amino acids
     */
    void applyAminoAcidStoichiometryConfig(
        const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& aminoAcidConfigKey);

    /**Sets the default amino acid stoichiometry configuration.
     * This method will also apply the configuration to all present amino acids.
     * @param[in] aminoAcidConfig Default stoichiomtery configuration for
     * amino acids
     */
    void applyAminoAcidStoichiometryConfig(
        const StoichiometryConfig& aminoAcidConfig);

    /**Sets the default stoichiometry configuration for all modifications within
     * this amino acid sequence.
     * @param[in] modificationConfigKey Default stoichiometry configuration key for
     * modifications
     */
    void applyModificationStoichiometryConfig(
        const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& modificationConfigKey);

    /**Sets the default stoichiometry configuration for all modifications within
     * this amino acid sequence.
     * @param[in] modificationConfig Default stoichiometry configuration for
     * modifications
     */
    void applyModificationStoichiometryConfig(
        const StoichiometryConfig& modificationConfig);

    /**Returns the stoichiometry of the amino acid.
     *
     * Note: This method actually calculates the stoichiometry each time!
     *
     * @returns Stoichiometry of the amino acid sequence.
     */
    Stoichiometry getStoichiometry() const;

    /**Returns a string representing the amino acid sequence without the
     * modifications. Each amino acid is represented by its symbol, whereas the
     * N- and C-terminal end is left out.
     * @returns String containing the unmodified sequence of this amino acid
     * sequence
     */
    String toUnmodifiedSequenceString() const;

    /**Returns a string representing the full amino acid including its
     * modifications. The string might look like this:
     *
     * 0AAC(Phospho)CC(Oxidation)Q1
     *
     * The modification in parenthesis indicates that the amino acid before the
     * parenthesis is modified.
     *
     * @param[in] showTerminals Whether the string should contain the terminal
     * amino acid symbols.
     * @returns String representing the full amino acid
     */
    String toString(const Bool showTerminals = false) const;

    /**Returns the modification string as used for the method
     * applyModificationString(const std::string& modificationString)
     * @returns String containing all modifications including its sites and
     * positions.
     */
    String getModificationString() const;

//    bool operator==(const AminoAcidSequence& s) const;
//    bool operator!=(const AminoAcidSequence& s) const;
//    AminoAcidSequence& operator=(const AminoAcidSequence& rhs);

private:

};
// class AminoAcidSequence

std::ostream& operator<<(std::ostream&, const AminoAcidSequence&);

inline void AminoAcidSequence::applyModificationAtPosition(
    const modifications::RawModificationImpl::RawModificationImplKeyType& mod,
    const Size& pos)
{
    applyModificationAtPosition(modifications::Modification(mod), pos);
}

inline void AminoAcidSequence::applyModificationAtPosition(
    const modifications::RawModification& mod, const Size& pos)
{
    applyModificationAtPosition(modifications::Modification(mod), pos);
}

} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_AMINOACIDSEQUENCE_HPP__ */
