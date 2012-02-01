/*
 * Stoichiometry.hpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2009, 2010, 2011, 2012 Marc Kirchner
 * Copyright (c) 2010 Nathan Hueksen
 * Copyright (c) 2008 Thorben Kroeger
 *
 */

#ifndef __LIBAAS_INCLUDE_AAS_STOICHIOMETRY_HPP__
#define __LIBAAS_INCLUDE_AAS_STOICHIOMETRY_HPP__

#include "aas/StoichiometryConfig.hpp"
#include "aas/Element.hpp"
#include "aas/Types.hpp"

#include <map>
#include <vector>
#include <iostream>

namespace aas {
namespace stoichiometries {

/**Representation of a stoichiometry.
 *
 * This class ensures that no element with count 0 exists in the mapping.
 */
class Stoichiometry
{

public:

    /** Convenience typedef of the data type.
     */
    typedef std::map<aas::elements::Element, Double> DataType;
    /** Convenience typedef of the data type const_iterator.
     */
    typedef DataType::const_iterator const_iterator;
    /** Convenience typedef of the data type iterator.
     */
    typedef DataType::iterator iterator;
    /** Convenience typedef of the data type value_type.
     */
    typedef DataType::value_type value_type;

    /** Creates an empty stoichiometry.
     * The annotation id is set to 0.
     */
    Stoichiometry();

    /**Sets the annotation id.
     * @param[in] id The annotation id
     */
    void setAnnotationId(const Int& id);

    /**Returns the annotation id.
     * @returns The annotation id
     */
    Int getAnnotationId(void) const;

    /**Clears the internal map.
     */
    void clear();

    /**Returns a const iterator referring to the first element in the stoichiometry.
     * @returns A const iterator to the beginning of the stoichiometry
     */
    const_iterator begin() const;

    /**Returns an iterator referring to the first element in the stoichiometry.
     * @returns An iterator to the beginning of the stoichiometry
     */
    iterator begin();

    /**Returns a const iterator referring to the past-the-end element in the stoichiometry.
     * @returns A const iterator to the element past the end of the stoichiometry
     */
    const_iterator end() const;

    /**Returns an iterator referring to the past-the-end element in the stoichiometry.
     * @returns An iterator to the element past the end of the stoichiometry
     */
    iterator end();

    /**Returns the number of elements in the stoichiometry.
     * @returns The number of elements that conform the stoichiometry content.
     */
    Size size() const;

    /**Returns whether the map container is empty, i.e. whether its size is 0.
     * @returns true if the vector size is 0, false otherwise.
     */
    Bool empty() const;

    /**Sets the count of an element.
     * @param[in] element The element
     * @param[in] count The count of the element
     */
    void set(const aas::elements::Element& element, const Double& count);

    /**Adds a certain amount of to an element.
     * In case the result is 0 the element is delted from the stoichiometry.
     * @param[in] element The element
     * @param[in] count The count of the element
     */
    void add(const aas::elements::Element& element, const Double& count);

    /**Returns the count of the element with the specified elementId.
     * @param[in] element Element id
     * @returns 0.0 if the elementId is not present in the stoichiometry, the
     * count otherwise
     */
    Double get(const aas::elements::Element& element) const;

    /**Checks whether all entries in the stoichiometry are non negative.
     * @returns True if all elements in the stoichiometry are non negative,
     * false otherwise
     */
    Bool nonNegative() const;

    /**Returns a human readable string containing the chemical formula of the
     * stoichiometry i.e. H(36)C(20)N(7)O(12)P(1)S(3)
     * @returns A string representing the stoichiometry, without the isotopic
     * data from the elements
     */
    String toString() const;

    /**Applies a stoichiometry configuration to this stoichiometry.
     * @param[in] config Stoichiomtery configuration
     */
    void applyStoichiometryConfiguration(const StoichiometryConfig& config);

    /**Recalculates the stoichiometry with the given stoichiometry configurtions
     * and returns a copy the result.
     * @param[in] config Stoichiometry config which is used to recalculate the
     * stoichiometry
     * @returns A copy of the recalculates stoichiometry
     */
    Stoichiometry recalculatesWithConfiguration(
        const StoichiometryConfig& config) const;

    /**Adds the content of the argument to the stoichiometry and returns a new
     * stoichiometry.
     *
     * @param[in] s Stoichiometry object
     * @returns A copy of *this + s
     */
    Stoichiometry operator+(const Stoichiometry& s);

    /**Subtracts the content of the argument from the stoichiometry and retruns
     * a new stoichiometry object.
     * @param[in] s Stoichiometry object
     * @returns A copy of *this - s
     */
    Stoichiometry operator-(const Stoichiometry& s);

    /**Adds a copy of the argument to the stoichiometry.
     * The new stoichiometry content is the content existing in the
     * stoichiometry object before the call plus the content of the argument.
     * @param[in] s Stoichiometry object
     * @return *this
     */
    Stoichiometry& operator+=(const Stoichiometry& s);

    /**Subtracts a copy of the argument to the stoichiometry.
     * The new stoichiometry content is the content existing in the
     * stoichiometry object before the call minus the content of the argument.
     * @param[in] s Stoichiometry object
     * @return *this
     */
    Stoichiometry& operator-=(const Stoichiometry& s);

    /**Sets a copy of the argument as the new content for the stoichiometry object.
     * The previous content is dropped.
     * @param[in] s Stoichiometry to copy
     * @returns *this
     */
    Stoichiometry& operator=(const Stoichiometry& s);

    /**Compares the stoichiometry against another.
     * @param[in] s Stoichiometry object to compare *this with
     * @returns true if both residues are the same, false otherwise
     */
    bool operator==(const Stoichiometry &s) const;

    /**Compares the stoichiometry against another, with opposite result of
     * Stoichiometry::operator==.
     * @param[in] s Stoichiometry object to compare *this with
     * @returns true if the stoichiometries are different, false otherwise.
     */
    bool operator!=(const Stoichiometry &s) const;

private:

    /** Annotation id.
     */
    Int annotationId_;
    /** Internal mapping of aas::elements::Element to the amount.
     */
    DataType counts_;

};
// class Stoichiometry

std::ostream& operator<<(std::ostream& o, const aas::stoichiometries::Stoichiometry& s);
std::ostream& operator<<(std::ostream& o,
    const std::vector<aas::stoichiometries::Stoichiometry>& s);

inline void Stoichiometry::setAnnotationId(const Int& id)
{
    annotationId_ = id;
}

inline Int Stoichiometry::getAnnotationId(void) const
{
    return annotationId_;
}

} // namespace stoichiometries
} // namespace aas

#endif /* __LIBAAS_INCLUDE_AAS_STOICHIOMETRY_HPP__ */
