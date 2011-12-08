/*
 * Libaas.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 *
 */

#ifndef __X_INCLUDE_X_LIBAAS_HPP__
#define __X_INCLUDE_X_LIBAAS_HPP__

#include <libaas/Element.hpp>

#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/flyweight/no_tracking.hpp>

namespace libaas {

typedef boost::flyweight<boost::flyweights::key_value<
        libaas::ElementImpl::ElementImplKeyType, libaas::ElementImpl,
        libaas::element_id_extractor>, boost::flyweights::no_tracking>
        Element;

} // namespace libaas

#endif /* __X_INCLUDE_X_LIBAAS_HPP__ */
