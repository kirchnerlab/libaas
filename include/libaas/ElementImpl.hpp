/*
 * ElementImpl.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_LIBAAS_ELEMENTIMPL_HPP__
#define __LIBAAS_INCLUDE_LIBAAS_ELEMENTIMPL_HPP__

#include <libaas/Isotope.hpp>
#include <libaas/Types.hpp>

#include <string>
#include <vector>
#include <map>
#include <iostream>

namespace libaas {
namespace elements {

/**Representation of an element.
 *
 * This class holds all information about an element.
 */
class ElementImpl {

public:

    /**Convenience typedef of the symbol type of an element.
     */
    typedef String ElementImplSymbolType;
    /**Convenience typedef of the key type of an element.
     */
    typedef Size ElementImplKeyType;

    /**Default constructor to create a standard element.
     *
     * This constructor has access to static variables containing all
     * information necessary to create and fill the internal variables.
     *
     * @param[in] id Key/Id of the element
     * @throws Throws an exceptions of the given id is not recognized in the
     * list of standard elements.
     */
    ElementImpl(const ElementImplKeyType& id);

    /**Constructor to create a custom element.
     * @param[in] id Key/Id of the element
     * @param[in] symbol Symbol of the element
     * @param[in] atomicNumber Atomic number of the element
     */
    ElementImpl(const ElementImplKeyType& id, const String& symbol,
            const Size& atomicNumber);

    /**Constructor to create a custom element.
     * @param[in] id Key/Id of the element
     * @param[in] symbol Symbol of the element
     * @param[in] atomicNumber Atomic number of the element
     * @param[in] isotopes List of isotopes
     */
    ElementImpl(const ElementImplKeyType& id, const String& symbol,
            const Size& atomicNumber, const std::vector<Isotope>& isotopes);

    /**Returns the key/id of the element.
     * @returns Key/Id of the element.
     */
    const ElementImplKeyType& getId() const;

    /**Returns the element symbol.
     * @returns Symbol of the element.
     */
    const String& getSymbol() const;

    /**Returns the atomic number of the element.
     * @return Atomic number of the element
     */
    const Size& getAtomicNumber() const;

    /**Returns the list of isotopes of the element.
     * @returns List of isotopes of the element.
     */
    const std::vector<Isotope>& getIsotopes() const;

    /**Adds an isotope to the element.
     * @param[in] isotope Isotope
     */
    void addIsotope(const Isotope& isotope);

    /**Adds an isotope to the element.
     * @param[in] mass Mass
     * @param[in] frequency Frequency of the
     */
    void addIsotope(const Double& mass, const Double& frequency);

    /**Sets the list of isotopes of the element.
     * @param[in] isotopes List of isotopes
     */
    void setIsotopes(const std::vector<Isotope>& isotopes);

    ElementImpl& operator=(const ElementImpl& rhs);
    bool operator==(const ElementImpl& s) const;
    bool operator!=(const ElementImpl& s) const;

    /**Returns the number of standard elements.
     * @returns The number of standard elements.
     */
    static libaas::Size getNumberOfStandardElements();

    /**Returns a free key/id which is available to use for a custom element.
     * @returns Free key/id
     */
    static ElementImplKeyType getNextId();

    /**Returns the default mapping of an element symbol to an element key.
     * This mapping is used to create the default stoichiometry configuration.
     * @returns Default mapping of an element symbol to the element key.
     */
    static std::map<ElementImplSymbolType, ElementImplKeyType>
            getDefaultMapping();

private:

    ElementImplKeyType id_;
    String symbol_;
    Size atomicNumber_;
    std::vector<Isotope> isotopes_;

    static ElementImplKeyType freeId;

};
// class ElementImpl

std::ostream& operator<<(std::ostream&, const ElementImpl&);

inline const ElementImpl::ElementImplKeyType& ElementImpl::getId() const
{
    return id_;
}

} // namespace elements
} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_ELEMENTIMPL_HPP__ */
