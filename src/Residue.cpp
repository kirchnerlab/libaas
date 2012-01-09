/*
 * Residue.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Residue.hpp>

#include <sstream>

namespace libaas {

Residue::Residue(
		const libaas::aminoAcids::RawAminoAcidImpl::RawAminoAcidImplKeyType& aminoAcidKey) :
		aminoacid_(aminoAcidKey), modification_() {
}

Residue::Residue(const libaas::aminoAcids::AminoAcid& aminoacid) :
		aminoacid_(aminoacid), modification_() {
}

Residue::Residue(
		const libaas::aminoAcids::RawAminoAcidImpl::RawAminoAcidImplKeyType& aminoAcidKey,
		const libaas::modifications::RawModificationImpl::RawModificationImplKeyType& modificationKey) :
		aminoacid_(aminoAcidKey), modification_(modificationKey) {
}

Residue::Residue(const libaas::aminoAcids::AminoAcid& aminoAcid,
		const libaas::modifications::Modification& mod) :
		aminoacid_(aminoAcid), modification_(mod) {
}

void Residue::changeType(
		const aminoAcids::RawAminoAcidImpl::RawAminoAcidImplKeyType& aminoAcidKey) {
	aminoacid_ = libaas::aminoAcids::AminoAcid(aminoAcidKey);
}

void Residue::changeType(const aminoAcids::AminoAcid& aminoAcid) {
	aminoacid_ = aminoAcid;
}

Bool Residue::hasModification(
		const modifications::RawModificationImpl::RawModificationImplKeyType& modificationKey) const {
	return modification_.getModificationId() == modificationKey;
}

Bool Residue::hasModification(
		const modifications::Modification& modification) const {
	return modification_ == modification;
}

Bool Residue::isModified() const {
	return modification_.getModificationId() != "";
}

void Residue::removeModification() {
	modification_ = modifications::Modification();
}
Stoichiometry Residue::getStoichiometry() const {
	Stoichiometry s = aminoacid_.getStoichiometry();
	s += modification_.getStoichiometry();
	return s;
}

String Residue::toString() const {
	std::ostringstream oss;
	oss << aminoacid_.getSymbol();
	if (isModified()) {
		oss << "(" << modification_.getModificationId() << ")";
	}
	return oss.str();
}

libaas::Bool Residue::isNTerm() const {
	return aminoacid_.isNTerm();
}

libaas::Bool Residue::isCTerm() const {
	return aminoacid_.isCTerm();
}

const libaas::aminoAcids::AminoAcid& Residue::getAminoacid() const {
	return aminoacid_;
}

void Residue::setModification(
		const libaas::modifications::Modification& modification) {
	modification_ = modification;
}

const libaas::modifications::Modification& Residue::getModification() const {
	return modification_;
}

Residue& Residue::operator=(const Residue& rhs) {
	if (this != &rhs) {
		aminoacid_ == rhs.aminoacid_;
		modification_ == rhs.modification_;
	}
	return *this;
}

bool Residue::operator==(const Residue& r) const {
	return aminoacid_ == r.aminoacid_ && modification_ == r.modification_;
}

bool Residue::operator!=(const Residue& r) const {
	return !(operator ==(r));
}

std::ostream& operator<<(std::ostream& os, const Residue& o) {
	os << o.getAminoacid() << "\t" << o.getModification();
	return os;
}

} // namespace libaas
