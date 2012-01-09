/*
 * AminoAcid.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_LIBAAS_AMINOACID_HPP__
#define __LIBAAS_INCLUDE_LIBAAS_AMINOACID_HPP__

#include <libaas/RawAminoAcid.hpp>
#include <libaas/StoichiometryConfig.hpp>
#include <libaas/Stoichiometry.hpp>

#include <iostream>

namespace libaas {
namespace aminoAcids {

class AminoAcid {
public:

	AminoAcid(
			const RawAminoAcidImpl::RawAminoAcidImplKeyType& aminoAcidKey = '\0',
			const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid =
					StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG);
	AminoAcid(
			const RawAminoAcid& aminoAcid,
			const StoichiometryConfig& config = StoichiometryConfig(
					StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG));

	Char getSymbol() const;

	const RawAminoAcidImpl::RawAminoAcidImplKeyType& getRawAminoAcidKey() const;

	const RawAminoAcid& getRawAminoAcid() const;

	/**Returns the three letter code of the amino acid.
	 * @return The three letter code of the amino acid
	 */
	const String& getThreeLetterCode() const;

	/**Returns the full name of the amino acid.
	 * @returns The full name of the amino acid
	 */
	const String& getFullName() const;

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

	Stoichiometry getStoichiometry() const;

	/**Sets the stoichiometry configuration.
	 * Note: This will trigger the recalculation of the stoichiometry using the
	 * given configuration.
	 * @param[in] config Stoichiometry configuration
	 * @throws Throws an exception in case one ore more elements cannot be
	 * resolved by the stoichiometry configuration.
	 */
	void setStoichiometryConfig(const StoichiometryConfig& config);

	/**Sets the stoichiometry configuration.
	 * Note: This will trigger the recalculation of the stoichiometry using the
	 * given configuration.
	 * @param[in] configid Id of the stoichiometry configuration
	 * @throws Throws an exception in case one ore more elements cannot be
	 * resolved by the stoichiometry configuration.
	 */
	void
	setStoichiometryConfig(
			const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid);

	/**Returns the stoichiometry configuration.
	 * @returns Stoichiometry configuration
	 */
	const StoichiometryConfig& getStoichiometryConfig() const;

	/**Sets a copy of the argument as the new content for the amino acid object.
	 * The previous content is dropped.
	 * @param[in] a Amino acid to copy
	 * @returns *this
	 */
	AminoAcid& operator=(const AminoAcid& a);

	/**Compares the amino acid against another.
	 * @param[in] a Amino acid object to compare *this with
	 * @returns true if both amino acids are the same, false otherwise
	 */
	bool operator==(const AminoAcid& a) const;

	/**Compares the amino acid against another, with opposite result of
	 * RawAminoAcidImpl::operator==.
	 * @param[in] a Amino acid object to compare *this with
	 * @returns true if the amino acids are different, false otherwise.
	 */
	bool operator!=(const AminoAcid& a) const;

private:

	/**Recalculates the stoichiometry of the modification using the present
	 * stoichiometry configuration.
	 */
	void recalculateStoichiometry();

	RawAminoAcid rawAminoAcid_;
	StoichiometryConfig stoichiometryConfig_;
	Stoichiometry stoichiometry_;

};

std::ostream& operator<<(std::ostream& os, const AminoAcid& a);

} // namespace aminoAcids
} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_AMINOACID_HPP__ */
