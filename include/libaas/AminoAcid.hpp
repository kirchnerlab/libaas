/*
 * AminoAcid.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 *
 */

#ifndef __X_INCLUDE_X_AMINOACID_HPP__
#define __X_INCLUDE_X_AMINOACID_HPP__

#include <libaas/Stoichiometry.hpp>

#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/flyweight/no_tracking.hpp>

//#include <iostream>

namespace libaas {

// forward definition
struct aminoacid_id_extractor;

/** AminoAcid
 *
 */
class AminoAcid {

public:

    typedef int AminoAcidKeyType;
    typedef boost::flyweight<boost::flyweights::key_value<
            libaas::AminoAcid::AminoAcidKeyType, libaas::AminoAcid,
            libaas::aminoacid_id_extractor>, boost::flyweights::no_tracking>
            AminoAcidRef;
    /** Constructor
     *
     */
    AminoAcid(AminoAcidKeyType id);

    const AminoAcidKeyType& getId() const;

    //bool operator==(const AminoAcid& s) const;
    //AminoAcid& operator=(const AminoAcid& rhs);

private:

    AminoAcidKeyType id_;
    Stoichiometry stoichiometry_;

    char aminoAcid_;

}; // class AminoAcid

struct aminoacid_id_extractor {
    const AminoAcid::AminoAcidKeyType& operator()(const AminoAcid& a) const
    {
        return a.getId();
    }
};

//std::ostream& operator<<(std::ostream&, const AminoAcid&);
//istream& operator>>(std::istream&, AminoAcid&);

} // namespace libaas

#endif /* __X_INCLUDE_X_AMINOACID_HPP__ */
