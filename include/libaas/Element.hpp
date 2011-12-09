/*
 * Element.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __X_INCLUDE_X_ELEMENT_HPP__
#define __X_INCLUDE_X_ELEMENT_HPP__

#include <libaas/ElementImpl.hpp>

#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/flyweight/no_tracking.hpp>

namespace libaas {

struct element_id_extractor {
    const ElementImpl::ElementImplKeyType& operator()(const ElementImpl& e) const
    {
        return e.getId();
    }
};

typedef boost::flyweight<boost::flyweights::key_value<
        libaas::ElementImpl::ElementImplKeyType, libaas::ElementImpl,
        libaas::element_id_extractor>, boost::flyweights::no_tracking> Element;

bool operator<(const Element& lhs, const Element& rhs);
bool operator<=(const Element& lhs, const Element& rhs);
bool operator>(const Element& lhs, const Element& rhs);
bool operator>=(const Element& lhs, const Element& rhs);

} // namespace libaas

#endif /* __X_INCLUDE_X_ELEMENT_HPP__ */
