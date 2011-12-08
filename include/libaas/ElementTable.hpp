/*
 * ElementTable.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 *
 */

#ifndef __X_INCLUDE_X_ELEMENTTABLE_HPP__
#define __X_INCLUDE_X_ELEMENTTABLE_HPP__

#include <libaas/Element.hpp>
#include <libaas/Isotope.hpp>

#include <string>
#include <vector>
//#include <iostream>

namespace libaas {

/** ElementTable
 *
 */
class ElementTable {

public:
    /** Constructor
     *
     */
    ElementTable();

    size_t getAtomicNumber(const Element::ElementKeyType& id);

    std::string getSymbol(const Element::ElementKeyType& id);

    void getIsotopes(const Element::ElementKeyType& id, std::vector<
            libaas::Isotope>& isotopes);

    //bool operator==(const ElementTable& s) const;
    //ElementTable& operator=(const ElementTable& rhs);

private:

}; // class ElementTable

//std::ostream& operator<<(std::ostream&, const ElementTable&);
//istream& operator>>(std::istream&, ElementTable&);

} // namespace libaas

#endif /* __X_INCLUDE_X_ELEMENTTABLE_HPP__ */
