/*
 * Element.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_AAS_ELEMENT_HPP__
#define __LIBAAS_INCLUDE_AAS_ELEMENT_HPP__

#include <aas/FlyWeightReplacement.hpp>
#include <aas/ElementImpl.hpp>

namespace aas {
namespace elements {

typedef FlyWeightReplacement<ElementImpl, ElementImpl::ElementImplKeyType> Element;

/**Convenience function to add a custom element to this list of known elements.
 * This methods calls addElement(ElementImpl)
 * @param[in] id Key/Id of the element
 * @param[in] symbol Symbol of the element
 * @param[in] atomicNumber Atomic number of the element
 * @param[in] isotopes List of isotopes of the element
 * @returns True if the given element is added correctly, false otherwise.
 */
Bool addElement(const ElementImpl::ElementImplKeyType& id,
    const aas::String& symbol, const aas::Size& atomicNumber,
    const std::vector<Isotope>& isotopes);

/**Convenience function to add a custom element to the list of known elements.
 * Note: Once an element is added it is not possible to alter its properties.
 * In order to change an internal property you have to create a new element
 * with the correct values and add it to the list. In order to add it the
 * element must have a unique key.
 * IT IS NOT POSSIBLE TO OVERRIDE A REFERENCE (flyweight).
 * @param[in] element Instance of an ElementImpl
 * @returns True if the given element is added correctly, false otherwise.
 */
Bool addElement(const ElementImpl& element);

bool operator<(const Element& lhs, const Element& rhs);
bool operator<=(const Element& lhs, const Element& rhs);
bool operator>(const Element& lhs, const Element& rhs);
bool operator>=(const Element& lhs, const Element& rhs);

} // namespace elements
} // namespace aas

#endif /* __LIBAAS_INCLUDE_AAS_ELEMENT_HPP__ */
