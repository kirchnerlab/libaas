/*
 * Residue.hpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2011,2012 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_LIBAAS_RESIDUE_HPP__
#define __LIBAAS_INCLUDE_LIBAAS_RESIDUE_HPP__

#include <libaas/AminoAcid.hpp>
#include <libaas/Modification.hpp>
#include <libaas/Types.hpp>

#include <iostream>

namespace libaas {

/**Representation of a residue.
 *
 * A residue holds an amino acid and its modification.
 */
class Residue
{

public:

    /** Creates a residue without a modification
     * @param[in] aminoAcidKey The key/id of an amino acid
     */
    Residue(
        const libaas::aminoAcids::RawAminoAcidImpl::RawAminoAcidImplKeyType& aminoAcidKey =
                '\0');

    /**Creates a residue without a modification.
     * @param[in] aminoAcid The amino acid
     */
    Residue(const libaas::aminoAcids::AminoAcid& aminoAcid);

    /** Creates a residue with a modification
     *
     * Note: the constructor does not check whether the modification is
     * applicable to this amino acid.
     *
     * @param[in] aminoAcidKey The key/id of an amino acid
     * @param[in] modificationKey The key/id of the modification
     */
    Residue(
        const libaas::aminoAcids::RawAminoAcidImpl::RawAminoAcidImplKeyType& aminoAcidKey,
        const libaas::modifications::RawModificationImpl::RawModificationImplKeyType& modificationKey);

    /**Creates a residue with a modification.
     *
     * Note: the constructor does not check whether the modification is
     * applicable to this amino acid.
     *
     * @param[in] aminoAcid The amino acid
     * @param[in] mod The modification
     */
    Residue(const libaas::aminoAcids::AminoAcid& aminoAcid,
        const libaas::modifications::Modification& mod);

    /**Change type of the amino acid.
     * @param[in] aminoAcidKey The key of the amino acid
     *
     * TODO the modification stays the same. shall we remove it?
     */
    void changeType(
        const aminoAcids::RawAminoAcidImpl::RawAminoAcidImplKeyType& aminoAcidKey);

    /**Change type of the amino acid.
     * @param[in] aminoAcid The amino acid
     *
     * TODO the modification stays the same. shall we remove it?
     */
    void changeType(const aminoAcids::AminoAcid& aminoAcid);

    /**Returns the amino acid
     * @returns The amino acid
     */
    const libaas::aminoAcids::AminoAcid& getAminoAcid() const;

    /**Returns a modifiable reference to the amino acid of this residue.
     * @return A reference to the amino acid.
     */
    libaas::aminoAcids::AminoAcid& getAminoAcid();

    /**Checks whether the amino acid is N-terminal.
     * @returns True if the amino acid is AminoAcidImpl::PEPTIDE_N_TERM or
     * AminoAcidImpl::PROTEIN_N_TERM.
     */
    libaas::Bool isNTerm() const;

    /**Checks whether the amino acid is C-terminal.
     * @returns True if the amino acid is AminoAcidImpl::PEPTIDE_C_TERM or
     * AminoAcidImpl::PEPTIDE_C_TERM.
     */
    libaas::Bool isCTerm() const;

    /**Sets the modification.
     *
     * Note: this method does not check whether the modification is applicable
     * to this position.
     *
     * @param[in] modificationKey The key of a modification
     */
    void setModification(
        const libaas::modifications::RawModificationImpl::RawModificationImplKeyType& modificationKey);

    /**Sets the modification.
     *
     * Note: this method does not check whether the modification is applicable
     * to this position.
     *
     * @param[in] modification The modifiaction
     */
    void setModification(
        const libaas::modifications::Modification& modification);

    /**Returns the modification of this residue
     * @returns The modification
     */
    const libaas::modifications::Modification& getModification() const;

    /**Returns the modifiable modificaiton of this residue.
     * @returns A reference to modification
     */
    libaas::modifications::Modification& getModification();

    /**Checks whether the modification id is equal to the given key.
     *
     * This check does not include internal properties of the modification,
     * such as custom specificities or the stoichiometry configuration
     *
     * @param[in] modificationKey
     * @returns true if modification_.get_key() == modificationKey, false otherwise
     */
    Bool hasModification(
        const modifications::RawModificationImpl::RawModificationImplKeyType& modificationKey) const;

    /**Checks whether the modification is equal to the given one.
     * @param[in] modification Modification
     * @returns true if modification_ == modification, false otherwise
     */
    Bool hasModification(
        const modifications::Modification& modification) const;

    /**Checks whether the residue is modified.
     * @returns true if the residue is modified, false otherwise
     */
    Bool isModified() const;

    /**Removes the modification.
     */
    void removeModification();

    /**Sets the stoichiometry configuration key of the amino acid.
     * @param[in] configKey Stoichiometry configuration key
     */
    void applyAminoAcidStoichiometryConfig(
        const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configKey);

    /**Sets the stoichiometry configuration of the amino acid.
     * @param[in] config Stoichiometry configuration
     */
    void applyAminoAcidStoichiometryConfig(const StoichiometryConfig& config);

    /**Sets the stoichiometry configuration key of the modification.
     * @param[in] configKey Stoichiometry configuration key
     */
    void applyModificationStoichiometryConfig(
        const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configKey);

    /**Sets the stoichiometry configuration of the modification.
     * @param[in] config Stoichiometry configuration
     */
    void applyModificationStoichiometryConfig(
        const StoichiometryConfig& config);

    /**Returns the stoichiometry of the residue.
     * Note: This method actually calculates the stoichiometry by summing up the
     * stoichiometry of the amino acid and of the modification.
     *
     * @returns Stoichiometry of the amino acid plus its modification
     */
    Stoichiometry getStoichiometry() const;

    /**Returns a human readable string containing the symbol of the amino acid
     * the, if present, its modification in parenthesis, i.e. C(Oxidation)
     * @returns human readable string containing the amino acid symbol and its
     * modification
     */
    String toString() const;

    /**Sets a copy of the argument as the new content for the residue object.
     * The previous content is dropped.
     * @param[in] rhs Residue to copy
     * @returns *this
     */
    Residue& operator=(const Residue& rhs);

    /**Compares the residue against another.
     * @param[in] r Residue object to compare *this with
     * @returns true if both residues are the same, false otherwise
     */
    bool operator==(const Residue& r) const;

    /**Compares the residue against another, with opposite result of
     * Residue::operator==.
     * @param[in] r Residue object to compare *this with
     * @returns true if the residues are different, false otherwise.
     */
    bool operator!=(const Residue& r) const;

private:

    /** The amino acid.
     */
    libaas::aminoAcids::AminoAcid aminoacid_;
    /** The modification of the amino acid.
     */
    libaas::modifications::Modification modification_;

};
// class Residue

std::ostream& operator<<(std::ostream&, const Residue&);

} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_RESIDUE_HPP__ */
