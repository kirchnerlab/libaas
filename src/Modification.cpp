/*
 * Modification.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Modification.hpp>

#include <stdexcept>

namespace libaas {
namespace modifications {

Modification::Modification() :
    modification_(""), stoichiometryConfig_(StoichiometryConfig(
            StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG))
{
    reinit();
}

Modification::Modification(const RawModification& modification) :
    modification_(modification), stoichiometryConfig_(StoichiometryConfig(
            StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG))
{
    reinit();
}

Modification::Modification(
        const RawModificationImpl::RawModificationImplKeyType& modid) :
    modification_(RawModification(modid)),
            stoichiometryConfig_(StoichiometryConfig(
                    StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG))
{
    reinit();
}

Modification::Modification(const RawModification& modification,
        const StoichiometryConfig& config) :
    modification_(modification), stoichiometryConfig_(config)
{
    reinit();
}

Modification::Modification(
        const RawModificationImpl::RawModificationImplKeyType& modid,
        const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid) :
    modification_(RawModification(modid)), stoichiometryConfig_(
            StoichiometryConfig(configid))
{
    reinit();
}

void Modification::setModification(const RawModification& modification)
{
    modification_ = modification;
    reinit();
}

void Modification::setModification(
        const RawModificationImpl::RawModificationImplKeyType& modid)
{
    modification_ = RawModification(modid);
    reinit();
}

const RawModification& Modification::getModification() const
{
    return modification_;
}

void Modification::setStoichiometryConfig(const StoichiometryConfig& config)
{
    stoichiometryConfig_ = config;
    recalculateStoichiometry();
}

void Modification::setStoichiometryConfig(
        const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid)
{
    stoichiometryConfig_ = StoichiometryConfig(configid);
    recalculateStoichiometry();
}

const StoichiometryConfig& Modification::getStoichiometryConfig() const
{
    return stoichiometryConfig_;
}

const Stoichiometry& Modification::getStoichiometry() const
{
    return stoichiometry_;
}

void Modification::addCustomSpecificity(const Specificity& specificity)
{
    customSpecificities_.push_back(specificity);
}

void Modification::setCustomSpecificities(
        const std::vector<Specificity>& specificities)
{
    customSpecificities_ = specificities;
}

const std::vector<Specificity> Modification::getSpecificities() const
{
    if (customSpecificities_.empty()) {
        return modification_.get().getSpecificities();
    }
    return customSpecificities_;
}

const std::vector<Specificity> Modification::getCustomSpecificities() const
{
    return customSpecificities_;
}

void Modification::clearCustomSpecificities()
{
    customSpecificities_.clear();
}

const RawModificationImpl::RawModificationImplKeyType& Modification::getModificationId() const
{
    return modification_.get().getId();
}

const String& Modification::getName() const
{
    return modification_.get().getName();
}

const String& Modification::getFullName() const
{
    return modification_.get().getFullName();
}

const std::vector<String>& Modification::getAltNames() const
{
    return modification_.get().getAltNames();
}

const Stoichiometry& Modification::getRawStoichiometry() const
{
    return modification_.get().getStoichiometry();
}

const std::vector<Specificity>& Modification::getRawSpecificities() const
{
    return modification_.get().getSpecificities();
}

Bool Modification::isVerified() const
{
    return modification_.get().isVerified();
}

void Modification::reinit()
{
    customSpecificities_.clear();
    recalculateStoichiometry();
}

void Modification::recalculateStoichiometry()
{
    const Stoichiometry& rawStoichiometry =
            modification_.get().getStoichiometry();
    typedef Stoichiometry::const_iterator IT;
    typedef StoichiometryConfigImpl::const_iterator SCIT;

    StoichiometryConfig defaultConfig = StoichiometryConfig(
            StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG);

    stoichiometry_.clear();

    // iterate over all elements in rawStoichiometry
    for (IT it = rawStoichiometry.begin(); it != rawStoichiometry.end(); ++it) {
        elements::ElementImpl::ElementImplKeyType elementId = 0;
        const String& symbol = it->first.get().getSymbol();
        try {
            elementId = stoichiometryConfig_.get().getKeyForSymbol(symbol);
            stoichiometry_.set(libaas::elements::Element(elementId), it->second);
        } catch (std::out_of_range& e) {
            // cannot find symbol in custom map
            // searching symbol in default map
            try {
                elementId = defaultConfig.get().getKeyForSymbol(symbol);
                stoichiometry_.set(libaas::elements::Element(elementId),
                        it->second);
            } catch (std::out_of_range& e) {
                // cannot find symbol in default map
                throw std::out_of_range(
                        "Modification::recalculateStoichiometry(): Cannot find element symbol.");
            }
        }
    }
}

bool Modification::operator==(const Modification& s) const
{
    return modification_ == s.modification_ && stoichiometryConfig_
            == s.stoichiometryConfig_ && stoichiometry_ == s.stoichiometry_
            && customSpecificities_ == s.customSpecificities_;
}

bool Modification::operator!=(const Modification& m) const
{
    return !(operator ==(m));
}

Modification& Modification::operator=(const Modification& rhs)
{
    if (this != &rhs) {
        modification_ = rhs.getModification();
        stoichiometryConfig_ = rhs.getStoichiometryConfig();
        stoichiometry_ = rhs.getStoichiometry();
        customSpecificities_ = rhs.getCustomSpecificities();
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Modification& o)
{
    os << o.getModification() << "\t" << o.getStoichiometryConfig() << "\t"
            << o.getStoichiometry() << "\t" << o.getCustomSpecificities();
    return os;
}

} // namespace modifications
} // namespace libaas
