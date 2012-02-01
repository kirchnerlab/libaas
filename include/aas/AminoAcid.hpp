/*
 * AminoAcid.hpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2011,2012 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_AAS_AMINOACID_HPP__
#define __LIBAAS_INCLUDE_AAS_AMINOACID_HPP__

#include "aas/RawAminoAcid.hpp"
#include "aas/StoichiometryConfig.hpp"
#include "aas/Stoichiometry.hpp"

#include <iostream>

namespace aas {
namespace aminoAcids {

/**Representation of an amino acid using aas::aminoAcids::RawAminoAcid.
 */
class AminoAcid
{
public:

    /**Constructor.
     * @param[in] aminoAcidKey The key/id of the raw amino acid
     * @param[in] configid The stoichiometry config key/id
     * @throws Throwsn an aas::errors::LogicError exception in case the given amino
     * acid key cannot be resolved.
     */
    AminoAcid(
        const RawAminoAcidImpl::RawAminoAcidImplKeyType& aminoAcidKey = '\0',
        const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid =

        StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG);

    /**Constructor.
     * @param[in] aminoAcid The raw amino acid
     * @param[in] config The stoichiometry config which is used to calculate the
     * stoichiometry
     */
    AminoAcid(
        const RawAminoAcid& aminoAcid,
        const StoichiometryConfig& config = StoichiometryConfig(
            StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG));

    /**Returns the symbol of the amino acid.
     * @returns The symbol of the amino acid.
     */
    Char getSymbol() const;

    /**Returns the key/id of the raw amino acid.
     * @returns The key/id of the raw amino acid.
     */
    const RawAminoAcidImpl::RawAminoAcidImplKeyType& getRawAminoAcidKey() const;

    /**Returns the raw amino acid.
     * @returns The raw amino acid.
     */
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
    aas::Bool isNTerm() const;

    /**Checks whether the amino acid is C-terminal.
     * @returns True if the amino acid is AminoAcidImpl::PEPTIDE_C_TERM or
     * AminoAcidImpl::PEPTIDE_C_TERM.
     */
    aas::Bool isCTerm() const;

    /**Calculates and returns a copy of the stoichiometry of this amino acid.
     * The calculation is skipped in case the present stoichiometry configuration is
     * StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG.
     * This method calls recalculatesWithConfiguration() on the stoichiometry retrieved
     * by the raw amino acid.
     * @returns The stoichiometry calculated with the present stoichiometry configuration
     * @throws Throws an aas::errors::RuntimeError in case one or more elements cannot
     * be resolved by the stochiometry config.
     */
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

    /**The raw amino acid.
     */
    RawAminoAcid rawAminoAcid_;
    /**The stoichiometry configuration used to calculate the stoichiometry.
     */
    StoichiometryConfig stoichiometryConfig_;

};

std::ostream& operator<<(std::ostream& os, const AminoAcid& a);

} // namespace aminoAcids
} // namespace aas

#endif /* __LIBAAS_INCLUDE_AAS_AMINOACID_HPP__ */
