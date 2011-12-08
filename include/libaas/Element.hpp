/*
 * Element.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 *
 */

#ifndef __X_INCLUDE_X_ELEMENTIMPL_HPP__
#define __X_INCLUDE_X_ELEMENTIMPL_HPP__

#include <libaas/Isotope.hpp>

#include <string>
#include <vector>
#include <iostream>

namespace libaas {

// forward definition
struct element_id_extractor;

/** Element
 *
 */
class ElementImpl {

public:

    typedef size_t ElementImplKeyType;
    //    typedef boost::flyweight<boost::flyweights::key_value<
    //            libaas::Element::ElementKeyType, libaas::Element,
    //            libaas::element_id_extractor>, boost::flyweights::no_tracking>
    //            ElementRef;

    /** Constructor
     *
     */
    ElementImpl(ElementImplKeyType id);
    ElementImpl(const ElementImplKeyType& id, const std::string& symbol,
            const size_t& atomicNumber);

    const ElementImplKeyType& getId() const;
    const std::string& getSymbol() const;
    const size_t& getAtomicNumber() const;
    const std::vector<Isotope>& getIsotopes() const;

    void addIsotope(const libaas::Isotope& i);
    void addIsotope(const double& mass, const double& frequency);
    void setIsotopes(const std::vector<libaas::Isotope>& isotopes);

    bool operator==(const ElementImpl& s) const;
    //Element& operator=(const Element& rhs);

    static ElementImplKeyType getNumberOfStandardElements();
    static ElementImplKeyType getNextId();

private:

    ElementImplKeyType id_;
    std::string symbol_;
    size_t atomicNumber_;
    std::vector<libaas::Isotope> isotopes_;

    static ElementImplKeyType freeId;

}; // class ElementImpl

struct element_id_extractor {
    const ElementImpl::ElementImplKeyType& operator()(const ElementImpl& e) const
    {
        return e.getId();
    }
};

std::ostream& operator<<(std::ostream&, const ElementImpl&);
//istream& operator>>(std::istream&, Element&);

} // namespace libaas

#endif /* __X_INCLUDE_X_ELEMENT_HPP__ */
