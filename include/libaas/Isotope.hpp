/*
 * Isotope.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_LIBAAS_ISOTOPE_HPP__
#define __LIBAAS_INCLUDE_LIBAAS_ISOTOPE_HPP__

#include <libaas/Types.hpp>

#include <vector>
#include <iostream>

namespace libaas {
namespace elements {

/**Representation of an isotope.
 */
class Isotope
{

public:
    /** Default constructor.
     * @param[in] mass Mass
     * @param[in] frequency Frequency
     */
    Isotope(const Double& mass, const Double& frequency);

    /**Returns the mass of the isotope.
     * @returns Mass of the isotope.
     */
    const Double& getMass() const;

    /**Returns the frequency of the isotope.
     * @returns Frequency of the isotope.
     */
    const Double& getFrequency() const;

    /**Sets a copy of the argument as the new content for the isotope object.
     * The previous content is dropped.
     * @param[in] rhs Isotope to copy
     * @returns *this
     */
    Isotope& operator=(const Isotope& rhs);

    /**Compares the isotope against another.
     * @param[in] i Isotope object to compare *this with
     * @returns true if both isotopes are the same, false otherwise
     */
    bool operator==(const Isotope& i) const;

    /**Compares the isotope against another, with opposite result of
     * Isotope::operator==.
     * @param[in] i Isotope object to compare *this with
     * @returns true if the isotopes are different, false otherwise.
     */
    bool operator!=(const Isotope& i) const;

private:

    /** Mass of the isotope.
     */
    Double mass_;
    /** Frequency of the isotope.
     */
    Double frequency_;

};
// class Isotope

std::ostream& operator<<(std::ostream&, const Isotope&);
std::ostream& operator<<(std::ostream&, const std::vector<Isotope>&);

} // namespace elements
} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_ISOTOPE_HPP__ */
