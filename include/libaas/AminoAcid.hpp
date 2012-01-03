/*
 * AminoAcid.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_LIBAAS_AMINOACID_HPP__
#define __LIBAAS_INCLUDE_LIBAAS_AMINOACID_HPP__

#include <libaas/AminoAcidImpl.hpp>

#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/flyweight/no_tracking.hpp>

namespace libaas {
namespace aminoAcids {

/**@brief ID extractor for amino acids.
 *
 * The class AminoAcidIdExtractor is used allow the instantiation of
 * flyweight<AminoAcidImpl>(Key) in order to simplify the access.
 */
struct AminoAcidIdExtractor {
    /**Returns the key of the amino acid.
     * @param[in] a instance of an amino acid implementation
     * @returns The key of the amino acid
     */
	const AminoAcidImpl::AminoAcidImplKeyType& operator()(
			const AminoAcidImpl& a) const {
		return a.getId();
	}
};

/**Typedef to simplify the data type flyweight<AminoAcidImpl>
 */
typedef boost::flyweight<
		boost::flyweights::key_value<AminoAcidImpl::AminoAcidImplKeyType,
				AminoAcidImpl, AminoAcidIdExtractor>
		, boost::flyweights::no_tracking> AminoAcid;

/**Convenience function to add a custom amino acid to this list of known amino
 * acids.
 * This methods calls addAminoAcid(AminoAcidImpl)
 * @param[in] id Key/Id of the amino acid
 * @param[in] symbol Symbol of the amino acid
 * @param[in] stoichiometry Stoichiometry of the amino acid
 * @returns True if the given amino acid is added correctly, false otherwise.
 */
Bool addAminoAcid(const AminoAcidImpl::AminoAcidImplKeyType& id,
		const Char symbol, const libaas::Stoichiometry& stoichiometry);

/**Convenience function to add a custom amino acid to the list of known amino
 * acids.
 * Note: Once an amino acid is added it is not possible to alter its properties.
 * In order to change an internal property, you have to create a new amino acid
 * with the correct values.
 * IT IS NOT POSSIBLE TO OVERRIDE A REFERENCE (flyweight).
 * @param[in] aa Instance of an AminoAcidImpl
 * @returns True if the given amino acid is added correctly, false otherwise.
 */
Bool addAminoAcid(const AminoAcidImpl& aa);

bool operator<(const AminoAcid& lhs, const AminoAcid& rhs);
bool operator<=(const AminoAcid& lhs, const AminoAcid& rhs);
bool operator>(const AminoAcid& lhs, const AminoAcid& rhs);
bool operator>=(const AminoAcid& lhs, const AminoAcid& rhs);

} // namespace aminoAcids
} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_AMINOACID_HPP__ */
