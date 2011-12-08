/*
 * Modification.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 *
 */

#include <libaas/Modification.hpp>

namespace libaas {

/** Constructor
 *
 */
Modification::Modification(ModificationKeyType id) :
    id_(id)
{
}

const Modification::ModificationKeyType& Modification::getId() const
{
    return id_;
}

//std::ostream& operator<<(std::ostream& os, const Modification& o) {
//    return os;
//}
//istream& operator>>(std::istream& is, Modification& i) {
//    return is;
//}

} // namespace libaas
