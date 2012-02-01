/*
 * LibIPACA.hpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2011,2012 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_LIBAAS_LIBIPACA_HPP__
#define __LIBAAS_INCLUDE_LIBAAS_LIBIPACA_HPP__

#include "libaas/Stoichiometry.hpp"
#include "libaas/Element.hpp"

#include <ipaca/Spectrum.hpp>
#include <ipaca/Stoichiometry.hpp>
#include <ipaca/Traits.hpp>
#include <ipaca/Types.hpp>

#include <vector>

namespace libaas {
namespace adapter {

typedef ipaca::detail::Spectrum LibaasSpectrum;
typedef libaas::Stoichiometry LibaasStoichiometry;

struct SpectrumConverter
{
    void operator()(const ipaca::detail::Spectrum& lhs, LibaasSpectrum& rhs)
    {
        rhs = lhs;
    }
};

struct ElementConverter
{
    void operator()(const libaas::elements::Element& lhs,
        ipaca::detail::Element& rhs)
    {
        rhs.count = 0.0;
        rhs.isotopes.clear();
        typedef std::vector<libaas::elements::Isotope> AASIsotopeList;
        const AASIsotopeList& eis = lhs.get().getIsotopes();
        // TODO make sure isotopes are added sorted by mass!
        for (AASIsotopeList::const_iterator it = eis.begin(); it != eis.end();
                ++it) {
            ipaca::detail::Isotope i;
            i.ab = it->getFrequency();
            i.mz = it->getMass();
            rhs.isotopes.push_back(i);
        }
    }
};

struct StoichiometryConverter
{
    void operator()(const LibaasStoichiometry& lhs,
        ipaca::detail::Stoichiometry& rhs)
    {
        typedef LibaasStoichiometry::const_iterator SIT;
        typedef std::vector<libaas::elements::Isotope>::const_iterator IIT;
        ElementConverter ec;
        for (SIT it = lhs.begin(); it != lhs.end(); ++it) {
            ipaca::detail::Element e;
            ec(it->first, e);
            e.count = it->second;
            rhs.push_back(e);
        }
    }
};

} // namespace adapter
} // namespace libaas

namespace ipaca {

template<>
struct Traits<libaas::adapter::LibaasStoichiometry,
        libaas::adapter::LibaasSpectrum>
{
    typedef libaas::adapter::SpectrumConverter spectrum_converter;
    typedef libaas::adapter::StoichiometryConverter stoichiometry_converter;
    static ipaca::detail::Element getHydrogens(const ipaca::Size n);
    static ipaca::Bool isHydrogen(const ipaca::detail::Element&);
    static ipaca::Double getElectronMass();
};

ipaca::detail::Element Traits<
        libaas::adapter::LibaasStoichiometry, libaas::adapter::LibaasSpectrum>::getHydrogens(
    const ipaca::Size n)
{
    ipaca::detail::Element h;
    libaas::adapter::ElementConverter ec;
    ec(libaas::elements::Element(1), h);
    h.count = static_cast<Double>(n);
    return h;
}

ipaca::Bool Traits<libaas::adapter::LibaasStoichiometry,
        libaas::adapter::LibaasSpectrum>::isHydrogen(
    const ipaca::detail::Element& e)
{
    ipaca::detail::Element h;
    libaas::adapter::ElementConverter ec;
    ec(libaas::elements::Element(1), h);
    typedef std::vector<ipaca::detail::Isotope>::const_iterator IT;
    for (IT et = e.isotopes.begin(), ht = h.isotopes.begin();
            et != e.isotopes.end() && ht != h.isotopes.end(); ++et, ++ht) {
        if (et->ab != ht->ab || et->mz != ht->mz) {
            return false;
        }
    }
    return true;
}

ipaca::Double Traits<libaas::adapter::LibaasStoichiometry,
        libaas::adapter::LibaasSpectrum>::getElectronMass()
{
    return ipaca::detail::getElectronMass();
}

} // namespace ipaca

#endif /* __LIBAAS_INCLUDE_LIBAAS_LIBIPACA_HPP__ */
