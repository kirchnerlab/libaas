/*
 * Modification.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __X_INCLUDE_X_MODIFICATION_HPP__
#define __X_INCLUDE_X_MODIFICATION_HPP__

#include <libaas/ModificationImpl.hpp>

#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/flyweight/no_tracking.hpp>

namespace libaas {

struct modification_id_extractor {
    const ModificationImpl::ModificationImplKeyType& operator()(
            const ModificationImpl& m) const
    {
        return m.getId();
    }
};

typedef boost::flyweight<boost::flyweights::key_value<
        libaas::ModificationImpl::ModificationImplKeyType,
        libaas::ModificationImpl, libaas::modification_id_extractor>,
        boost::flyweights::no_tracking> Modification;

bool operator<(const Modification& lhs, const Modification& rhs);
bool operator<=(const Modification& lhs, const Modification& rhs);
bool operator>(const Modification& lhs, const Modification& rhs);
bool operator>=(const Modification& lhs, const Modification& rhs);

} // namespace libaas

#endif /* __X_INCLUDE_X_MODIFICATION_HPP__ */
