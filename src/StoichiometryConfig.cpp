/*
 * StoichiometryConfig.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/StoichiometryConfig.hpp>

namespace libaas {

bool operator<(const StoichiometryConfig& lhs, const StoichiometryConfig& rhs)
{
    return lhs.get_key() < rhs.get_key();
}

bool operator<=(const StoichiometryConfig& lhs, const StoichiometryConfig& rhs)
{
    return lhs.get_key() <= rhs.get_key();
}

bool operator>(const StoichiometryConfig& lhs, const StoichiometryConfig& rhs)
{
    return lhs.get_key() > rhs.get_key();
}

bool operator>=(const StoichiometryConfig& lhs, const StoichiometryConfig& rhs)
{
    return lhs.get_key() >= rhs.get_key();
}

libaas::Bool addStoichiometryConfig(
    const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& id,
    const StoichiometryConfigImpl::DataType& map)
{
//    ElementConfig dec(ElementConfigImpl::DEFAULT_ELEMENT_CONFIG);
    StoichiometryConfigImpl ec(id);
    typedef StoichiometryConfigImpl::DataType::const_iterator IT;
    for (IT it = map.begin(); it != map.end(); ++it) {
        ec.insertElement(it->first, it->second);
    }
    return addStoichiometryConfig(ec);
}

libaas::Bool addStoichiometryConfig(
    const StoichiometryConfigImpl& stoichiometryConfig)
{
    return StoichiometryConfig(stoichiometryConfig) == stoichiometryConfig;
}

} // namespace libaas
