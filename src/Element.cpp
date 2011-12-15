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

// TODO General:
// 1) implement operators such as <,<=,==,!=,... for each type?
// 2) implement operator<< for vector<type> for all types?

Bool addElement(const ElementImpl::ElementImplKeyType& id,
        const String& symbol, const Size& atomicNumber,
        const std::vector<Isotope>& isotopes)
{
    ElementImpl element(id, symbol, atomicNumber);
    element.setIsotopes(isotopes);
    Element element_ref(element);
    return element_ref == element;
}

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

} // namespace elements
} // namespace libaas
