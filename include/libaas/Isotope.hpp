/*
 * Isotope.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 *
 */

#ifndef __X_INCLUDE_X_ISOTOPE_HPP__
#define __X_INCLUDE_X_ISOTOPE_HPP__

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
	Isotope(const double& mass, const double& frequency);

	const double& getMass() const;
	const double& getFrequency() const;

	bool operator==(const Isotope& s) const;
	//Isotope& operator=(const Isotope& rhs);

private:
    double mass_;
    double frequency_;

}; // class Isotope

std::ostream& operator<<(std::ostream&, const Isotope&);
//istream& operator>>(std::istream&, Isotope&);

} // namespace libaas

#endif /* __X_INCLUDE_X_ISOTOPE_HPP__ */
