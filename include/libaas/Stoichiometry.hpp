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
#include <vector>
#include <iostream>

namespace libaas {

/** Stoichiometry
 *
 */
class Stoichiometry {

public:

    typedef std::map<libaas::Element, double>::const_iterator const_iterator;
    typedef std::map<libaas::Element, double>::iterator iterator;
    typedef std::map<libaas::Element, double>::value_type value_type;

    /** Constructor
     *
     */
    Stoichiometry();

    void setAnnotationId(const int& id);
    int getAnnotationId(void) const;

    virtual void clear();

    const_iterator begin() const;
    iterator begin();
    const_iterator end() const;
    iterator end();

    size_t size() const;
    bool empty() const;
    bool zero() const;

    double get(const libaas::Element& elementId) const;
    void set(const libaas::Element& elementId, const double& count);
    void add(const libaas::Element& elementId, const double& count);

    bool nonNegative() const;

    Stoichiometry operator+(const Stoichiometry& s);
    Stoichiometry operator-(const Stoichiometry& s);
    Stoichiometry& operator+=(const Stoichiometry& s);
    Stoichiometry& operator-=(const Stoichiometry& s);
    Stoichiometry& operator=(const Stoichiometry& s);
    bool operator==(const Stoichiometry &s) const;
    bool operator!=(const Stoichiometry &s) const;

private:

    int annotationId_;
    std::map<libaas::Element, double> counts_;

}; // class Stoichiometry

std::ostream& operator<<(std::ostream& o, const libaas::Stoichiometry& s);
std::ostream& operator<<(std::ostream& o, const std::vector<
        libaas::Stoichiometry>& s);

//istream& operator>>(std::istream&, Stoichiometry&);

inline void Stoichiometry::setAnnotationId(const int& id)
{
    annotationId_ = id;
}

inline int Stoichiometry::getAnnotationId(void) const
{
    return annotationId_;
}

} // namespace libaas

#endif /* __X_INCLUDE_X_STOICHIOMETRY_HPP__ */
