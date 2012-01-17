/*
 * Element.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Element.hpp>

namespace libaas {
namespace elements {

bool operator<(const Element& lhs, const Element& rhs)
{
    return lhs.get_key() < rhs.get_key();
}

bool operator<=(const Element& lhs, const Element& rhs)
{
    return lhs.get_key() <= lhs.get_key();
}

bool operator>(const Element& lhs, const Element& rhs)
{
    return lhs.get_key() > lhs.get_key();
}

bool operator>=(const Element& lhs, const Element& rhs)
{
    return lhs.get_key() >= rhs.get_key();
}

//std::ostream& operator<<(std::ostream& os, const Element& e) {
//    os << e.get();
//    return os;
//}

Bool addElement(const ElementImpl::ElementImplKeyType& id,
    const libaas::String& symbol, const libaas::Size& atomicNumber,
    const std::vector<Isotope>& isotopes)
{
    return addElement(ElementImpl(id, symbol, atomicNumber, isotopes));
}

Bool addElement(const ElementImpl& element)
{
    Element element_ref(element);
    return element_ref == element;
}

} // namespace elements
} // namespace libaas
