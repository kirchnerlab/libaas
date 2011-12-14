/*
 * RawModification.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __X_INCLUDE_X_RAWMODIFICATION_HPP__
#define __X_INCLUDE_X_RAWMODIFICATION_HPP__

#include <libaas/RawModificationImpl.hpp>

#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/flyweight/no_tracking.hpp>

namespace libaas {
namespace modifications {

struct rawmodification_id_extractor {
	const RawModificationImpl::RawModificationImplKeyType& operator()(
			const RawModificationImpl& m) const {
		return m.getId();
	}
};

typedef boost::flyweight<
		boost::flyweights::key_value<
				RawModificationImpl::RawModificationImplKeyType,
				RawModificationImpl, rawmodification_id_extractor>
		, boost::flyweights::no_tracking> RawModification;

// TODO addRawModification

bool operator<(const RawModification& lhs, const RawModification& rhs);
bool operator<=(const RawModification& lhs, const RawModification& rhs);
bool operator>(const RawModification& lhs, const RawModification& rhs);
bool operator>=(const RawModification& lhs, const RawModification& rhs);

} // namespace modifications
} // namespace libaas

#endif /* __X_INCLUDE_X_RAWMODIFICATION_HPP__ */
