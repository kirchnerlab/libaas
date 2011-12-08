/*
 * ElementTable.hpp
 *
 *  Copyright (C) 2011 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_LIBAAS_ELEMENTTABLE_HPP__
#define __LIBAAS_INCLUDE_LIBAAS_ELEMENTTABLE_HPP__

#include <libaas/config.hpp>
#include <libaas/old/Types.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <vector>
#include <iostream>

namespace libaas {

class Element;

/** Extensible periodic table of elements.
 * An \c ElementTable object provides lookup functionality akin to a periodic
 * table of elements. The mapping inside the table is based on a unique ID.
 * For the statically assigned standard elements, the unique ID corresponds to
 * the atomic number but this guarantee is abandoned for any elements
 * (commonly isotope enrichments) that are added post-initialization.
 *
 * The \c ElementTable also acts as a factory for \c Element objects.
 */
class ElementTable {
public:
    /** Constructor.
     */
    ElementTable();

    /** Creates a new element in the table of elements and returns a
     * mutable \c Element object.
     * @return A reference to the newly created \c Element instance.
     */
    Element create();

    /** Access an element in the table of elements based on it's ID.
     * @param id The ID of the requested element instance.
     * @return A const reference to the \c Element instance.
     */
    const Element get(const Size id) const;

    /**
     *
     * @param symbol
     * @return
     */
    // const Element getBySymbol(const String symbol) const;

    /**
     *
     * @param atomicNumber
     * @return
     */
    //  const Element getByAtomicNumber(const Size atomicNumber) const;

    /** Request the number of elements present in the table of elements.
     * @return The size of the table of elements.
     */
    Size size() const;

private:
    class ElementTableImpl;
    boost::shared_ptr<ElementTableImpl> impl_;
    friend class Element;
};

/** Class representing a chemical element.
 * Instances of the class hold the basic information necessary for MS, i.e.
 * the isotope distribution of the element's stable isotopes.
 *
 * Note that \c Element objects should be considered to be references, i.e.
 * they should be treated as constant, non-mutable objects once the table
 * of elements has been set up.
 */
class Element {
public:
    struct Isotope {
        Double mass;
        Double frequency;
    };
    Size getId() const;
    String getSymbol() const;
    void setSymbol(const String& symbol);
    Size getAtomicNumber() const;
    void setAtomicNumber(const Size& atomicNumber);
    const std::vector<Isotope>& getIsotopes() const;
    void setIsotopes(const std::vector<Isotope>& isotopes);
    void addIsotope(const Double mass, const Double frequency);

private:
    class ElementImpl;
    Element();
    Element(const ElementImpl&);
    boost::shared_ptr<ElementImpl> impl_;
    friend class ElementTable::ElementTableImpl;
};

std::ostream& operator<<(std::ostream&, const Element& e);

} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_ELEMENTTABLE_HPP__ */

