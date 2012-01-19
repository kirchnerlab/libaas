/*
 * Residue.cpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2011,2012 Marc Kirchner
 *
 */

#include <libaas/Residue.hpp>
#include <libaas/Error.hpp>

#include <boost/make_shared.hpp>

#include <stdio.h>
#include <sstream>

namespace libaas {

Residue::ModificationPtr Residue::EMPTY_MOD;

Residue::Residue(
    const libaas::aminoAcids::RawAminoAcidImpl::RawAminoAcidImplKeyType& aminoAcidKey,
    const libaas::modifications::RawModificationImpl::RawModificationImplKeyType& modificationKey,
    const libaas::modifications::RawModificationImpl::RawModificationImplKeyType& labelKey) :
        aminoacid_(aminoAcidKey), modification_(
            boost::make_shared<modifications::Modification>()), isotopicLabel_(
            boost::make_shared<modifications::Modification>())
{
    if (!EMPTY_MOD.get()) {
        EMPTY_MOD = ModificationPtr(new modifications::Modification(""));
    }
    if (modificationKey != "") {
        modification_ = ModificationPtr(
            new modifications::Modification(modificationKey));
    } else {
        modification_ = EMPTY_MOD;
    }
    if (labelKey != "") {
        isotopicLabel_ = ModificationPtr(
            new modifications::Modification(labelKey));
    } else {
        isotopicLabel_ = EMPTY_MOD;
    }
}

Residue::Residue(const libaas::aminoAcids::AminoAcid& aminoAcid,
    const libaas::modifications::Modification& mod,
    const libaas::modifications::Modification& label) :
        aminoacid_(aminoAcid), modification_(
            boost::make_shared<modifications::Modification>()), isotopicLabel_(
            boost::make_shared<modifications::Modification>())
{
    if (!EMPTY_MOD.get()) {
        EMPTY_MOD = ModificationPtr(new modifications::Modification(""));
    }
    if (mod.getModificationId() != "") {
        modification_ = ModificationPtr(new modifications::Modification(mod));
    } else {
        modification_ = EMPTY_MOD;
    }
    if (label.getModificationId() != "") {
        isotopicLabel_ = ModificationPtr(
            new modifications::Modification(label));
    } else {
        isotopicLabel_ = EMPTY_MOD;
    }
}

Residue::~Residue()
{
}

void Residue::changeType(
    const aminoAcids::RawAminoAcidImpl::RawAminoAcidImplKeyType& aminoAcidKey)
{
    aminoacid_ = libaas::aminoAcids::AminoAcid(aminoAcidKey);
}

void Residue::changeType(const aminoAcids::AminoAcid& aminoAcid)
{
    aminoacid_ = aminoAcid;
}

Bool Residue::hasModification(
    const modifications::RawModificationImpl::RawModificationImplKeyType& modificationKey) const
{
    return modification_->getModificationId() == modificationKey;
}

Bool Residue::hasModification(
    const modifications::Modification& modification) const
{
    return *modification_ == modification;
}

Bool Residue::isModified() const
{
    return modification_->getModificationId() != "";
}

Bool Residue::hasLabel(
    const modifications::RawModificationImpl::RawModificationImplKeyType& labelKey) const
{
    return isotopicLabel_->getModificationId() == labelKey;
}

Bool Residue::hasLabel(const modifications::Modification& label) const
{
    return *isotopicLabel_ == label;
}

Bool Residue::isLabeled() const
{
    return isotopicLabel_->getModificationId() != "";
}

void Residue::removeModification()
{
    modification_ = EMPTY_MOD;
}

void Residue::removeIsotopicLabel()
{
    isotopicLabel_ = EMPTY_MOD;
}

void Residue::applyAminoAcidStoichiometryConfig(
    const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configKey)
{
    aminoacid_.setStoichiometryConfig(configKey);
}

void Residue::applyAminoAcidStoichiometryConfig(
    const StoichiometryConfig& config)
{
    aminoacid_.setStoichiometryConfig(config);
}

void Residue::applyModificationStoichiometryConfig(
    const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configKey)
{
    if (modification_ != NULL) {
        modification_->setStoichiometryConfig(configKey);
    }
}

void Residue::applyModificationStoichiometryConfig(
    const StoichiometryConfig& config)
{
    if (modification_ != NULL) {
        modification_->setStoichiometryConfig(config);
    }
}

void Residue::applyIsotopicLabelStoichiometryConfig(
    const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configKey)
{
    if (isotopicLabel_ != NULL) {
        isotopicLabel_->setStoichiometryConfig(configKey);
    }
}

void Residue::applyIsotopicLabelStoichiometryConfig(
    const StoichiometryConfig& config)
{
    if (isotopicLabel_ != NULL) {
        isotopicLabel_->setStoichiometryConfig(config);
    }
}

Stoichiometry Residue::getStoichiometry() const
{
    // MAYBE optimize by storing the stoichiometry
    Stoichiometry s = aminoacid_.getStoichiometry();
    if (modification_ != NULL) {
        s += modification_->getStoichiometry();
    }
    if (isotopicLabel_ != NULL) {
        s += isotopicLabel_->getStoichiometry();
    }
    return s;
}

String Residue::toString() const
{
    std::ostringstream oss;
    oss << aminoacid_.getSymbol();
    if (isModified()) {
        oss << "(" << modification_->getModificationId() << ")";
    }
    return oss.str();
}

libaas::Bool Residue::isNTerm() const
{
    return aminoacid_.isNTerm();
}

libaas::Bool Residue::isCTerm() const
{
    return aminoacid_.isCTerm();
}

const libaas::aminoAcids::AminoAcid& Residue::getAminoAcid() const
{
    return aminoacid_;
}

libaas::aminoAcids::AminoAcid& Residue::getAminoAcid()
{
    return aminoacid_;
}

void Residue::setModification(
    const libaas::modifications::RawModificationImpl::RawModificationImplKeyType& modificationKey)
{
    setModification(modifications::Modification(modificationKey));
}

void Residue::setModification(
    const libaas::modifications::Modification& modification)
{
    if (!modification.isIsotopicLabel()) {
        modification_ = ModificationPtr(
            new modifications::Modification(modification));
    } else {
        libaas_logic_error(
            "Residue::setModification(): Given modification is an isotopic label. use setIsotopicLabel() instead.");
    }
}

const Residue::ModificationPtr& Residue::getModification() const
{
    return modification_;
}

void Residue::setIsotopicLabel(
    const libaas::modifications::RawModificationImpl::RawModificationImplKeyType& isotopicLabelKey)
{
    setIsotopicLabel(modifications::Modification(isotopicLabelKey));
}

void Residue::setIsotopicLabel(
    const libaas::modifications::Modification& isotopicLabel)
{
    if (isotopicLabel.isIsotopicLabel()) {
        isotopicLabel_ = ModificationPtr(
            new modifications::Modification(isotopicLabel));
    } else {
        libaas_logic_error(
            "Residue::setIsotopicLabel(): Given isotopic label is a standard modification. Use setModification() instead.");
    }
}

const Residue::ModificationPtr& Residue::getIsotopicLabel() const
{
    return isotopicLabel_;
}

Residue& Residue::operator=(const Residue& rhs)
{
    if (this != &rhs) {
        aminoacid_ = rhs.aminoacid_;
        modification_ = rhs.modification_;
        isotopicLabel_ = rhs.isotopicLabel_;
    }
    return *this;
}

bool Residue::operator==(const Residue& r) const
{
    return aminoacid_ == r.aminoacid_ && *modification_ == *r.modification_
            && *isotopicLabel_ == *r.isotopicLabel_;
}

bool Residue::operator!=(const Residue& r) const
{
    return !(operator ==(r));
}

std::ostream& operator<<(std::ostream& os, const Residue& o)
{
    os << o.getAminoAcid() << "\t" << o.getModification() << "\t"
            << o.getIsotopicLabel();
    return os;
}

} // namespace libaas
