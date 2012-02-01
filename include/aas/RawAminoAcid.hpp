/*
 * RawAminoAcid.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_AAS_RAWAMINOACID_HPP__
#define __LIBAAS_INCLUDE_AAS_RAWAMINOACID_HPP__

#include <aas/RawAminoAcidImpl.hpp>
#include <aas/FlyWeightReplacement.hpp>

namespace aas {
namespace aminoAcids {

typedef aas::FlyWeightReplacement<RawAminoAcidImpl,
        RawAminoAcidImpl::RawAminoAcidImplKeyType> RawAminoAcid;

/**Convenience function to add a custom raw amino acid to this list of known amino
 * acids.
 * This methods calls addAminoAcid(RawAminoAcidImpl)
 * @param[in] id Key/Id of the amino acid
 * @param[in] symbol Symbol of the amino acid
 * @param[in] threeLetterCode Three letter code of the amino acid
 * @param[in] fullName Full name of the amino acid
 * @param[in] stoichiometry Stoichiometry of the amino acid
 * @returns True if the given amino acid is added correctly, false otherwise.
 */
Bool addRawAminoAcid(const RawAminoAcidImpl::RawAminoAcidImplKeyType& id,
    const Char symbol, const String& threeLetterCode, const String& fullName,
    const aas::Stoichiometry& stoichiometry);

/**Convenience function to add a custom raw amino acid to the list of known amino
 * acids.
 * Note: Once an amino acid is added it is not possible to alter its properties.
 * In order to change an internal property, you have to create a new amino acid
 * with the correct values.
 * IT IS NOT POSSIBLE TO OVERRIDE A REFERENCE (flyweight).
 * @param[in] aa Instance of an RawAminoAcidImpl
 * @returns True if the given amino acid is added correctly, false otherwise.
 */
Bool addRawAminoAcid(const RawAminoAcidImpl& aa);

bool operator<(const RawAminoAcid& lhs, const RawAminoAcid& rhs);
bool operator<=(const RawAminoAcid& lhs, const RawAminoAcid& rhs);
bool operator>(const RawAminoAcid& lhs, const RawAminoAcid& rhs);
bool operator>=(const RawAminoAcid& lhs, const RawAminoAcid& rhs);

} // namespace aminoAcids
} // namespace aas

#endif /* __LIBAAS_INCLUDE_AAS_RAWAMINOACID_HPP__ */
