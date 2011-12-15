/*
 * Specificity.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2010,2011 Marc Kirchner
 * Copyright (c) 2010 Nathan Huesken
 *
 */

#ifndef __X_INCLUDE_X_SPECIFICITY_HPP__
#define __X_INCLUDE_X_SPECIFICITY_HPP__

#include <libaas/AminoAcid.hpp>
#include <libaas/Types.hpp>

#include <vector>
#include <iostream>

namespace libaas {
namespace modifications {

/** Specificity
 *
 */
class Specificity {

public:

    enum Position {
        PEPTIDE_N_TERM = 0,
        PEPTIDE_C_TERM,
        PROTEIN_N_TERM,
        PROTEIN_C_TERM,
        ANYWHERE
    };

    enum Classification {
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

    /** Constructor
     *
     */
    Specificity();

    Specificity(const libaas::String& site, const libaas::String& position, const libaas::String& classification);

    void setSite(const libaas::aminoAcids::AminoAcid& aminoAcid);
    const libaas::aminoAcids::AminoAcid& getSite() const;

    void setClassification(const Classification& classification);
    const Classification& getClassification() const;

    void setPosition(const Position& position);
    const Position& getPosition() const;

    void addNeutralLoss(const Stoichiometry& stoichiometry);
    void setNeutralLoss(const std::vector<Stoichiometry>& stoichiometry);
    const std::vector<Stoichiometry>& getNeutralLoss() const;

    void addPepNeutralLoss(const Stoichiometry& stoichiometry);
    void setPepNeutralLoss(const std::vector<Stoichiometry>& stoichiometry);
    const std::vector<Stoichiometry>& getPepNeutralLoss() const;

    void setComment(const String& comment);
    const String& getComment() const;

    bool operator==(const Specificity& s) const;
    //Specificity& operator=(const Specificity& rhs);

    static Classification parseClassificationString(const libaas::String& classification);
    static Position parsePositionString(const libaas::String& position);

private:

    libaas::aminoAcids::AminoAcid site_;

    Classification classification_;
    Position position_;
    std::vector<Stoichiometry> neutralLoss_;
    std::vector<Stoichiometry> pepNeutralLoss_;
    //Int specGroup_;
    String comment_;

}; // class Specificity

std::ostream& operator<<(std::ostream&, const Specificity&);
std::ostream& operator<<(std::ostream&, const std::vector<Specificity>&);

} // namespace modifications
} // namespace libaas

#endif /* __X_INCLUDE_X_SPECIFICITY_HPP__ */
