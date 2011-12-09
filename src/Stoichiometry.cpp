/*
 * Stoichiometry.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2010 Nathan Hueksen
 * Copyright (c) 2009,2010 Marc Kirchner
 * Copyright (c) 2008 Thorben Kroeger
 *
 */

#include <libaas/Stoichiometry.hpp>

namespace libaas {

/** Constructor
 *
 */
Stoichiometry::Stoichiometry() :
    annotationId_(0), counts_()
{
}

void Stoichiometry::clear()
{
    counts_.clear();
    annotationId_ = 0;
}

Stoichiometry::const_iterator Stoichiometry::begin() const
{
    return counts_.begin();
}

Stoichiometry::iterator Stoichiometry::begin()
{
    return counts_.begin();
}

Stoichiometry::const_iterator Stoichiometry::end() const
{
    return counts_.end();
}

Stoichiometry::iterator Stoichiometry::end()
{
    return counts_.end();
}

Bool Stoichiometry::empty() const
{
    return counts_.empty();
}

Size Stoichiometry::size() const
{
    return counts_.size();
}

Bool Stoichiometry::zero() const
{
    // Since it is assured that no elements with count = 0 exist
    // this is the same as empty
    return empty();
}

Double Stoichiometry::get(const Element& element) const
{
    const_iterator elem = counts_.find(element);
    if (elem == counts_.end()) {
        return 0.0; // Not found, so zero atoms present
    } else {
        return elem->second;
    }
}

void Stoichiometry::set(const Element& element, const Double& count)
{
    if (count == 0.0) {
        counts_.erase(element); // Not in here has the same meaning as count =0
    } else {
        counts_[element] = count;
    }
}

void Stoichiometry::add(const Element& element, const Double& count) {
    Double& c = counts_[element];
    c += count;
    if (c == 0.0) {
        counts_.erase(element); // Not present has the same meaning as count = 0
    }
}

Bool Stoichiometry::nonNegative() const
{
    const_iterator iter;
    for (iter = counts_.begin(); iter != counts_.end(); ++iter) {
        if (iter->second < 0.0) {
            return false;
        }
    }
    return true;
}

Stoichiometry& Stoichiometry::operator=(const Stoichiometry& s)
{
    if (this != &s) {
        annotationId_ = s.annotationId_;
        counts_ = s.counts_;
    }
    return *this;
}

bool Stoichiometry::operator==(const Stoichiometry& s) const
{
    // Since it is assured, that no zero elements exists,
    // the stoichiometries are equal if the maps are equal
    return counts_ == s.counts_;
}

bool Stoichiometry::operator!=(const Stoichiometry& s) const
{
    return !operator==(s);
}

Stoichiometry& Stoichiometry::operator+=(const Stoichiometry& s)
{
    const_iterator other_iter = s.counts_.begin();
    for (other_iter = s.begin(); other_iter != s.end(); ++other_iter) {
        add(other_iter->first, other_iter->second);
    }
    return *this;
}

Stoichiometry Stoichiometry::operator+(const Stoichiometry& s)
{
    Stoichiometry stoi = *this; // Make a copy
    stoi += s;
    return stoi;
}

Stoichiometry& Stoichiometry::operator-=(const Stoichiometry& s)
{
    const_iterator other_iter = s.begin();
    for (other_iter = s. begin(); other_iter != s.end(); ++other_iter) {
        add(other_iter->first, -other_iter->second);
    }
    return *this;
}

Stoichiometry Stoichiometry::operator-(const Stoichiometry& s)
{
    Stoichiometry stoi = *this; //Make a copy
    stoi -= s;
    return stoi;
}

std::ostream& operator<<(std::ostream& o, const libaas::Stoichiometry& s)
{
    for (Stoichiometry::const_iterator it = s.begin(); it != s.end(); ++it) {
        o << "(" << it->first << ")" << it->second << " ";
    }
    o << '[' << s.getAnnotationId() << ']';
    return o;
}

std::ostream& operator<<(std::ostream& o,
        const std::vector<libaas::Stoichiometry>& s)
{
    for (std::vector<Stoichiometry>::const_iterator it = s.begin(); it
            != s.end(); ++it) {
        o << *it << std::endl;
    }
    return o;
}

//istream& operator>>(std::istream& is, Stoichiometry& i) {
//    return is;
//}

} // namespace libaas
