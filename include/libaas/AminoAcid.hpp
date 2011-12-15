/*
 * AminoAcid.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __X_INCLUDE_X_AMINOACID_HPP__
#define __X_INCLUDE_X_AMINOACID_HPP__

#include <libaas/AminoAcidImpl.hpp>

#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/flyweight/no_tracking.hpp>

namespace libaas {
namespace aminoAcids {

struct AminoAcidIdExtractor {
	const AminoAcidImpl::AminoAcidImplKeyType& operator()(
			const AminoAcidImpl& a) const {
		return a.getId();
	}
};

typedef boost::flyweight<
		boost::flyweights::key_value<AminoAcidImpl::AminoAcidImplKeyType,
				AminoAcidImpl, AminoAcidIdExtractor>
		, boost::flyweights::no_tracking> AminoAcid;

bool operator<(const AminoAcid& lhs, const AminoAcid& rhs);
bool operator<=(const AminoAcid& lhs, const AminoAcid& rhs);
bool operator>(const AminoAcid& lhs, const AminoAcid& rhs);
bool operator>=(const AminoAcid& lhs, const AminoAcid& rhs);

Bool addAminoAcid(const AminoAcidImpl::AminoAcidImplKeyType& id,
		const Char symbol, const libaas::Stoichiometry& stoichiometry);

} // namespace aminoAcids
} // namespace libaas

#endif /* __X_INCLUDE_X_AMINOACID_HPP__ */
