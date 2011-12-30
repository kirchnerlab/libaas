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

struct RawModificationIdExtractor {
	const RawModificationImpl::RawModificationImplKeyType& operator()(
			const RawModificationImpl& m) const {
		return m.getId();
	}
};

typedef boost::flyweight<
		boost::flyweights::key_value<
				RawModificationImpl::RawModificationImplKeyType,
				RawModificationImpl, RawModificationIdExtractor>
		, boost::flyweights::no_tracking> RawModification;

libaas::Bool addRawModification(
		const RawModificationImpl::RawModificationImplKeyType& id,
		const libaas::String& psiName, const libaas::String& interimName,
		const libaas::String& description,
		const std::vector<String>& altDescriptions,
		const Stoichiometry& stoichiometry,
		const std::vector<Specificity>& specificities,
		const libaas::Bool& verified);

libaas::Bool addRawModification(const RawModificationImpl& rawModification);

bool operator<(const RawModification& lhs, const RawModification& rhs);
bool operator<=(const RawModification& lhs, const RawModification& rhs);
bool operator>(const RawModification& lhs, const RawModification& rhs);
bool operator>=(const RawModification& lhs, const RawModification& rhs);

} // namespace modifications
} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_RAWMODIFICATION_HPP__ */
