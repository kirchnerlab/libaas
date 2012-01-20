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

#include <boost/shared_ptr.hpp>

#include <iostream>

namespace libaas {

/**Representation of a residue.
 *
 * A residue holds an amino acid and its modification.
 */
class Residue
{

public:

    typedef boost::shared_ptr<modifications::Modification> ModificationPtr;

    /** Creates a residue with a modification
     *
     * Note: the constructor does not check whether the modification is
     * applicable to this amino acid.
     *
     * @param[in] aminoAcidKey The key/id of an amino acid
     * @param[in] modificationKey The key/id of the modification
     * @param[in] labelKey The key/id of the label
     */
    Residue(
        const libaas::aminoAcids::RawAminoAcidImpl::RawAminoAcidImplKeyType& aminoAcidKey =
                '\0',
        const libaas::modifications::RawModificationImpl::RawModificationImplKeyType& modificationKey =
                "",
        const libaas::modifications::RawModificationImpl::RawModificationImplKeyType& labelKey =
                "");

    /**Creates a residue with a modification.
     *
     * Note: the constructor does not check whether the modification is
     * applicable to this amino acid.
     *
     * @param[in] aminoAcid The amino acid
     * @param[in] mod The modification
     * @param[in] label The isotopic label
     */
    Residue(const libaas::aminoAcids::AminoAcid& aminoAcid,
        const libaas::modifications::Modification& mod =
                modifications::Modification(),
        const libaas::modifications::Modification& label =
                modifications::Modification());

    ~Residue();

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
     * Calls setModification(Modification)
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
    const modifications::Modification& getModification() const;

    /**Sets the isotopic label.
     *
     * calls setIsotopicLabel(Modification)
     *
     * @param[in] isotopicLabelKey The key/id of the isotopic label.
     */
    void setIsotopicLabel(
        const libaas::modifications::RawModificationImpl::RawModificationImplKeyType& isotopicLabelKey);

    /**Sets the isotopic label.
     *
     * Note: this method does not check whether the isotopic label is applicable
     * to this position.
     *
     * @param[in] isotopicLabel The isotopic label
     */
    void setIsotopicLabel(
        const libaas::modifications::Modification& isotopicLabel);

    /**Returns the isotopic label of this residue
     * @returns The isotopic label
     */
    const modifications::Modification& getIsotopicLabel() const;

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

    /**Checks whether the isotopic label id is equal to the given key.
     *
     * This check does not include internal properties of the isotopic label,
     * such as custom specificities or the stoichiometry configuration
     *
     * @param[in] labelKey
     * @returns true if isotopicLabel_.get_key() == labelKey, false otherwise
     */
    Bool hasLabel(
        const modifications::RawModificationImpl::RawModificationImplKeyType& labelKey) const;

    /**Checks whether the isotopic label is equal to the given one.
     * @param[in] label Isotopic label
     * @returns true if isotopicLabel_ == label, false otherwise
     */
    Bool hasLabel(const modifications::Modification& label) const;

    /**Checks whether the residue is modified.
     * @returns true if the residue is modified, false otherwise
     */
    Bool isLabeled() const;

    /**Removes the modification.
     */
    void removeModification();

    /**Removes the isotopic label.
     */
    void removeIsotopicLabel();

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

    /**Sets the stoichiometry configuration key of the isotopic label.
     * @param[in] configKey Stoichiometry configuration key
     */
    void applyIsotopicLabelStoichiometryConfig(
        const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configKey);

    /**Sets the stoichiometry configuration of the isotopic label.
     * @param[in] config Stoichiometry configuration
     */
    void applyIsotopicLabelStoichiometryConfig(
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

    static ModificationPtr EMPTY_MOD;

private:

    /** The amino acid.
     */
    libaas::aminoAcids::AminoAcid aminoacid_;
    /** The modification of the amino acid.
     */
    ModificationPtr modification_;
    /** The isotopic label of the amino acid.
     */
    ModificationPtr isotopicLabel_;

};
// class Residue

std::ostream& operator<<(std::ostream&, const Residue&);

} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_RESIDUE_HPP__ */
