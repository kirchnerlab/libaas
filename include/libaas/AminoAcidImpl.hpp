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

	/**Sets the symbol of the amino acid.
	 * @param[in] symbol Symbol of the amino acid
	 */
	void setSymbol(const Char& symbol);

	/**Returns the symbol of the amino acid
	 * @returns Symbol of the amino acid.
	 */
	Char getSymbol() const;

	/**Sets the stoichiometry of the amino acid.
	 * @param[in] stoichiometry Stoichiometry of the amino acid
	 */
	void setStoichiometry(const Stoichiometry& stoichiometry);

	/**Returns the stoichiometry of the amino acid.
	 * @returns stoichiometry of the amino acid.
	 */
	const libaas::Stoichiometry& getStoichiometry() const;

	/**Sets the three letter code for the amino acid.
	 * @param[in] threeLetterCode The three letter code of the amino acid
	 */
	void setThreeLetterCode(const String& threeLetterCode);

	/**Returns the three letter code of the amino acid.
	 * @return The three letter code of the amino acid
	 */
	const String& getThreeLetterCode() const;

	/**Sets the full name of the amino acid.
	 * @param[in] fullName Full name of the amino acid
	 */
	void setFullName(const String& fullName);

	/**Returns the full name of the amino acid.
	 * @returns The full name of the amino acid
	 */
	const String& getFullName() const;

	/**Checks whether the amino acid is N-terminal.
	 * @returns True if the amino acid is AminoAcidImpl::PEPTIDE_N_TERM or
	 * AminoAcidImpl::PROTEIN_N_TERM.
	 */
	Bool isNTerm() const;

	/**Checks whether the amino acid is C-terminal.
	 * @returns True if the amino acid is AminoAcidImpl::PEPTIDE_C_TERM or
	 * AminoAcidImpl::PEPTIDE_C_TERM.
	 */
	Bool isCTerm() const;

	/**Sets a copy of the argument as the new content for the amino acid object.
	 * The previous content is dropped.
	 * @param[in] a Amino acid to copy
	 * @returns *this
	 */
	AminoAcidImpl& operator=(const AminoAcidImpl& a);

	/**Compares the amino acid against another.
	 * @param[in] a Amino acid object to compare *this with
	 * @returns true if both amino acids are the same, false otherwise
	 */
	bool operator==(const AminoAcidImpl& a) const;

	/**Compares the amino acid against another, with opposite result of
	 * AminoAcidImpl::operator==.
	 * @param[in] a Amino acid object to compare *this with
	 * @returns true if the amino acids are different, false otherwise.
	 */
	bool operator!=(const AminoAcidImpl& a) const;

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
	 * string can contain the one-letter code, three-letter code and full
	 * name of the amino acid.
	 * @param[in] aminoAcid String representing the amino acid.
	 * @returns Corresponding key of the amino acid with the string aminoAcid
	 * @throws Throws an exception if the given amino acid string is not in the
	 * list of standard amino acids.
	 */
	static AminoAcidImplKeyType getKeyForAminoAcidString(
			const libaas::String& aminoAcid);

private:

	/** Key/Id of the amino acid.
	 */
	AminoAcidImplKeyType id_;
	/** One letter symbol of the amino acid.
	 */
	Char symbol_;
	/** Three letter code of the amino acid.
	 */
	libaas::String threeLetterCode_;
	/** Full name of the amino acid.
	 */
	libaas::String fullName_;
	/** Stoichiometry of the amino acid.
	 */
	libaas::Stoichiometry stoichiometry_;

};
// class AminoAcidImpl

std::ostream& operator<<(std::ostream&, const AminoAcidImpl&);

inline const AminoAcidImpl::AminoAcidImplKeyType& AminoAcidImpl::getId() const {
	return id_;
}

} // namespace aminoAcids
} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_AMINOACIDIMPL_HPP__ */
