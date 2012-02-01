/*
 * LibIPACA.hpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2011,2012 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_AAS_LIBIPACA_HPP__
#define __LIBAAS_INCLUDE_AAS_LIBIPACA_HPP__

#include "aas/Stoichiometry.hpp"
#include "aas/Element.hpp"

#include <ipaca/Spectrum.hpp>
#include <ipaca/Stoichiometry.hpp>
#include <ipaca/Traits.hpp>
#include <ipaca/Types.hpp>

#include <vector>

namespace aas {
namespace adapter {

typedef ipaca::detail::Spectrum LibaasSpectrum;
typedef aas::stoichiometries::Stoichiometry LibaasStoichiometry;

struct SpectrumConverter
{
    void operator()(const ipaca::detail::Spectrum& lhs, LibaasSpectrum& rhs)
    {
        rhs = lhs;
    }
};

struct ElementConverter
{
    void operator()(const aas::elements::Element& lhs,
        ipaca::detail::Element& rhs)
    {
        rhs.count = 0.0;
        rhs.isotopes.clear();
        typedef std::vector<aas::elements::Isotope> AASIsotopeList;
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
        typedef std::vector<aas::elements::Isotope>::const_iterator IIT;
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
} // namespace aas

namespace ipaca {

template<>
struct Traits<aas::adapter::LibaasStoichiometry, aas::adapter::LibaasSpectrum>
{
    typedef aas::adapter::SpectrumConverter spectrum_converter;
    typedef aas::adapter::StoichiometryConverter stoichiometry_converter;
    static ipaca::detail::Element getHydrogens(const ipaca::Size n);
    static ipaca::Bool isHydrogen(const ipaca::detail::Element&);
    static ipaca::Double getElectronMass();
};

ipaca::detail::Element Traits<aas::adapter::LibaasStoichiometry,
        aas::adapter::LibaasSpectrum>::getHydrogens(const ipaca::Size n)
{
    ipaca::detail::Element h;
    aas::adapter::ElementConverter ec;
    ec(aas::elements::Element(1), h);
    h.count = static_cast<Double>(n);
    return h;
}

ipaca::Bool Traits<aas::adapter::LibaasStoichiometry,
        aas::adapter::LibaasSpectrum>::isHydrogen(
    const ipaca::detail::Element& e)
{
    ipaca::detail::Element h;
    aas::adapter::ElementConverter ec;
    ec(aas::elements::Element(1), h);
    typedef std::vector<ipaca::detail::Isotope>::const_iterator IT;
    for (IT et = e.isotopes.begin(), ht = h.isotopes.begin();
            et != e.isotopes.end() && ht != h.isotopes.end(); ++et, ++ht) {
        if (et->ab != ht->ab || et->mz != ht->mz) {
            return false;
        }
    }
    return true;
}

ipaca::Double Traits<aas::adapter::LibaasStoichiometry,
        aas::adapter::LibaasSpectrum>::getElectronMass()
{
    return ipaca::detail::getElectronMass();
}

} // namespace ipaca

#endif /* __LIBAAS_INCLUDE_AAS_LIBIPACA_HPP__ */
