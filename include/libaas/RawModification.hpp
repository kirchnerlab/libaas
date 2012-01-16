/*
 * RawModification.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_LIBAAS_RAWMODIFICATION_HPP__
#define __LIBAAS_INCLUDE_LIBAAS_RAWMODIFICATION_HPP__

#include <libaas/RawModificationImpl.hpp>

#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/flyweight/no_tracking.hpp>

namespace libaas {
namespace modifications {

/**@brief ID extrator for raw modifications.
 *
 * The class RawModificationIdExtractor is used allow the instantiation of
 * flyweight<RawModificationImpl>(Key) in order to simplify the access.
 */
struct RawModificationIdExtractor
{
    /**Returns the key of the raw modification.
     * @param[in] m instance of a raw modification implementation
     * @returns The key of the raw modification
     */
    const RawModificationImpl::RawModificationImplKeyType& operator()(
        const RawModificationImpl& m) const
    {
        return m.getId();
    }
};

/**Typedef to simplify the data type flyweight<RawModificationImpl>
 */
typedef boost::flyweight<
        boost::flyweights::key_value<
                RawModificationImpl::RawModificationImplKeyType,
                RawModificationImpl, RawModificationIdExtractor>
        , boost::flyweights::no_tracking> RawModification;

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
libaas::Bool addRawModification(
    const RawModificationImpl::RawModificationImplKeyType& id,
    const libaas::String& name, const libaas::String& fullname,
    const std::vector<String>& altNames, const Stoichiometry& stoichiometry,
    const std::vector<Specificity>& specificities,
    const libaas::Bool& verified);

/**Convenience function to add a custom raw modification to the list of known
 * raw modifications.
 * Note: Once an amino acid is added it is not possible to alter its properties.
 * In order to change an internal property, you have to create a new amino acid
 * with the correct values.
 * IT IS NOT POSSIBLE TO OVERRIDE A REFERENCE (flyweight).
 * @param[in] rawModification Instance of a RawModificationImpl
 * @returns True if the given raw modification is added correctly, false otherwise.
 */
libaas::Bool addRawModification(const RawModificationImpl& rawModification);

bool operator<(const RawModification& lhs, const RawModification& rhs);
bool operator<=(const RawModification& lhs, const RawModification& rhs);
bool operator>(const RawModification& lhs, const RawModification& rhs);
bool operator>=(const RawModification& lhs, const RawModification& rhs);

} // namespace modifications
} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_RAWMODIFICATION_HPP__ */
