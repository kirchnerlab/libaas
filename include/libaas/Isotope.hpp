/*
 * Isotope.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __X_INCLUDE_X_ISOTOPE_HPP__
#define __X_INCLUDE_X_ISOTOPE_HPP__

#include <libaas/Types.hpp>

#include <iostream>

namespace libaas {

/** Isotope
 *
 */
class Isotope {

public:
    /** Constructor
     *
     */
    Isotope(const Double& mass, const Double& frequency);

    const Double& getMass() const;
    const Double& getFrequency() const;

    bool operator==(const Isotope& s) const;
    bool operator!=(const Isotope& s) const;
    Isotope& operator=(const Isotope& rhs);

private:
    Double mass_;
    Double frequency_;

}; // class Isotope

std::ostream& operator<<(std::ostream&, const Isotope&);
//istream& operator>>(std::istream&, Isotope&);

} // namespace libaas

#endif /* __X_INCLUDE_X_ISOTOPE_HPP__ */
