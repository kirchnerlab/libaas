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

#include <vector>
#include <iostream>

namespace libaas {
namespace modifications {

/** Specificity
 *
 */
class Specificity {

public:

    // TODO Connect to AminoAcidImpl?
    enum Position {
        PEPTIDE_N_TERM = 0,
        PEPTIDE_C_TERM,
        PROTEIN_N_TERM,
        PROTEIN_C_TERM,
        ANYWHERE
    };

    enum Classification {
        POST_TRANSLATIONAL = 0,
        MULTIPLE,
        CHEMICAL_DERIVATIVE,
        ARTEFACT,
        ISOTOPIC_LABEL,
        PRE_TRANSLATIONAL,
        OTHER_GLYCOSYLATION,
        N_LINKED_GLYCOSYLATION,
        AA_SUBSTITUTION,
        OTHER,
        NON_STANDARD_RESIDUE,
        CO_TRANSLATIONAL,
        O_LINKED_GLYCOSYLATION,
        SYNTH_PEP_PROTECT_GP
    };

    /** Constructor
     *
     */
    Specificity();

    bool operator==(const Specificity& s) const;
    //Specificity& operator=(const Specificity& rhs);

private:

    libaas::aminoAcids::AminoAcid site_;

    Classification classification_;
    Position position_;
    // can not find this in unimod
    //Stoichiometry deltaStoichiometry_;
    Stoichiometry neutralLoss_;
    //Int specGroup_;
    std::string comment_;
    //std::map<std::string, UnsignedInt> elementTableMap_;

}; // class Specificity

std::ostream& operator<<(std::ostream&, const Specificity&);
std::ostream& operator<<(std::ostream&, const std::vector<Specificity>&);

} // namespace modifications
} // namespace libaas

#endif /* __X_INCLUDE_X_SPECIFICITY_HPP__ */
