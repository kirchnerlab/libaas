/*
 * AminoAcid.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 *
 */

#include <libaas/AminoAcid.hpp>

namespace libaas {

/** Constructor
 *
 */
AminoAcid::AminoAcid(AminoAcid::AminoAcidKeyType id) :
    id_(id)
{
}

const AminoAcid::AminoAcidKeyType& AminoAcid::getId() const
{
    return id_;
}

//std::ostream& operator<<(std::ostream& os, const AminoAcid& o) {
//    return os;
//}
//istream& operator>>(std::istream& is, AminoAcid& i) {
//    return is;
//}

} // namespace libaas
