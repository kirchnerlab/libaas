/*
 * AminoAcid.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __X_INCLUDE_X_AMINOACID_HPP__
#define __X_INCLUDE_X_AMINOACID_HPP__

#include <libaas/AminoAcidImpl.hpp>

#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/flyweight/no_tracking.hpp>

//#include <iostream>

namespace libaas {

struct aminoacid_id_extractor {
    const AminoAcidImpl::AminoAcidImplKeyType& operator()(
            const AminoAcidImpl& a) const
    {
        return a.getId();
    }
};

typedef boost::flyweight<boost::flyweights::key_value<
        libaas::AminoAcidImpl::AminoAcidImplKeyType, libaas::AminoAcidImpl,
        libaas::aminoacid_id_extractor>, boost::flyweights::no_tracking>
        AminoAcid;

bool operator<(const libaas::AminoAcid& lhs, const libaas::AminoAcid& rhs);
bool operator<=(const libaas::AminoAcid& lhs, const libaas::AminoAcid& rhs);
bool operator>(const libaas::AminoAcid& lhs, const libaas::AminoAcid& rhs);
bool operator>=(const libaas::AminoAcid& lhs, const libaas::AminoAcid& rhs);

} // namespace libaas

#endif /* __X_INCLUDE_X_AMINOACID_HPP__ */
