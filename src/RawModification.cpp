/*
 * RawModification.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/RawModification.hpp>

namespace libaas {
namespace modifications {

libaas::Bool addRawModification(
		const RawModificationImpl::RawModificationImplKeyType& id,
		const libaas::String& name, const libaas::String& fullName,
		const std::vector<String>& altDescriptions,
		const Stoichiometry& stoichiometry,
		const std::vector<Specificity>& specificities,
		const libaas::Bool& verified) {
	RawModificationImpl rm(id, name, fullName, verified);
	rm.setAltNames(altDescriptions);
	rm.setStoichiometry(stoichiometry);
	rm.setSpecificities(specificities);
	return addRawModification(rm);
}

libaas::Bool addRawModification(const RawModificationImpl& rawModification) {
	return rawModification == RawModification(rawModification);
}

bool operator<(const RawModification& lhs, const RawModification& rhs) {
	return lhs.get_key() < rhs.get_key();
}

bool operator<=(const RawModification& lhs, const RawModification& rhs) {
	return lhs.get_key() <= rhs.get_key();
}

bool operator>(const RawModification& lhs, const RawModification& rhs) {
	return lhs.get_key() > rhs.get_key();
}

bool operator>=(const RawModification& lhs, const RawModification& rhs) {
	return lhs.get_key() >= rhs.get_key();
}

} // namespace modifications
} // namespace libaas
