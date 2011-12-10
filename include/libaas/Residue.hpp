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

//#include <iostream>

namespace libaas {

/** Residue
 *
 */
class Residue {

public:
    /** Constructor
     *
     */
    Residue();

    //bool operator==(const Residue& s) const;
    //Residue& operator=(const Residue& rhs);

private:

    libaas::aminoAcids::AminoAcid aminoacid_;
    libaas::modifications::Modification modification_;

}; // class Residue

//std::ostream& operator<<(std::ostream&, const Residue&);

} // namespace libaas

#endif /* __X_INCLUDE_X_RESIDUE_HPP__ */
