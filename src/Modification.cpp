/*
 * Modification.cpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2011,2012 Marc Kirchner
 *
 */

#include <libaas/Modification.hpp>

#include <stdexcept>

namespace libaas {
namespace modifications {

Modification::Modification(const RawModification& modification,
		const StoichiometryConfig& config) :
		modification_(modification), stoichiometryConfig_(config), stoichiometry_(), customSpecificities_() {
	reinit();
}

Modification::Modification(
		const RawModificationImpl::RawModificationImplKeyType& modid,
		const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid) :
		modification_(RawModification(modid)), stoichiometryConfig_(
				StoichiometryConfig(configid)), stoichiometry_(), customSpecificities_() {
	reinit();
}

void Modification::setModification(const RawModification& modification) {
	modification_ = modification;
	reinit();
}

void Modification::setModification(
		const RawModificationImpl::RawModificationImplKeyType& modid) {
	modification_ = RawModification(modid);
	reinit();
}

const RawModification& Modification::getModification() const {
	return modification_;
}

void Modification::setStoichiometryConfig(const StoichiometryConfig& config) {
	if (&config != &stoichiometryConfig_) {
		stoichiometryConfig_ = config;
		recalculateStoichiometry();
	}
}

void Modification::setStoichiometryConfig(
		const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid) {
	StoichiometryConfig config(configid);
	if (&config != &stoichiometryConfig_) {
		stoichiometryConfig_ = config;
		recalculateStoichiometry();
	}
}

const StoichiometryConfig& Modification::getStoichiometryConfig() const {
	return stoichiometryConfig_;
}

const Stoichiometry& Modification::getStoichiometry() const {
	return stoichiometry_;
}

void Modification::addCustomSpecificity(const Specificity& specificity) {
	customSpecificities_.push_back(specificity);
}

void Modification::setCustomSpecificities(
		const std::vector<Specificity>& specificities) {
	customSpecificities_ = specificities;
}

const std::vector<Specificity> Modification::getSpecificities() const {
	if (customSpecificities_.empty()) {
		return modification_.get().getSpecificities();
	}
	return customSpecificities_;
}

const std::vector<Specificity> Modification::getCustomSpecificities() const {
	return customSpecificities_;
}

void Modification::clearCustomSpecificities() {
	customSpecificities_.clear();
}

const RawModificationImpl::RawModificationImplKeyType& Modification::getModificationId() const {
	return modification_.get().getId();
}

const String& Modification::getName() const {
	return modification_.get().getName();
}

const String& Modification::getFullName() const {
	return modification_.get().getFullName();
}

const std::vector<String>& Modification::getAltNames() const {
	return modification_.get().getAltNames();
}

const Stoichiometry& Modification::getRawStoichiometry() const {
	return modification_.get().getStoichiometry();
}

const std::vector<Specificity>& Modification::getRawSpecificities() const {
	return modification_.get().getSpecificities();
}

Bool Modification::isVerified() const {
	return modification_.get().isVerified();
}

Bool Modification::isApplicable(const aminoAcids::AminoAcid& prev,
		const aminoAcids::AminoAcid& current,
		const aminoAcids::AminoAcid& next) const {
	// TODO maybe it is easier to get the specs from the modification and test directly
	// currently it is forwarded to the instance which is able to decide this
	if (customSpecificities_.empty()) {
		// custom specificities are empty, so check against raw modification
		return modification_.get().isApplicable(next, current, prev);
	} else {
		// custom specificites are not empty, so check against those
		typedef std::vector<Specificity>::const_iterator IT;
		IT end = customSpecificities_.end();
		for (IT it = customSpecificities_.begin(); it != end; ++it) {
			if (it->isApplicable(prev.getRawAminoAcid(),
					current.getRawAminoAcid(), next.getRawAminoAcid())) {
				return true;
			}
		}
		return false;
	}
}

void Modification::reinit() {
	customSpecificities_.clear();
	recalculateStoichiometry();
}

void Modification::recalculateStoichiometry() {
	// MAYBE optimize by not using recalc (apply instead)
	stoichiometry_ = modification_.get().getStoichiometry().recalculatesWithConfiguration(
			stoichiometryConfig_);
}

bool Modification::operator==(const Modification& m) const {
	return modification_ == m.modification_
			&& stoichiometryConfig_ == m.stoichiometryConfig_
			&& stoichiometry_ == m.stoichiometry_
			&& customSpecificities_ == m.customSpecificities_;
}

bool Modification::operator!=(const Modification& m) const {
	return !(operator ==(m));
}

Modification& Modification::operator=(const Modification& rhs) {
	if (this != &rhs) {
		modification_ = rhs.getModification();
		stoichiometryConfig_ = rhs.getStoichiometryConfig();
		stoichiometry_ = rhs.getStoichiometry();
		customSpecificities_ = rhs.getCustomSpecificities();
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Modification& o) {
	os << o.getModification() << "\t" << o.getStoichiometryConfig() << "\t"
			<< o.getStoichiometry() << "\t" << o.getCustomSpecificities();
	return os;
}

} // namespace modifications
} // namespace libaas
