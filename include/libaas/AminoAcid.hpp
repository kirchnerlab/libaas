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

namespace libaas {
namespace aminoAcid {

// TODO we might want to fix the name of the id extractor to be conform
// with best practice (but this nomenclature is similar to the example provided
// by boost)

struct aminoacid_id_extractor {
    const AminoAcidImpl::AminoAcidImplKeyType& operator()(
            const AminoAcidImpl& a) const
    {
        return a.getId();
    }
};

typedef boost::flyweight<boost::flyweights::key_value<
        AminoAcidImpl::AminoAcidImplKeyType, AminoAcidImpl,
        aminoacid_id_extractor>, boost::flyweights::no_tracking>
        AminoAcid;

bool operator<(const AminoAcid& lhs, const AminoAcid& rhs);
bool operator<=(const AminoAcid& lhs, const AminoAcid& rhs);
bool operator>(const AminoAcid& lhs, const AminoAcid& rhs);
bool operator>=(const AminoAcid& lhs, const AminoAcid& rhs);

} // namespace aminoAcid
} // namespace libaas

#endif /* __X_INCLUDE_X_AMINOACID_HPP__ */
