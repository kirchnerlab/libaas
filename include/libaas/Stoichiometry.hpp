/*
 * Stoichiometry.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 *
 */

#ifndef __X_INCLUDE_X_STOICHIOMETRY_HPP__
#define __X_INCLUDE_X_STOICHIOMETRY_HPP__

#include <libaas/Element.hpp>

#include <map>
//#include <iostream>

namespace libaas {

/** Stoichiometry
 *
 */
class Stoichiometry {

public:

    /** Constructor
     *
     */
    Stoichiometry();

    //bool operator==(const Stoichiometry& s) const;
    //Stoichiometry& operator=(const Stoichiometry& rhs);

private:

    //std::map<Element::ElementRef, double> counts_;

}; // class Stoichiometry

//std::ostream& operator<<(std::ostream&, const Stoichiometry&);
//istream& operator>>(std::istream&, Stoichiometry&);

} // namespace libaas

#endif /* __X_INCLUDE_X_STOICHIOMETRY_HPP__ */
