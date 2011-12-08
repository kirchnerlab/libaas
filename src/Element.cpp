/*
 * Element.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 *
 */

#include <libaas/Element.hpp>

namespace libaas {

// TODO it might be enough to define operator<... for Element since the
// implicit conversion from fw<Element> -> const Element& should solve the
// map<fw<Element>> stuff

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

} // namespace libaas
