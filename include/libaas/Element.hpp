/*
 * Element.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 *
 */

#ifndef __X_INCLUDE_X_ELEMENT_HPP__
#define __X_INCLUDE_X_ELEMENT_HPP__

#include <libaas/Isotope.hpp>

#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/flyweight/no_tracking.hpp>

#include <string>
#include <vector>
#include <iostream>

namespace libaas {

// forward definition
struct element_id_extractor;

/** Element
 *
 *  store isotopes as set?
 */
class Element {

public:

//    struct Isotope {
//        double mass;
//        double frequency;
//
//        bool operator==(const Isotope& s) const;
//    };

    typedef size_t ElementKeyType;
    typedef boost::flyweight<boost::flyweights::key_value<
            libaas::Element::ElementKeyType, libaas::Element,
            libaas::element_id_extractor>, boost::flyweights::no_tracking>
            ElementRef;

    /** Constructor
     *
     */
    Element(ElementKeyType id);

    const ElementKeyType& getId() const;
    const std::string& getSymbol() const;
    const size_t& getAtomicNumber() const;
    const std::vector<Isotope>& getIsotopes() const;

    bool operator==(const Element& s) const;
    //Element& operator=(const Element& rhs);

private:

    ElementKeyType id_;
    std::string symbol_;
    size_t atomicNumber_;
    std::vector<libaas::Isotope> isotopes_;

}; // class Element

struct element_id_extractor {
    const Element::ElementKeyType& operator()(const Element& e) const
    {
        return e.getId();
    }
};

std::ostream& operator<<(std::ostream&, const Element&);
//istream& operator>>(std::istream&, Element&);

} // namespace libaas

#endif /* __X_INCLUDE_X_ELEMENT_HPP__ */
