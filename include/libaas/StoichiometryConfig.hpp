/*
 * StoichiometryConfig.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_LIBAAS_STOICHIOMETRYCONFIG_HPP__
#define __LIBAAS_INCLUDE_LIBAAS_STOICHIOMETRYCONFIG_HPP__

#include <libaas/StoichiometryConfigImpl.hpp>
#include <libaas/Types.hpp>

#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/flyweight/no_tracking.hpp>

namespace libaas {

/**@brief ID extractor for stoichiometry configurations.
 *
 * The class StoichiometryConfigIdExtractor is used allow the instantiation of
 * flyweight<StoichiometryConfigImpl>(Key) in order to simplify the access.
 */
struct StoichiometryConfigIdExtractor
{
    /**Returns the key of the stoichiometry configuration.
     * @param[in] e instance of a stoichiometry configuration implementation
     * @returns The key of the stoichiometry configuration
     */
    const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& operator()(
        const StoichiometryConfigImpl& e) const
    {
        return e.getId();
    }
};

/**Typedef to simplify the data type flyweight<StoichiometryConfigImpl>
 */
typedef boost::flyweight<
        boost::flyweights::key_value<
                StoichiometryConfigImpl::StoichiometryConfigImplKeyType,
                StoichiometryConfigImpl, StoichiometryConfigIdExtractor>
        , boost::flyweights::no_tracking> StoichiometryConfig;

/**Convenience function to add a custom stoichiometry configuration to the list of
 * known stoichiometry configurations.
 * This method creates a StoichiometryConfigImpl and calls
 * addStoichiometryConfig(stoichiometryConfig) to add it.
 * @param[in] id Key/Id of the stoichiometry configuration
 * @param[in] map Mapping of an element symbol to an element id
 * @returns True if the given amino acid is added correctly, false otherwise.
 */
libaas::Bool
addStoichiometryConfig(
    const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& id,
    const StoichiometryConfigImpl::DataType& map);

/**Convenience function to add a custom stoichiometry configuration to the list of
 * known stoichiometry configurations.
 * Note: Once a configuration is added it is not possible to alter its properties.
 * In order to change an internal property, you have to create a new amino acid
 * with the correct values.
 * @param[in] stoichiometryConfig Stoichiometry configuration
 * @returns True if the given amino acid is added correctly, false otherwise.
 */
libaas::Bool addStoichiometryConfig(
    const StoichiometryConfigImpl& stoichiometryConfig);

bool operator<(const StoichiometryConfig& lhs, const StoichiometryConfig& rhs);
bool operator<=(const StoichiometryConfig& lhs,
    const StoichiometryConfig& rhs);
bool operator>(const StoichiometryConfig& lhs, const StoichiometryConfig& rhs);
bool operator>=(const StoichiometryConfig& lhs,
    const StoichiometryConfig& rhs);

} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_STOICHIOMETRYCONFIG_HPP__ */
