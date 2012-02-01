/*
 * AminoAcid.hpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2011,2012 Marc Kirchner
 *
 */

#include "aas/AminoAcid.hpp"

namespace aas {
namespace aminoAcids {

AminoAcid::AminoAcid(
    const RawAminoAcidImpl::RawAminoAcidImplKeyType& aminoAcidKey,
    const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid) :
        rawAminoAcid_(aminoAcidKey), stoichiometryConfig_(configid)
{
}

AminoAcid::AminoAcid(const RawAminoAcid& aminoAcid,
    const StoichiometryConfig& config) :
        rawAminoAcid_(aminoAcid), stoichiometryConfig_(config)
{
}

Char AminoAcid::getSymbol() const
{
    return rawAminoAcid_.get().getSymbol();
}

const RawAminoAcidImpl::RawAminoAcidImplKeyType& AminoAcid::getRawAminoAcidKey() const
{
    return rawAminoAcid_.get_key();
}

const RawAminoAcid& AminoAcid::getRawAminoAcid() const
{
    return rawAminoAcid_;
}

const String& AminoAcid::getThreeLetterCode() const
{
    return rawAminoAcid_.get().getThreeLetterCode();
}

const String& AminoAcid::getFullName() const
{
    return rawAminoAcid_.get().getFullName();
}

aas::Bool AminoAcid::isNTerm() const
{
    return rawAminoAcid_.get().isNTerm();
}

aas::Bool AminoAcid::isCTerm() const
{
    return rawAminoAcid_.get().isCTerm();
}

Stoichiometry AminoAcid::getStoichiometry() const
{
    if (stoichiometryConfig_.get_key()
            == StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG) {
        return rawAminoAcid_.get().getStoichiometry();
    }
    return rawAminoAcid_.get().getStoichiometry().recalculatesWithConfiguration(
        stoichiometryConfig_);
}

void AminoAcid::setStoichiometryConfig(const StoichiometryConfig& config)
{
    if (&config != &stoichiometryConfig_) {
        stoichiometryConfig_ = config;
    }
}

void AminoAcid::setStoichiometryConfig(
    const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid)
{
    StoichiometryConfig config(configid);
    if (&config != &stoichiometryConfig_) {
        stoichiometryConfig_ = config;
    }
}

const StoichiometryConfig& AminoAcid::getStoichiometryConfig() const
{
    return stoichiometryConfig_;
}

AminoAcid& AminoAcid::operator=(const AminoAcid& a)
{
    if (this != &a) {
        rawAminoAcid_ = a.rawAminoAcid_;
        stoichiometryConfig_ = a.stoichiometryConfig_;
    }
    return *this;
}

bool AminoAcid::operator==(const AminoAcid& a) const
{
    return rawAminoAcid_ == a.rawAminoAcid_
            && stoichiometryConfig_ == a.stoichiometryConfig_;
}

bool AminoAcid::operator!=(const AminoAcid& a) const
{
    return !(operator ==(a));
}

std::ostream& operator<<(std::ostream& os, const AminoAcid& a)
{
    os << a.getRawAminoAcid();
    os << a.getStoichiometry();
    return os;
}

} // namespace aminoAcids
} // namespace aas
