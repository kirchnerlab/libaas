/*
 * Element.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Element.hpp>

namespace libaas {
namespace elementTable {

// TODO it might be enough to define operator<... for Element since the
// implicit conversion from fw<Element> -> const Element& should solve the
// map<fw<Element>> stuff

Bool ElementTable::addElement(const ElementImpl::ElementImplKeyType& id,
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

} // namespace elementTable
} // namespace libaas
