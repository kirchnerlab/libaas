/*
 * AminoAcidImpl.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __X_INCLUDE_X_AMINOACIDIMPL_HPP__
#define __X_INCLUDE_X_AMINOACIDIMPL_HPP__

#include <libaas/Stoichiometry.hpp>
#include <libaas/Types.hpp>

#include <iostream>

namespace libaas {
namespace aminoAcid {

/** AminoAcid
 *
 */
class AminoAcidImpl {

public:

    typedef Char AminoAcidImplKeyType;

    /** Constructor
     *
     */
    AminoAcidImpl(const AminoAcidImplKeyType& id);

    const AminoAcidImplKeyType& getId() const;
    Char getSymbol() const;
    const libaas::Stoichiometry& getStoichiometry() const;

    Bool isNTerm() const;
    Bool isCTerm() const;

    AminoAcidImpl& operator=(const AminoAcidImpl& a);
    bool operator==(const AminoAcidImpl& b) const;
    bool operator!=(const AminoAcidImpl& b) const;

    static const Char PEPTIDE_N_TERM;
    static const Char PROTEIN_N_TERM;
    static const Char PEPTIDE_C_TERM;
    static const Char PROTEIN_C_TERM;

private:

    AminoAcidImplKeyType id_;
    Char symbol_;
    libaas::Stoichiometry stoichiometry_;

}; // class AminoAcidImpl

std::ostream& operator<<(std::ostream&, const AminoAcidImpl&);
//istream& operator>>(std::istream&, AminoAcid&);

} // namespace aminoAcid
} // namespace libaas

#endif /* __X_INCLUDE_X_AMINOACIDIMPL_HPP__ */
