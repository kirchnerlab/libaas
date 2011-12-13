/*
 * StoichiometryConfigImpl.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/StoichiometryConfigImpl.hpp>

namespace libaas {

StoichiometryConfigImpl::StoichiometryConfigImplKeyType StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG =
		"DEFAULT_STOICHIOMETRY_CONFIG";

/** Constructor
 *
 */
StoichiometryConfigImpl::StoichiometryConfigImpl(
		const StoichiometryConfigImplKeyType& id) :
		id_(id) {
	if (id == DEFAULT_ELEMENT_CONFIG) {
		std::map<elements::ElementImpl::ElementImplSymbolType,
				elements::ElementImpl::ElementImplKeyType> map =
				elements::ElementImpl::getDefaultMapping();
		typedef std::map<elements::ElementImpl::ElementImplSymbolType,
				elements::ElementImpl::ElementImplKeyType>::const_iterator IT;
		for (IT it = map.begin(); it != map.end(); ++it) {
			insert(EntryType(it->first, it->second));
		}
	} else {
		// initialize with default element config entries
		// (or assume missing symbols are configured with default element config)
	}
}

const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& StoichiometryConfigImpl::getId() const {
	return id_;
}

void StoichiometryConfigImpl::insertElement(const elements::Element& element) {
	insert(EntryType(element.get().getSymbol(), element.get().getId()));
}

StoichiometryConfigImpl StoichiometryConfigImpl::clone(
		const StoichiometryConfigImplKeyType& id) const {
	StoichiometryConfigImpl tmp(id);
	typedef StoichiometryConfigImpl::const_iterator IT;
	for (IT it = begin(); it != end(); ++it) {
		tmp.insert(EntryType(it->first, it->second));
	}
	return tmp;
}

bool StoichiometryConfigImpl::operator==(
		const StoichiometryConfigImpl& s) const {
	if (id_ == s.id_) {
		typedef StoichiometryConfigImpl::const_iterator IT;
		IT it1, it2;
		for (it1 = begin(), it2 = s.begin(); it1 != end() && it2 != s.end();
				++it1, ++it2) {
			if (it1->first != it2->first || it1->second != it2->second) {
				return false;
			}
		}
		if (it1 != end() || it2 != s.end()) {
			return false;
		}
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const StoichiometryConfigImpl& o) {
	os << o.getId() << ":";
	typedef StoichiometryConfigImpl::const_iterator IT;
	for (IT it = o.begin(); it != o.end(); ++it) {
		os << it->first << " " << it->second << ", ";
	}
	return os;
}

} // namespace libaas
