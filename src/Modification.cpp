/*
 * Modification.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Modification.hpp>

namespace libaas {
namespace modifications {

/** Constructor
 *
 */

Modification::Modification() :
		modification_(""), stoichiometryConfig_(
				StoichiometryConfig(
						StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG)) {
}

Modification::Modification(const RawModification& modification) :
		modification_(modification), stoichiometryConfig_(
				StoichiometryConfig(
						StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG)) {
}

Modification::Modification(
		const RawModificationImpl::RawModificationImplKeyType& modid) :
		modification_(RawModification(modid)), stoichiometryConfig_(
				StoichiometryConfig(
						StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG)) {
}

Modification::Modification(const RawModification& modification,
		const StoichiometryConfig& config) :
		modification_(modification), stoichiometryConfig_(config) {
}
Modification::Modification(
		const RawModificationImpl::RawModificationImplKeyType& modid,
		const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid) :
		modification_(RawModification(modid)), stoichiometryConfig_(
				StoichiometryConfig(configid)) {
}

void Modification::setModification(const RawModification& modification) {
	modification_ = modification;
}

void Modification::setModification(
		const RawModificationImpl::RawModificationImplKeyType& modid) {
	modification_ = RawModification(modid);
}

const RawModification& Modification::getModification() const {
	return modification_;
}

void Modification::setStoichiometryConfig(const StoichiometryConfig& config) {
	stoichiometryConfig_ = config;
}

void Modification::setStoichiometryConfig(
		const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid) {
	stoichiometryConfig_ = StoichiometryConfig(configid);
}

const StoichiometryConfig& Modification::getStoichiometryConfig() const {
	return stoichiometryConfig_;
}

bool Modification::operator==(const Modification& s) const {
	return modification_ == s.modification_
			&& stoichiometryConfig_ == s.stoichiometryConfig_;
}

std::ostream& operator<<(std::ostream& os, const Modification& o) {
	os << o.getModification() << "\t" << o.getStoichiometryConfig();
	return os;
}

} // namespace modifications
} // namespace libaas
