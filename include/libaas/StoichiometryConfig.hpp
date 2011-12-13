/*
 * StoichiometryConfig.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __X_INCLUDE_X_STOICHIOMETRYCONFIG_HPP__
#define __X_INCLUDE_X_STOICHIOMETRYCONFIG_HPP__

#include <libaas/StoichiometryConfigImpl.hpp>
#include <libaas/Types.hpp>

#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/flyweight/no_tracking.hpp>

namespace libaas {

struct stoichiometryConfig_id_extractor {
	const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& operator()(
			const StoichiometryConfigImpl& e) const {
		return e.getId();
	}
};

typedef boost::flyweight<
		boost::flyweights::key_value<
				StoichiometryConfigImpl::StoichiometryConfigImplKeyType,
				StoichiometryConfigImpl, stoichiometryConfig_id_extractor>
		, boost::flyweights::no_tracking> StoichiometryConfig;

libaas::Bool
addStoichiometryConfig(
		const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& id,
		const StoichiometryConfigImpl::DataType& map);

libaas::Bool addStoichiometryConfig(
		const StoichiometryConfigImpl& stoichiometryConfig);

} // namespace libaas

#endif /* __X_INCLUDE_X_ELEMENTCONFIG_HPP__ */
