/*
 * StoichiometryConfigImpl.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __X_INCLUDE_X_STOICHIOMETRYCONFIGIMPL_HPP__
#define __X_INCLUDE_X_STOICHIOMETRYCONFIGIMPL_HPP__

#include <libaas/Element.hpp>
#include <libaas/Types.hpp>

#include <map>
#include <iostream>

namespace libaas {

/** StoichiometryConfigImpl
 *
 */
class StoichiometryConfigImpl {

public:

	typedef std::map<elements::ElementImpl::ElementImplSymbolType,
			elements::ElementImpl::ElementImplKeyType> DataType;
	typedef std::pair<elements::ElementImpl::ElementImplSymbolType,
			elements::ElementImpl::ElementImplKeyType> EntryType;

	typedef DataType::const_iterator const_iterator;
	typedef DataType::iterator iterator;
	typedef DataType::value_type value_type;

	typedef String StoichiometryConfigImplKeyType;

	/** Constructor
	 *
	 */
	StoichiometryConfigImpl(const StoichiometryConfigImplKeyType& id);

	const StoichiometryConfigImplKeyType& getId() const;

	const_iterator begin() const;
	iterator begin();
	const_iterator end() const;
	iterator end();

	void insertElement(const elements::Element& element);
	void insertElement(
			const elements::ElementImpl::ElementImplSymbolType& symbol,
			const elements::ElementImpl::ElementImplKeyType& key);

	const elements::ElementImpl::ElementImplKeyType& getKeyForSymbol(
			const elements::ElementImpl::ElementImplSymbolType& symbol) const;

	StoichiometryConfigImpl clone(
			const StoichiometryConfigImplKeyType& id) const;

	bool operator==(const StoichiometryConfigImpl& s) const;
	//ElementConfigImpl& operator=(const ElementConfigImpl& rhs);

	static StoichiometryConfigImplKeyType DEFAULT_ELEMENT_CONFIG;

private:

	DataType map_;
	StoichiometryConfigImplKeyType id_;

};
// class StoichiometryConfigImpl

std::ostream& operator<<(std::ostream&, const StoichiometryConfigImpl&);

} // namespace libaas

#endif /* __X_INCLUDE_X_STOICHIOMETRYCONFIGIMPL_HPP__ */
