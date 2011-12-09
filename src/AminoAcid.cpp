/*
 * AminoAcid.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/AminoAcid.hpp>

namespace libaas {
namespace aminoAcid {

// TODO it might be enough to define operator<... for AminoAcid since the
// implicit conversion from fw<AminoAcid> -> const AminoAcid& should solve the
// map<fw<AminoAcid>> stuff

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

} // namespace aminoAcid
} // namespace libaas
