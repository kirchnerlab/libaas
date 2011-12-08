/*
 * AminoAcidImpl.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 *
 */

#ifndef __X_INCLUDE_X_AMINOACIDIMPL_HPP__
#define __X_INCLUDE_X_AMINOACIDIMPL_HPP__

#include <libaas/Stoichiometry.hpp>

#include <iostream>

namespace libaas {

/** AminoAcid
 *
 */
class AminoAcidImpl {

public:

    typedef char AminoAcidImplKeyType;

    /** Constructor
     *
     */
    AminoAcidImpl(const AminoAcidImplKeyType& id);

    const AminoAcidImplKeyType& getId() const;
    const char& getSymbol() const;
    const libaas::Stoichiometry& getStoichiometry() const;

    bool isNTerm() const;
    bool isCTerm() const;

    AminoAcidImpl& operator=(const AminoAcidImpl& a);
    bool operator==(const AminoAcidImpl& b) const;
    bool operator!=(const AminoAcidImpl& b) const;

    static const char PEPTIDE_N_TERM;
    static const char PROTEIN_N_TERM;
    static const char PEPTIDE_C_TERM;
    static const char PROTEIN_C_TERM;

private:

    AminoAcidImplKeyType id_;
    char symbol_;
    libaas::Stoichiometry stoichiometry_;

}; // class AminoAcidImpl

std::ostream& operator<<(std::ostream&, const AminoAcidImpl&);
//istream& operator>>(std::istream&, AminoAcid&);

} // namespace libaas

#endif /* __X_INCLUDE_X_AMINOACIDIMPL_HPP__ */
