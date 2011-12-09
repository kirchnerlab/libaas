/*
 * Modification.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Modification.hpp>

namespace libaas {

bool operator<(const Modification& lhs, const Modification& rhs)
{
    return lhs.get_key() < rhs.get_key();
}

bool operator<=(const Modification& lhs, const Modification& rhs)
{
    return lhs.get_key() <= rhs.get_key();
}

bool operator>(const Modification& lhs, const Modification& rhs)
{
    return lhs.get_key() > rhs.get_key();
}

bool operator>=(const Modification& lhs, const Modification& rhs)
{
    return lhs.get_key() >= rhs.get_key();
}

} // namespace libaas
