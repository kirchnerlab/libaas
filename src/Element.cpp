/*
 * Element.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 *
 */

#include <libaas/Element.hpp>
#include <libaas/ElementTable.hpp>

namespace libaas {

/** Constructor
 *
 */
Element::Element(Element::ElementKeyType id) :
    id_(id)
{
    ElementTable et;
    symbol_ = et.getSymbol(id);
    atomicNumber_ = et.getAtomicNumber(id);
    et.getIsotopes(id, isotopes_);
}

const Element::ElementKeyType& Element::getId() const
{
    return id_;
}

const std::string& Element::getSymbol() const
{
    return symbol_;
}

const size_t& Element::getAtomicNumber() const
{
    return atomicNumber_;
}

const std::vector<libaas::Isotope>& Element::getIsotopes() const
{
    return isotopes_;
}

bool Element::operator==(const Element& s) const
{
    return s.id_ == id_ && s.symbol_ == symbol_ && s.atomicNumber_
            == atomicNumber_ && s.isotopes_ == isotopes_;
}

std::ostream& operator<<(std::ostream& os, const Element& o) {
    os << o.getId() << ":" << o.getSymbol() << "(" << o.getAtomicNumber() << ") - ";
    typedef std::vector<Isotope>::const_iterator IT;
    for (IT it = o.getIsotopes().begin(); it != o.getIsotopes().end(); ++it) {
        os << "(" << *it << ")";
    }
    return os;
}

//istream& operator>>(std::istream& is, Element& i) {
//    return is;
//}

} // namespace libaas
