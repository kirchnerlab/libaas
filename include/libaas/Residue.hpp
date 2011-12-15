/*
 * Residue.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __X_INCLUDE_X_RESIDUE_HPP__
#define __X_INCLUDE_X_RESIDUE_HPP__

#include <libaas/AminoAcid.hpp>
#include <libaas/Modification.hpp>
#include <libaas/Types.hpp>

#include <iostream>

namespace libaas {

/** Residue
 *
 */
class Residue {

public:
	Residue(const libaas::aminoAcids::AminoAcid& aminoAcid);

	void changeType(
			const aminoAcids::AminoAcidImpl::AminoAcidImplKeyType& aminoAcidKey);
	void changeType(const aminoAcids::AminoAcid& aminoAcid);
	bool hasModification(
			const modifications::RawModificationImpl::RawModificationImplKeyType& modification) const;
	bool hasModification(const modifications::Modification& modification) const;
	bool isModified() const;

	Stoichiometry getStoichiometry() const;

	libaas::Bool isNTerm() const;
	libaas::Bool isCTerm() const;

	void setAminoacid(const libaas::aminoAcids::AminoAcid& aminoacid);
	const libaas::aminoAcids::AminoAcid& getAminoacid() const;

	void setModification(
			const libaas::modifications::Modification& modification);
	const libaas::modifications::Modification& getModification() const;
	libaas::modifications::Modification& getModification();

	Residue& operator=(const Residue& a);
	bool operator==(const Residue& b) const;
	bool operator!=(const Residue& b) const;

private:

	libaas::aminoAcids::AminoAcid aminoacid_;
	libaas::modifications::Modification modification_;

};
// class Residue

std::ostream& operator<<(std::ostream&, const Residue&);

} // namespace libaas

#endif /* __X_INCLUDE_X_RESIDUE_HPP__ */
