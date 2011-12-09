/*
 * Stoichiometry.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2009, 2010, 2011 Marc Kirchner
 * Copyright (c) 2010 Nathan Hueksen
 * Copyright (c) 2008 Thorben Kroeger
 *
 */

#ifndef __X_INCLUDE_X_STOICHIOMETRY_HPP__
#define __X_INCLUDE_X_STOICHIOMETRY_HPP__

#include <libaas/Element.hpp>
#include <libaas/Types.hpp>

#include <map>
#include <vector>
#include <iostream>

namespace libaas {

/** Stoichiometry
 *
 */
class Stoichiometry {

public:

    typedef std::map<libaas::elementTable::Element, Double>::const_iterator const_iterator;
    typedef std::map<libaas::elementTable::Element, Double>::iterator iterator;
    typedef std::map<libaas::elementTable::Element, Double>::value_type value_type;

    /** Constructor
     *
     */
    Stoichiometry();

    void setAnnotationId(const Int& id);
    Int getAnnotationId(void) const;

    virtual void clear();

    const_iterator begin() const;
    iterator begin();
    const_iterator end() const;
    iterator end();

    Size size() const;
    Bool empty() const;
    Bool zero() const;

    Double get(const libaas::elementTable::Element& elementId) const;
    void set(const libaas::elementTable::Element& elementId, const Double& count);
    void add(const libaas::elementTable::Element& elementId, const Double& count);

    Bool nonNegative() const;

    Stoichiometry operator+(const Stoichiometry& s);
    Stoichiometry operator-(const Stoichiometry& s);
    Stoichiometry& operator+=(const Stoichiometry& s);
    Stoichiometry& operator-=(const Stoichiometry& s);
    Stoichiometry& operator=(const Stoichiometry& s);
    bool operator==(const Stoichiometry &s) const;
    bool operator!=(const Stoichiometry &s) const;

private:

    Int annotationId_;
    std::map<libaas::elementTable::Element, Double> counts_;

}; // class Stoichiometry

// TODO maybe we should add << for vector<type> for all our classes?

std::ostream& operator<<(std::ostream& o, const libaas::Stoichiometry& s);
std::ostream& operator<<(std::ostream& o, const std::vector<
        libaas::Stoichiometry>& s);

inline void Stoichiometry::setAnnotationId(const Int& id)
{
    annotationId_ = id;
}

inline Int Stoichiometry::getAnnotationId(void) const
{
    return annotationId_;
}

} // namespace libaas

#endif /* __X_INCLUDE_X_STOICHIOMETRY_HPP__ */
