/*
 * AminoAcidImpl.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_LIBAAS_AMINOACIDIMPL_HPP__
#define __LIBAAS_INCLUDE_LIBAAS_AMINOACIDIMPL_HPP__

#include <libaas/Stoichiometry.hpp>
#include <libaas/Types.hpp>

#include <iostream>

namespace libaas {
namespace aminoAcids {

/**Representation of an amino acid.
 *
 * This class only represents the amino acid without its modifications.
 * Furthermore, this class is usually not used directly, since the appropriate
 * flyweight AminoAcid provides the necessary constructors and functions to
 * use amino acids in a memory friendly manner.
 */
class AminoAcidImpl {

public:

    /**Convenience typedef for the key type.
     */
    typedef Char AminoAcidImplKeyType;

    /**Default constructor to create a standard amino acid.
     * In order to create a custom amino acid, use
     * AminoAcidImpl(id, symbol, stoichiometry).
     *
     * This constructor has access to static variables containing all
     * information necessary to create and fill the internal variables.
     *
     * @param[in] id Key/Id of the amino acid.
     * @throws Throws an exception in case the id is not in the list of standart
     * amino acids.
     */
    AminoAcidImpl(const AminoAcidImplKeyType& id);

    /**Cosntructor to create a custom amino acid.
     * @param[in] id Key/Id of the amino acid
     * @param[in] symbol Symbol of the amino acid
     * @param[in] stoichiometry Stoichiometry of the amino acid
     */
    AminoAcidImpl(const AminoAcidImplKeyType& id, const char symbol,
            const libaas::Stoichiometry& stoichiometry);

    /**Returns the key of the amino acid.
     * @returns Key of the amino acid.
     */
    const AminoAcidImplKeyType& getId() const;

    /**Returns the symbol of the amino acid
     * @returns Symbol of the amino acid.
     */
    Char getSymbol() const;

    /**Returns the stoichiometry of the amino acid.
     * @returns stoichiometry of the amino acid.
     */
    const libaas::Stoichiometry& getStoichiometry() const;

    /**
     * @returns True if the amino acid is AminoAcidImpl::PEPTIDE_N_TERM or
     * AminoAcidImpl::PROTEIN_N_TERM.
     */
    Bool isNTerm() const;

    /**
     * @returns True if the amino acid is AminoAcidImpl::PEPTIDE_C_TERM or
     * AminoAcidImpl::PEPTIDE_N_TERM.
     */
    Bool isCTerm() const;

    AminoAcidImpl& operator=(const AminoAcidImpl& a);
    bool operator==(const AminoAcidImpl& b) const;
    bool operator!=(const AminoAcidImpl& b) const;

    /** Key for the artificial peptide N-term amino acid.
     */
    static const Char PEPTIDE_N_TERM;
    /** Key for the artificial protein N-term amino acid.
     */
    static const Char PROTEIN_N_TERM;
    /** Key for the artificial peptide C-term amino acid.
     */
    static const Char PEPTIDE_C_TERM;
    /** Key for the artificial protein C-term amino acid.
     */
    static const Char PROTEIN_C_TERM;

    /**Returns the corresponding key of the amino acid string aminoAcid. The
     * string can contain the one-letter code, three-letter code (niy) and full
     * name (niy) of the amino acid.
     * TODO implement 3-letter, full name identification
     * @param[in] aminoAcid String representing the amino acid.
     * @returns Corresponding key of the amino acid with the string aminoAcid
     * @throws Throws an exception if the given amino acid string is not in the
     * list of standard amino acids.
     */
    static AminoAcidImplKeyType getKeyForAminoAcidString(
            const libaas::String& aminoAcid);

private:

    AminoAcidImplKeyType id_;
    Char symbol_;
    libaas::Stoichiometry stoichiometry_;

}; // class AminoAcidImpl

std::ostream& operator<<(std::ostream&, const AminoAcidImpl&);

inline const AminoAcidImpl::AminoAcidImplKeyType& AminoAcidImpl::getId() const
{
    return id_;
}

} // namespace aminoAcids
} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_AMINOACIDIMPL_HPP__ */
