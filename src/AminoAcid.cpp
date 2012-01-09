/*
 * AminoAcid.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/AminoAcid.hpp>

#include <stdexcept>

namespace libaas {
namespace aminoAcids {

AminoAcid::AminoAcid(
		const RawAminoAcidImpl::RawAminoAcidImplKeyType& aminoAcidKey,
		const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid) :
		rawAminoAcid_(aminoAcidKey), stoichiometryConfig_(configid), stoichiometry_(
				rawAminoAcid_.get().getStoichiometry()) {
}

AminoAcid::AminoAcid(const RawAminoAcid& aminoAcid,
		const StoichiometryConfig& config) :
		rawAminoAcid_(aminoAcid), stoichiometryConfig_(config), stoichiometry_(
				rawAminoAcid_.get().getStoichiometry()) {
}

Char AminoAcid::getSymbol() const {
	return rawAminoAcid_.get().getSymbol();
}

const RawAminoAcidImpl::RawAminoAcidImplKeyType& AminoAcid::getRawAminoAcidKey() const {
	return rawAminoAcid_.get_key();
}

const RawAminoAcid& AminoAcid::getRawAminoAcid() const {
	return rawAminoAcid_;
}

const String& AminoAcid::getThreeLetterCode() const {
	return rawAminoAcid_.get().getThreeLetterCode();
}

const String& AminoAcid::getFullName() const {
	return rawAminoAcid_.get().getFullName();
}

libaas::Bool AminoAcid::isNTerm() const {
	return rawAminoAcid_.get().isNTerm();
}

libaas::Bool AminoAcid::isCTerm() const {
	return rawAminoAcid_.get().isCTerm();
}

Stoichiometry AminoAcid::getStoichiometry() const {
	return stoichiometry_;
}

void AminoAcid::setStoichiometryConfig(const StoichiometryConfig& config) {
	stoichiometryConfig_ = config;
	recalculateStoichiometry();
}

void AminoAcid::setStoichiometryConfig(
		const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid) {
	stoichiometryConfig_ = StoichiometryConfig(configid);
	recalculateStoichiometry();
}

const StoichiometryConfig& AminoAcid::getStoichiometryConfig() const {
	return stoichiometryConfig_;
}

void AminoAcid::recalculateStoichiometry() {
	stoichiometry_ = rawAminoAcid_.get().getStoichiometry().applyConfiguration(
			stoichiometryConfig_);
}

AminoAcid& AminoAcid::operator=(const AminoAcid& a) {
	if (this != &a) {
		rawAminoAcid_ = a.rawAminoAcid_;
		stoichiometryConfig_ = a.stoichiometryConfig_;
		stoichiometry_ = a.stoichiometry_;
	}
	return *this;
}

bool AminoAcid::operator==(const AminoAcid& a) const {
	return rawAminoAcid_ == a.rawAminoAcid_
			&& stoichiometryConfig_ == a.stoichiometryConfig_
			&& stoichiometry_ == a.stoichiometry_;
}

bool AminoAcid::operator!=(const AminoAcid& a) const {
	return !(operator ==(a));
}

std::ostream& operator<<(std::ostream& os, const AminoAcid& a) {
	os << a.getRawAminoAcid();
	os << a.getStoichiometry();
	return os;
}

} // namespace aminoAcids
} // namespace libaas
