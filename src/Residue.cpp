/*
 * Residue.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Residue.hpp>

namespace libaas {

/** Constructor
 *
 */
Residue::Residue(const libaas::aminoAcids::AminoAcid& aminoacid) :
		aminoacid_(aminoacid) {
}

void Residue::changeType(
		const aminoAcids::AminoAcidImpl::AminoAcidImplKeyType& aminoAcidKey) {
	aminoacid_ = libaas::aminoAcids::AminoAcid(aminoAcidKey);
}

void Residue::changeType(const aminoAcids::AminoAcid& aminoAcid) {
	aminoacid_ = aminoAcid;
}

bool Residue::hasModification(
		const modifications::RawModificationImpl::RawModificationImplKeyType& modification) const {
	return modification_.getModificationId() == modification;
}

bool Residue::hasModification(
		const modifications::Modification& modification) const {
	return modification_ == modification;
}

bool Residue::isModified() const {
	// TODO implement isModified
	return false;
}

Stoichiometry Residue::getStoichiometry() const {
	Stoichiometry s = aminoacid_.get().getStoichiometry();
	s += modification_.getStoichiometry();
	return s;
}

libaas::Bool Residue::isNTerm() const {
	return aminoacid_.get().isNTerm();
}

libaas::Bool Residue::isCTerm() const {
	return aminoacid_.get().isCTerm();
}

void Residue::setAminoacid(const libaas::aminoAcids::AminoAcid& aminoacid) {
	aminoacid_ = aminoacid;
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

libaas::modifications::Modification& Residue::getModification() {
	return modification_;
}

std::ostream& operator<<(std::ostream& os, const Residue& o) {
	os << o.getAminoacid() << "\t" << o.getModification();
	return os;
}

} // namespace libaas
