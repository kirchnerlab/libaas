/*
 * Residue.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __X_INCLUDE_X_RESIDUE_HPP__
#define __X_INCLUDE_X_RESIDUE_HPP__

#include <libaas/AminoAcid.hpp>
#include <libaas/Modification.hpp>

#include <iostream>

namespace libaas {

/** Residue
 *
 */
class Residue {

public:
    Residue(const libaas::aminoAcids::AminoAcid& aminoAcid);

    void setAminoacid(const libaas::aminoAcids::AminoAcid& aminoacid);
    const libaas::aminoAcids::AminoAcid& getAminoacid() const;

    void setModification(
            const libaas::modifications::Modification& modification);
    const libaas::modifications::Modification& getModification() const;
    libaas::modifications::Modification& getModification();

private:

    libaas::aminoAcids::AminoAcid aminoacid_;
    libaas::modifications::Modification modification_;

}; // class Residue

std::ostream& operator<<(std::ostream&, const Residue&);

} // namespace libaas

#endif /* __X_INCLUDE_X_RESIDUE_HPP__ */
