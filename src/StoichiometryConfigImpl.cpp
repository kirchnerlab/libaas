/*
 * StoichiometryConfigImpl.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/StoichiometryConfigImpl.hpp>

#include <stdexcept>

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
			map_.insert(EntryType(it->first, it->second));
		}
	} else {
		// initialize with default element config entries
		// (or assume missing symbols are configured with default element config)
	}
}

const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& StoichiometryConfigImpl::getId() const {
	return id_;
}

StoichiometryConfigImpl::const_iterator StoichiometryConfigImpl::begin() const {
	return map_.begin();
}

StoichiometryConfigImpl::iterator StoichiometryConfigImpl::begin() {
	return map_.begin();
}

StoichiometryConfigImpl::const_iterator StoichiometryConfigImpl::end() const {
	return map_.end();
}

StoichiometryConfigImpl::iterator StoichiometryConfigImpl::end() {
	return map_.end();
}

void StoichiometryConfigImpl::insertElement(const elements::Element& element) {
	map_.insert(EntryType(element.get().getSymbol(), element.get().getId()));
}

void StoichiometryConfigImpl::insertElement(
		const elements::ElementImpl::ElementImplSymbolType& symbol,
		const elements::ElementImpl::ElementImplKeyType& key) {
	map_.insert(EntryType(symbol, key));
}

const elements::ElementImpl::ElementImplKeyType& StoichiometryConfigImpl::getKeyForSymbol(
		const elements::ElementImpl::ElementImplSymbolType& symbol) const {
	typedef const_iterator IT;
	IT tmp = map_.find(symbol);
	if (tmp != end()) {
		return tmp->second;
	} else {
		throw std::out_of_range(
				"StoichiometryConfigImpl::getKeyForSymbol(): Cannot find symbol in stoichiometry config.");
	}
}

StoichiometryConfigImpl StoichiometryConfigImpl::clone(
		const StoichiometryConfigImplKeyType& id) const {
	StoichiometryConfigImpl tmp(id);
	typedef StoichiometryConfigImpl::const_iterator IT;
	for (IT it = begin(); it != end(); ++it) {
		tmp.map_.insert(EntryType(it->first, it->second));
	}
	return tmp;
}

bool StoichiometryConfigImpl::operator==(
		const StoichiometryConfigImpl& s) const {
	return id_ == s.id_ && map_ == s.map_;
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
