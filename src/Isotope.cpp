/*
 * Isotope.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Isotope.hpp>

namespace libaas {

/** Constructor
 *
 */
Isotope::Isotope(const Double& mass, const Double& frequency) :
    mass_(mass), frequency_(frequency)
{
}

const Double& Isotope::getMass() const
{
    return mass_;
}
const Double& Isotope::getFrequency() const
{
    return frequency_;
}

bool Isotope::operator==(const Isotope& s) const
{
    return s.mass_ == mass_ && s.frequency_ == frequency_;
}

bool Isotope::operator!=(const Isotope& s) const
{
    return !(operator ==(s));
}

libaas::Isotope& Isotope::operator=(const Isotope& rhs)
{
    if (this != &rhs) {
        mass_ = rhs.mass_;
        frequency_ = rhs.frequency_;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Isotope& o)
{
    os << o.getMass() << "; " << o.getFrequency();
    return os;
}

//istream& operator>>(std::istream& is, Isotope& i) {
//    return is;
//}

} // namespace libaas
