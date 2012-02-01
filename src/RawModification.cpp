/*
 * RawModification.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include "aas/RawModification.hpp"

namespace aas {
namespace modifications {

aas::Bool addRawModification(
    const RawModificationImpl::RawModificationImplKeyType& id,
    const aas::String& name, const aas::String& fullName,
    const std::vector<String>& altNames, const aas::stoichiometries::Stoichiometry& stoichiometry,
    const std::vector<Specificity>& specificities, const aas::Bool& verified)
{
    RawModificationImpl rm(id, name, fullName, verified);
    rm.setAltNames(altNames);
    rm.setStoichiometry(stoichiometry);
    rm.setSpecificities(specificities);
    return addRawModification(rm);
}

aas::Bool addRawModification(const RawModificationImpl& rawModification)
{
    return RawModification(rawModification) == rawModification;
}

bool operator<(const RawModification& lhs, const RawModification& rhs)
{
    return lhs.get_key() < rhs.get_key();
}

bool operator<=(const RawModification& lhs, const RawModification& rhs)
{
    return lhs.get_key() <= rhs.get_key();
}

bool operator>(const RawModification& lhs, const RawModification& rhs)
{
    return lhs.get_key() > rhs.get_key();
}

bool operator>=(const RawModification& lhs, const RawModification& rhs)
{
    return lhs.get_key() >= rhs.get_key();
}

} // namespace modifications
} // namespace aas
