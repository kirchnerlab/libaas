/*
 * Modification.hpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_AAS_MODIFICATION_HPP__
#define __LIBAAS_INCLUDE_AAS_MODIFICATION_HPP__

#include "aas/RawModification.hpp"
#include "aas/AminoAcid.hpp"
#include "aas/Specificity.hpp"
#include "aas/Stoichiometry.hpp"
#include "aas/StoichiometryConfig.hpp"

#include <iostream>
#include <vector>

namespace aas {

namespace modifications {

/**Representation of an amino acid modification.
 *
 * This class is a wrapper for a RawModification. Furthermore, it provides
 * function to add custom specificities which shadow the specificities of the
 * raw modification.
 */
class Modification
{

public:

    /**Constructor to create a new modification using the given raw
     * modification and stoichiometry configuration.
     * @param[in] modification Modification
     * @param[in] config Stoichiometry configuration
     */
    Modification(
        const RawModification& modification,
        const aas::stoichiometries::StoichiometryConfig& config = aas::stoichiometries::StoichiometryConfig(
            aas::stoichiometries::StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG));

    /**Constructor to create a new modification using the given id of a raw
     * modification and id of a stoichiometry configuration.
     * @param[in] modid
     * @param[in] configid
     * @throws Throws an aas::errors::LogicError exception in case the given
     * modification key cannot be resolved.
     */
    Modification(
        const RawModificationImpl::RawModificationImplKeyType& modid = "",
        const aas::stoichiometries::StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid =
                aas::stoichiometries::StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG);

    /**Sets the raw modification.
     * Note: This function will reset the custom specificities.
     * @param[in] rawModification
     */
    void setModification(const RawModification& rawModification);

    /**Sets the raw modification.
     * Note: This function will reset the custom specificities.
     * @param[in] modid Id of the raw modification
     * @throws Throws an aas::errors::LogicError exception in case the modid cannot be
     * resolved.
     */
    void setModification(
        const RawModificationImpl::RawModificationImplKeyType& modid);

    /**Returns the raw modification.
     * @returns The raw modification
     */
    const RawModification& getModification() const;

    /**Sets the stoichiometry configuration.
     * @param[in] config Stoichiometry configuration
     */
    void setStoichiometryConfig(const aas::stoichiometries::StoichiometryConfig& config);

    /**Sets the stoichiometry configuration.
     * @param[in] configid Id of the stoichiometry configuration
     */
    void
    setStoichiometryConfig(
        const aas::stoichiometries::StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid);

    /**Returns the stoichiometry configuration.
     * @returns Stoichiometry configuration
     */
    const aas::stoichiometries::StoichiometryConfig& getStoichiometryConfig() const;

    /**Calculates and returns a copy of the stoichiometry of this amino acid.
     * The calculation is skipped in case the present stoichiometry configuration is
     * StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG.
     * This method calls recalculatesWithConfiguration() on the stoichiometry retrieved
     * by the raw amino acid.
     * @returns The stoichiometry calculated with the present stoichiometry configuration
     * @throws Throws an aas::errors::RuntimeError in case one or more elements cannot
     * be resolved by the stochiometry config.
     */
    aas::stoichiometries::Stoichiometry getStoichiometry() const;

    /**Adds a custom specificity.
     * @param[in] specificity Specificity
     */
    void addCustomSpecificity(const Specificity& specificity);

    /**Sets custom specificites.
     * @param[in] specificities List of specificities used as custom specificites
     */
    void setCustomSpecificities(const std::vector<Specificity>& specificities);

    /**Returns all custom specificities.
     * @returns Custom specificities.
     */
    const std::vector<Specificity>& getCustomSpecificities() const;

    /**Clears the list of custom specificities.
     */
    void clearCustomSpecificities();

    /**Returns a list of active specificities.
     *
     * If the list of custom specificities is empty the specificities of the
     * raw modification are returned.
     *
     * @returns List of specificities
     */
    const std::vector<Specificity>& getSpecificities() const;

    /**Returns the key/id of the modification.
     * @returns Id of the modification
     */
    const RawModificationImpl::RawModificationImplKeyType
    & getModificationId() const;

    /**Returns the name of the modification.
     * @returns Name of the modification
     */
    const String& getName() const;

    /**Returns the full name (description) of the modification.
     * @returns Full name (description) of the modification
     */
    const String& getFullName() const;

    /**Returns the alternative names of the modification
     * @returns alternative names of the modification
     */
    const std::vector<String>& getAltNames() const;

    /**Returns the stoichiometry of the raw modification.
     * @returns Stoichiometry of the raw modification
     */
    const aas::stoichiometries::Stoichiometry& getRawStoichiometry() const;

    /**Returns the specificities of the raw modification.
     * @returns Specificities of the raw modification
     */
    const std::vector<Specificity>& getRawSpecificities() const;

    /**Checks whether this modification is used as an isotopic label.
     *
     * @returns true if one of the specificities returned by getSpecificities
     * is a "aas::modifications::Specificity::ISOTOPIC_LABEL", false otherwise
     */
    Bool isIsotopicLabel() const;

    /**Returns the status of the modification.
     * @returns Status of the modification
     */
    Bool isVerified() const;

    /**Checks whether this modification is applicable to the amino acid current.
     *
     * In case no custom specificities are set, the specificities of the raw
     * modification are used, otherwise only the custom specificities are taken
     * into account.
     *
     * @param[in] prev Previous amino acid
     * @param[in] current Amino acid which should be modified with this
     * modification
     * @param[in] next Next amino acid
     * @returns true if the modification is applicable to the current amino acid,
     * false otherwise
     */
    Bool isApplicable(const aminoAcids::AminoAcid& prev,
        const aminoAcids::AminoAcid& current,
        const aminoAcids::AminoAcid& next) const;

    /**Sets a copy of the argument as the new content for the modification object.
     * The previous content is dropped.
     * @param[in] rhs Modification to copy
     * @returns *this
     */
    Modification& operator=(const Modification& rhs);

    /**Compares the modification against another.
     * @param[in] m Modification object to compare *this with
     * @returns true if both modifications are the same, false otherwise
     */
    bool operator==(const Modification& m) const;

    /**Compares the modification against another, with opposite result of
     * Modification::operator==.
     * @param[in] m Modification object to compare *this with
     * @returns true if the modifications are different, false otherwise.
     */
    bool operator!=(const Modification& m) const;

private:

    /**Object of the raw modification.
     */
    RawModification rawModification_;

    /**Stoichiometry configuration used to calculate the stoichiometry.
     */
    aas::stoichiometries::StoichiometryConfig stoichiometryConfig_;

    /**Custom specificities of the modification.
     */
    std::vector<Specificity> customSpecificities_;

};
// class Modification

std::ostream& operator<<(std::ostream&, const Modification&);

} // namespace modifications
} // namespace aas

#endif /* __LIBAAS_INCLUDE_AAS_MODIFICATION_HPP__ */
