/*
 * AminoAcidSequence.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 *
 */

#ifndef __X_INCLUDE_X_AMINOACIDSEQUENCE_HPP__
#define __X_INCLUDE_X_AMINOACIDSEQUENCE_HPP__

#include <libaas/Residue.hpp>
#include <libaas/Collection.hpp>

//#include <iostream>

namespace libaas {

/** AminoAcidSequence
 *
 */
class AminoAcidSequence : public libaas::Collection<libaas::Residue> {

public:
    /** Constructor
     *
     */
	AminoAcidSequence();

	//bool operator==(const AminoAcidSequence& s) const;
	//AminoAcidSequence& operator=(const AminoAcidSequence& rhs);

private:

}; // class AminoAcidSequence

//std::ostream& operator<<(std::ostream&, const AminoAcidSequence&);
//istream& operator>>(std::istream&, AminoAcidSequence&);

} // namespace libaas

#endif /* __X_INCLUDE_X_AMINOACIDSEQUENCE_HPP__ */
