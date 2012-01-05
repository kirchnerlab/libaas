/*
 * Residue.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_LIBAAS_RESIDUE_HPP__
#define __LIBAAS_INCLUDE_LIBAAS_RESIDUE_HPP__

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
	const libaas::aminoAcids::AminoAcid& getAminoacid() const;

	libaas::Bool isNTerm() const;
	libaas::Bool isCTerm() const;

	void setModification(
			const libaas::modifications::Modification& modification);
	const libaas::modifications::Modification& getModification() const;
	bool hasModification(
			const modifications::RawModificationImpl::RawModificationImplKeyType& modification) const;
	bool hasModification(const modifications::Modification& modification) const;
	bool isModified() const;
	void removeModification();

	Stoichiometry getStoichiometry() const;

	String toString() const;

	Residue& operator=(const Residue& rhs);
	bool operator==(const Residue& r) const;
	bool operator!=(const Residue& r) const;

private:

	libaas::aminoAcids::AminoAcid aminoacid_;
	libaas::modifications::Modification modification_;

};
// class Residue

std::ostream& operator<<(std::ostream&, const Residue&);

} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_RESIDUE_HPP__ */
