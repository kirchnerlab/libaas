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
namespace elements {

// TODO we might want to fix the name of the id extractor to be conform
// with best practice (but this nomenclature is similar to the example provided
// by boost)

struct element_id_extractor {
    const ElementImpl::ElementImplKeyType& operator()(const ElementImpl& e) const
    {
        return e.getId();
    }
};

typedef boost::flyweight<boost::flyweights::key_value<
        ElementImpl::ElementImplKeyType, ElementImpl, element_id_extractor>,
        boost::flyweights::no_tracking> Element;

bool operator<(const Element& lhs, const Element& rhs);
bool operator<=(const Element& lhs, const Element& rhs);
bool operator>(const Element& lhs, const Element& rhs);
bool operator>=(const Element& lhs, const Element& rhs);

Bool addElement(const ElementImpl::ElementImplKeyType& id,
        const String& symbol, const Size& atomicNumber, const std::vector<
                Isotope>& isotopes);

} // namespace elements
} // namespace libaas

#endif /* __X_INCLUDE_X_ELEMENT_HPP__ */
