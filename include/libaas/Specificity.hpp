/*
 * Specificity.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2010,2011 Marc Kirchner
 * Copyright (c) 2010 Nathan Huesken
 *
 */

#ifndef __LIBAAS_INCLUDE_LIBAAS_SPECIFICITY_HPP__
#define __LIBAAS_INCLUDE_LIBAAS_SPECIFICITY_HPP__

#include <libaas/RawAminoAcid.hpp>
#include <libaas/Types.hpp>

#include <vector>
#include <iostream>

namespace libaas {
namespace modifications {

/** Representation of the specificity.
 */
class Specificity
{

public:

    /**Available positions.
     */
    enum Position
    {
        ANY_N_TERM = 0, ANY_C_TERM, PROTEIN_N_TERM, PROTEIN_C_TERM, ANYWHERE
    };

    /** Available classifications.
     */
    enum Classification
    {
        NONE = 0,
        POST_TRANSLATIONAL,
        CO_TRANSLATIONAL,
        PRE_TRANSLATIONAL,
        CHEMICAL_DERIVATIVE,
        ARTEFACT,
        N_LINKED_GLYCOSYLATION,
        O_LINKED_GLYCOSYLATION,
        OTHER_GLYCOSYLATION,
        SYNTH_PEP_PROTECT_GP,
        ISOTOPIC_LABEL,
        NON_STANDARD_RESIDUE,
        MULTIPLE,
        OTHER,
        AA_SUBSTITUTION
    };

    /**Default constructor to create a specificity.
     * @param[in] site Site at which an event can happen
     * @param[in] position Position of the specificity
     * @param[in] classification Classification of the specificity
     */
    Specificity(const libaas::aminoAcids::RawAminoAcid& site,
        const Position position, const Classification classification);

    /**Convenience constructor.
     *
     * @param[in] site Site at which an event can happen
     * @param[in] position Position of the specificity
     * @param[in] classification Classification of the specificity
     * @throws Throws an exception if one of the given strings cannot be parsed
     * correctly.
     */
    Specificity(const libaas::String& site, const libaas::String& position,
        const libaas::String& classification);

    /**Sets the site.
     * @param[in] aminoAcid
     */
    void setSite(const libaas::aminoAcids::RawAminoAcid& aminoAcid);

    /**Returns the site.
     * @returns
     */
    const libaas::aminoAcids::RawAminoAcid& getSite() const;

    /**Sets the classification of the specificity.
     * @param[in] classification Classification
     */
    void setClassification(const Classification& classification);

    /**Returns the classification of the specificity
     * @returns The classification
     */
    const Classification& getClassification() const;

    /**Sets the position of the specificity.
     * @param[in] position Position
     */
    void setPosition(const Position& position);

    /**Returns the position of the specificity
     * @returns The position
     */
    const Position& getPosition() const;

    /**Adds a neutral loss.
     * @param[in] stoichiometry Stoichiometry of the neutral loss
     */
    void addNeutralLoss(const Stoichiometry& stoichiometry);

    /**Sets the list of neutral losses.
     * @param[in] stoichiometry List of stoichiometries
     */
    void setNeutralLosses(const std::vector<Stoichiometry>& stoichiometry);

    /**Returns the list of neutral losses.
     * @returns List of neutral losses
     */
    const std::vector<Stoichiometry>& getNeutralLosses() const;

    /**Clears the list of neutral losses.
     */
    void clearNeutralLosses();

    /**Adds a peptide neutral loss
     * @param[in] stoichiometry Stoichiometry of the peptide neutral loss
     */
    void addPepNeutralLoss(const Stoichiometry& stoichiometry);

    /**Sets the list of peptide neutral losses
     * @param[in] stoichiometries List of stoichiometries
     */
    void setPepNeutralLosses(
        const std::vector<Stoichiometry>& stoichiometries);

    /**Returns all peptide neutral losses.
     * @returns List of stoichiometries
     */
    const std::vector<Stoichiometry>& getPepNeutralLosses() const;

    /**Clears the list of peptide neutral losses.
     */
    void clearPepNeutralLosses();

    /**Sets the comment.
     * @param[in] comment Comment
     */
    void setComment(const String& comment);

    /**Returns the comment.
     * @returns The comment
     */
    const String& getComment() const;

    /**Checks whether this specificity matches the surrounding conditions of the
     * amino acid.
     * @param[in] prev Previous amino acid
     * @param[in] current Amino acid which should be modified with this
     * modification
     * @param[in] next Next amino acid
     * @returns true if the modification is applicable to the current amino acid,
     * false otherwise
     */
    Bool isApplicable(const libaas::aminoAcids::RawAminoAcid& prev,
        const libaas::aminoAcids::RawAminoAcid& current,
        const libaas::aminoAcids::RawAminoAcid& next) const;

    /**Sets a copy of the argument as the new content for the specificity object.
     * The previous content is dropped.
     * @param[in] rhs Specificity to copy
     * @returns *this
     */
    Specificity& operator=(const Specificity& rhs);

    /**Compares the specificity against another.
     * @param[in] s Specificity object to compare *this with
     * @returns true if both specificites are the same, false otherwise
     */
    bool operator==(const Specificity& s) const;

    /**Compares the specificity against another, with opposite result of
     * Specificity::operator==.
     * @param[in] s Specificity object to compare *this with
     * @returns true if the specificities are different, false otherwise.
     */
    bool operator!=(const Specificity& s) const;

    /**Converts the given string to lower case and tries to find the matching
     * enumeration.
     * @param[in] classification Classification string
     * @returns Classification
     * @throws Throws an exception if the given classification string does not
     * match any of the classification enumeration.
     */
    static Classification parseClassificationString(
        const libaas::String& classification);

    /**Converts the given string to lower case and tries to find the matching
     * position.
     * @param[in] position Position string
     * @returns Positions
     * @throws Throws an exception if the given position string does not match
     * any of the position enumerations.
     */
    static Position parsePositionString(const libaas::String& position);

private:

    /** Site at which an event can happen.
     */
    libaas::aminoAcids::RawAminoAcid site_;
    /** Position of the site.
     */
    Position position_;
    /** Classification of the specificity.
     */
    Classification classification_;
    /** List of possible neutral losses.
     */
    std::vector<Stoichiometry> neutralLosses_;
    /** List of possible peptide neutral losses.
     */
    std::vector<Stoichiometry> pepNeutralLosses_;
    /** A comment.
     */
    String comment_;

};
// class Specificity

std::ostream& operator<<(std::ostream&, const Specificity&);
std::ostream& operator<<(std::ostream&, const std::vector<Specificity>&);

} // namespace modifications
} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_SPECIFICITY_HPP__ */
