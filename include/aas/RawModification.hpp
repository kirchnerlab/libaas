/*
 * RawModification.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_AAS_RAWMODIFICATION_HPP__
#define __LIBAAS_INCLUDE_AAS_RAWMODIFICATION_HPP__

#include <aas/RawModificationImpl.hpp>
#include <aas/FlyWeightReplacement.hpp>

namespace aas {
namespace modifications {

typedef aas::FlyWeightReplacement<RawModificationImpl, RawModificationImpl::RawModificationImplKeyType> RawModification;

/**Convenience function to add a custom raw modification to the list of known
 * raw modifications.
 * @param[in] id Key/Id of the raw modification
 * @param[in] name Name of the raw modification
 * @param[in] fullName Full name (description) of the raw modification
 * @param[in] altNames Alternative names of the raw modification
 * @param[in] stoichiometry Stoichiometry of the modification
 * @param[in] specificities specificities of the modification
 * @param[in] verified Raw modification is verified
 * @returns True if the given raw modification is added correctly, false otherwise.
 */
aas::Bool addRawModification(
    const RawModificationImpl::RawModificationImplKeyType& id,
    const aas::String& name, const aas::String& fullname,
    const std::vector<String>& altNames, const Stoichiometry& stoichiometry,
    const std::vector<Specificity>& specificities, const aas::Bool& verified);

/**Convenience function to add a custom raw modification to the list of known
 * raw modifications.
 * Note: Once an amino acid is added it is not possible to alter its properties.
 * In order to change an internal property, you have to create a new amino acid
 * with the correct values.
 * IT IS NOT POSSIBLE TO OVERRIDE A REFERENCE (flyweight).
 * @param[in] rawModification Instance of a RawModificationImpl
 * @returns True if the given raw modification is added correctly, false otherwise.
 */
aas::Bool addRawModification(const RawModificationImpl& rawModification);

bool operator<(const RawModification& lhs, const RawModification& rhs);
bool operator<=(const RawModification& lhs, const RawModification& rhs);
bool operator>(const RawModification& lhs, const RawModification& rhs);
bool operator>=(const RawModification& lhs, const RawModification& rhs);

} // namespace modifications
} // namespace aas

#endif /* __LIBAAS_INCLUDE_AAS_RAWMODIFICATION_HPP__ */
