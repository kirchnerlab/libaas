/*
 * ModificationImpl.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/ModificationImpl.hpp>

namespace libaas {

/** Constructor
 *
 */
ModificationImpl::ModificationImpl(ModificationImplKeyType id) :
    id_(id)
{
}

const ModificationImpl::ModificationImplKeyType& ModificationImpl::getId() const
{
    return id_;
}

//std::ostream& operator<<(std::ostream& os, const ModificationImpl& o) {
//    return os;
//}
//istream& operator>>(std::istream& is, ModificationImpl& i) {
//    return is;
//}

} // namespace libaas
