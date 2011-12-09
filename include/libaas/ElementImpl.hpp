/*
 * ElementImpl.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __X_INCLUDE_X_ELEMENTIMPL_HPP__
#define __X_INCLUDE_X_ELEMENTIMPL_HPP__

#include <libaas/Isotope.hpp>
#include <libaas/Types.hpp>

#include <string>
#include <vector>
#include <iostream>

namespace libaas {

/** Element
 *
 */
class ElementImpl {

public:

    typedef Size ElementImplKeyType;

    /** Constructor
     *
     */
    ElementImpl(ElementImplKeyType id);
    ElementImpl(const ElementImplKeyType& id, const String& symbol,
            const Size& atomicNumber);

    const ElementImplKeyType& getId() const;
    const String& getSymbol() const;
    const Size& getAtomicNumber() const;
    const std::vector<Isotope>& getIsotopes() const;

    void addIsotope(const libaas::Isotope& i);
    void addIsotope(const Double& mass, const Double& frequency);
    void setIsotopes(const std::vector<libaas::Isotope>& isotopes);

    ElementImpl& operator=(const ElementImpl& rhs);
    bool operator==(const ElementImpl& s) const;
    bool operator!=(const ElementImpl& s) const;

    static ElementImplKeyType getNumberOfStandardElements();
    static ElementImplKeyType getNextId();

private:

    ElementImplKeyType id_;
    String symbol_;
    Size atomicNumber_;
    std::vector<libaas::Isotope> isotopes_;

    static ElementImplKeyType freeId;

}; // class ElementImpl

std::ostream& operator<<(std::ostream&, const ElementImpl&);
//istream& operator>>(std::istream&, Element&);

} // namespace libaas

#endif /* __X_INCLUDE_X_ELEMENTIMPL_HPP__ */
