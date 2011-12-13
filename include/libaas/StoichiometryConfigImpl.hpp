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
class StoichiometryConfigImpl: public std::map<
		elements::ElementImpl::ElementImplSymbolType,
		elements::ElementImpl::ElementImplKeyType> {

public:

	typedef std::map<elements::ElementImpl::ElementImplSymbolType,
			elements::ElementImpl::ElementImplKeyType> DataType;
	typedef std::pair<String, elements::ElementImpl::ElementImplKeyType> EntryType;

	typedef String StoichiometryConfigImplKeyType;

	/** Constructor
	 *
	 */
	StoichiometryConfigImpl(const StoichiometryConfigImplKeyType& id);

	const StoichiometryConfigImplKeyType& getId() const;

	void insertElement(const elements::Element& element);

	StoichiometryConfigImpl clone(
			const StoichiometryConfigImplKeyType& id) const;

	bool operator==(const StoichiometryConfigImpl& s) const;
	//ElementConfigImpl& operator=(const ElementConfigImpl& rhs);

	static StoichiometryConfigImplKeyType DEFAULT_ELEMENT_CONFIG;

private:

	StoichiometryConfigImplKeyType id_;

};
// class StoichiometryConfigImpl

std::ostream& operator<<(std::ostream&, const StoichiometryConfigImpl&);

} // namespace libaas

#endif /* __X_INCLUDE_X_STOICHIOMETRYCONFIGIMPL_HPP__ */
