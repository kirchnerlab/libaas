/*
 * Modification.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_LIBAAS_MODIFICATION_HPP__
#define __LIBAAS_INCLUDE_LIBAAS_MODIFICATION_HPP__

#include <libaas/RawModification.hpp>
#include <libaas/Specificity.hpp>
#include <libaas/Stoichiometry.hpp>
#include <libaas/StoichiometryConfig.hpp>

#include <iostream>
#include <vector>

namespace libaas {
namespace modifications {

/**Representation of an amino acid modification.
 *
 * This class is a wrapper for a RawModification. Furthermore, it provides
 * function to add custom specificities which shadow the specificities of the
 * raw modification.
 */
class Modification {

public:

	/**Empty constructor to allow the instantiation of an empty modification.
	 * The default stoichiometry configuration will be used to calculate the
	 * stoichiometry.
	 */
	Modification();

	/**Constructor to create a new modification using the given raw
	 * modification.
	 * The default stoichiometry configuration is used to calculate the
	 * stoichiometry.
	 * @param[in] modification Modification
	 * @throws Throws an exception in case one ore more elements cannot be
	 * resolved by the stoichiometry configuration.
	 */
	Modification(const RawModification& modification);

	/**Constructor to create a new modification using the given id of a raw
	 * modification.
	 * The default stoichiometry configuration is used to calculate the
	 * stoichiometry.
	 * @param[in] modid Id of the modification
	 * @throws Throws an exception in case one ore more elements cannot be
	 * resolved by the stoichiometry configuration.
	 */
	Modification(const RawModificationImpl::RawModificationImplKeyType& modid);

	/**Constructor to create a new modification using the given raw
	 * modification and stoichiometry configuration.
	 * @param[in] modification Modification
	 * @param[in] config Stoichiometry configuration
	 * @throws Throws an exception in case one ore more elements cannot be
	 * resolved by the stoichiometry configuration.
	 */
	Modification(const RawModification& modification,
			const StoichiometryConfig& config);

	/**Constructor to create a new modification using the given id of a raw
	 * modification and id of a stoichiometry configuration.
	 * @param[in] modid
	 * @param[in] configid
	 * @throws Throws an exception in case one ore more elements cannot be
	 * resolved by the stoichiometry configuration.
	 */
	Modification(
			const RawModificationImpl::RawModificationImplKeyType& modid,
			const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid);

	/**Sets the raw modification.
	 * Note: This function will reset the custom specificities.
	 * @param[in] rawModification
	 */
	void setModification(const RawModification& rawModification);

	/**Sets the raw modification.
	 * Note: This function will reset the custom specificities.
	 * @param[in] modid Id of the raw modification
	 */
	void setModification(
			const RawModificationImpl::RawModificationImplKeyType& modid);

	/**Returns the raw modification.
	 * @returns The raw modification
	 */
	const RawModification& getModification() const;

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

	/**Returns the stoichiometry.
	 * @returns The stoichiometry of the modification
	 */
	const Stoichiometry& getStoichiometry() const;

	/**Adds a custom specificity.
	 * @param[in] specificity Specificity
	 */
	void addCustomSpecificitiy(const Specificity& specificity);

	/**Sets custom specificites.
	 * @param[in] specificities List of specificities used as custom specificites
	 */
	void setCustomSpecificities(const std::vector<Specificity>& specificities);

	/**Returns all custom specificities.
	 * @returns Custom specificities.
	 */
	const std::vector<Specificity> getCustomSpecificities() const;

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
	const std::vector<Specificity> getSpecificities() const;

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
	const Stoichiometry& getRawStoichiometry() const;

	/**Returns the specificities of the raw modification.
	 * @returns Specificities of the raw modification
	 */
	const std::vector<Specificity>& getRawSpecificities() const;

	/**Returns the status of the modification.
	 * @returns Status of the modification
	 */
	Bool isVerified() const;

	bool operator==(const Modification& s) const;
	bool operator!=(const Modification& s) const;
	Modification& operator=(const Modification& rhs);

private:

	/** Re-initializes the modification.
	 *
	 * A call of this function will reset the custom specificities and invokes
	 * the recalculation of the stoichiometry using the present stoichiometry
	 * configuration.
	 */
	void reinit();

	/** Recalculates the stoichiometry of the modification using the present
	 * stoichiometry configuration.
	 */
	void recalculateStoichiometry();

	RawModification modification_;
	StoichiometryConfig stoichiometryConfig_;
	libaas::Stoichiometry stoichiometry_;
	std::vector<Specificity> customSpecificities_;

};
// class Modification

std::ostream& operator<<(std::ostream&, const Modification&);

} // namespace modifications
} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_MODIFICATION_HPP__ */
