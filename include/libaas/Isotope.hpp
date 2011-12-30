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
class Isotope {

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

    bool operator==(const Isotope& s) const;
    bool operator!=(const Isotope& s) const;
    Isotope& operator=(const Isotope& rhs);

private:
    Double mass_;
    Double frequency_;

}; // class Isotope

std::ostream& operator<<(std::ostream&, const Isotope&);
std::ostream& operator<<(std::ostream&, const std::vector<Isotope>&);

} // namespace elements
} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_ISOTOPE_HPP__ */
