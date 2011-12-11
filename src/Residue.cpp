/*
 * Residue.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Residue.hpp>

namespace libaas {

/** Constructor
 *
 */
Residue::Residue()
{

}

void Residue::setAminoacid(const libaas::aminoAcids::AminoAcid& aminoacid)
{
    aminoacid_ = aminoacid;
}

const libaas::aminoAcids::AminoAcid& Residue::getAminoacid() const
{
    return aminoacid_;
}

void Residue::setModification(
        const libaas::modifications::Modification& modification)
{
    modification_ = modification;
}

const libaas::modifications::Modification& Residue::getModification() const
{
    return modification_;
}

//std::ostream& operator<<(std::ostream& os, const Residue& o) {
//    return os;
//}
//istream& operator>>(std::istream& is, Residue& i) {
//    return is;
//}

} // namespace libaas
