/*
 * Element.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_LIBAAS_ELEMENT_HPP__
#define __LIBAAS_INCLUDE_LIBAAS_ELEMENT_HPP__

#include <libaas/ElementImpl.hpp>

#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/flyweight/no_tracking.hpp>

namespace libaas {
namespace elements {

/**The class ElementIdExtractor is used allow the instantiation of
 * flyweight<ElementImpl>(Key). This simplifies the instantiation and provides
 * a speed up, since the ElementImpl is instantiated only once.
 */
struct ElementIdExtractor {
    const ElementImpl::ElementImplKeyType& operator()(const ElementImpl& e) const
    {
        return e.getId();
    }
};

/**Typedef to simplify the data type flyweight<ElementImpl>
 */
typedef boost::flyweight<boost::flyweights::key_value<
        ElementImpl::ElementImplKeyType, ElementImpl, ElementIdExtractor>,
        boost::flyweights::no_tracking> Element;

/**Convenience function to add a custom element to this list of known elements.
 * This methods calls addElement(ElementImpl)
 * @param[in] id Key/Id of the element
 * @param[in] symbol Symbol of the element
 * @param[in] atomicNumber Atomic number of the element
 * @param[in] isotopes List of isotopes of the element
 * @returns True if the given element is added correctly, false otherwise.
 */
Bool addElement(const ElementImpl::ElementImplKeyType& id,
        const String& symbol, const Size& atomicNumber, const std::vector<
                Isotope>& isotopes);

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
} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_ELEMENT_HPP__ */
