/*
 * AminoAcid.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/AminoAcid.hpp>

namespace libaas {
namespace aminoAcids {

Bool addAminoAcid(const AminoAcidImpl::AminoAcidImplKeyType& id,
        const Char symbol, const libaas::Stoichiometry& stoichiometry)
{
    AminoAcidImpl aminoAcid(id, symbol, stoichiometry);
    AminoAcid aminoAcid_r(aminoAcid);
    return aminoAcid_r == aminoAcid;
}

bool operator<(const AminoAcid& lhs, const AminoAcid& rhs)
{
    return lhs.get_key() < rhs.get_key();
}

bool operator<=(const AminoAcid& lhs, const AminoAcid& rhs)
{
    return lhs.get_key() <= rhs.get_key();
}

bool operator>(const AminoAcid& lhs, const AminoAcid& rhs)
{
    return lhs.get_key() > rhs.get_key();
}

bool operator>=(const AminoAcid& lhs, const AminoAcid& rhs)
{
    return lhs.get_key() >= rhs.get_key();
}

} // namespace aminoAcids
} // namespace libaas
