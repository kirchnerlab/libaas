/*
 * FlyWeightReplacement.hpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2011,2012 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_AAS_FLYWEIGHTREPLACEMENT_HPP__
#define __LIBAAS_INCLUDE_AAS_FLYWEIGHTREPLACEMENT_HPP__

#include <iostream>

namespace aas {

template<typename T, typename Tk>
class FlyWeightReplacement
{
public:

    FlyWeightReplacement() :
            t_()
    {
    }

    FlyWeightReplacement(const T& t) :
            t_(t)
    {
    }

    FlyWeightReplacement(const Tk& k) :
            t_(k)
    {
    }

    const T& get() const
    {
        return t_;
    }

    const Tk& get_key() const
    {
        return t_.getId();
    }

    bool operator==(const T& t) const
    {
        return t_ == t;
    }

    bool operator==(const FlyWeightReplacement<T, Tk>& a) const
    {
        return t_ == a.t_;
    }

protected:
    T t_;
};
template<typename T, typename Tk>
std::ostream& operator<<(std::ostream& os,
    const FlyWeightReplacement<T, Tk>& e)
{
    os << e.get();
    return os;
}

}

#endif /* __LIBAAS_INCLUDE_AAS_FLYWEIGHTREPLACEMENT_HPP__ */
