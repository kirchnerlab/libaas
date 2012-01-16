/*
 * RawAminoAcid.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/RawAminoAcid.hpp>

namespace libaas {
namespace aminoAcids {

bool operator<(const RawAminoAcid& lhs, const RawAminoAcid& rhs)
{
    return lhs.get_key() < rhs.get_key();
}

bool operator<=(const RawAminoAcid& lhs, const RawAminoAcid& rhs)
{
    return lhs.get_key() <= rhs.get_key();
}

bool operator>(const RawAminoAcid& lhs, const RawAminoAcid& rhs)
{
    return lhs.get_key() > rhs.get_key();
}

bool operator>=(const RawAminoAcid& lhs, const RawAminoAcid& rhs)
{
    return lhs.get_key() >= rhs.get_key();
}

Bool addRawAminoAcid(const RawAminoAcidImpl::RawAminoAcidImplKeyType& id,
    const Char symbol, const String& threeLetterCode, const String& fullName,
    const libaas::Stoichiometry& stoichiometry)
{
    RawAminoAcidImpl aa(id, symbol, stoichiometry);
    aa.setThreeLetterCode(threeLetterCode);
    aa.setFullName(fullName);
    return addRawAminoAcid(aa);
}

Bool addRawAminoAcid(const RawAminoAcidImpl& aminoAcid)
{
    RawAminoAcid aminoAcid_r(aminoAcid);
    // in case the key of the amino acid aminoAcid was already added or is a
    // standard amino acid which was retrieved earlier, the reference aminoAcid_r
    // will not contain the information as given in aminoAcid
    return aminoAcid == aminoAcid_r;
}

} // namespace aminoAcids
} // namespace libaas

