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

Bool addAminoAcid(const AminoAcidImpl::AminoAcidImplKeyType& id,
        const Char symbol, const libaas::Stoichiometry& stoichiometry)
{
    return addAminoAcid(AminoAcidImpl(id, symbol, stoichiometry));
}

Bool addAminoAcid(const AminoAcidImpl& aminoAcid) {
    AminoAcid aminoAcid_r(aminoAcid);
    // in case the key of the amino acid aminoAcid was already added or is a
    // standard amino acid which was retrieved earlier, the reference aminoAcid_r
    // will not contain the information as given in aminoAcid
    return aminoAcid == aminoAcid_r;
}

} // namespace aminoAcids
} // namespace libaas

