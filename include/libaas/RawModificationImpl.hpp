/*
 * RawModificationImpl.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __X_INCLUDE_X_RAWMODIFICATIONIMPL_HPP__
#define __X_INCLUDE_X_RAWMODIFICATIONIMPL_HPP__

#include <libaas/Stoichiometry.hpp>
#include <libaas/Specificity.hpp>
#include <libaas/Types.hpp>

#include <vector>
#include <iostream>

namespace libaas {
namespace modifications {

/** Modification
 *
 */
class RawModificationImpl {

public:

	typedef String RawModificationImplKeyType;

	RawModificationImpl(const RawModificationImplKeyType& id);
	RawModificationImpl(const RawModificationImpl::RawModificationImplKeyType& id,
			const libaas::String& psiName, const libaas::String& interimName,
			const libaas::String& description, const libaas::Bool& versified);

	const RawModificationImplKeyType& getId() const;

//	void setAccession(const Size& accession);
//	const Size& getAccession() const;

	void setPSIName(const String& psiName);
	const String& getPSIName() const;

	void setInterimName(const String& interimName);
	const String& getInterimName() const;

	void setDescription(const String& description);
	const String& getDescription() const;

	void addAltDescription(const String& altDescription);
	void setAltDescriptions(const std::vector<String>& altDescriptions);
	const std::vector<String>& getAltDescriptions() const;

	void setStoichiometry(const Stoichiometry& stoichiometry);
	const Stoichiometry& getStoichiometry() const;

	void addSpecificity(const Specificity& specificity);
	void setSpecificities(const std::vector<Specificity>& specificities);
	const std::vector<Specificity>& getSpecificities() const;

	void setVerified(Bool verified);
	Bool isVerified() const;

	bool operator==(const RawModificationImpl& s) const;
	//Modification& operator=(const Modification& rhs);

private:

	RawModificationImplKeyType id_;

	// TODO check member variable. They do not match unimod.xml but the field description of unimod
//	Size accession_;
	String psiName_;
	String interimName_;
	String description_;
	std::vector<String> altDescriptions_;
	Stoichiometry stoichiometry_;
	std::vector<Specificity> specificities_;
	Bool verified_;

	// unimod also contains references and a note

};
// class RawModificationImpl

std::ostream& operator<<(std::ostream&, const RawModificationImpl&);

inline const RawModificationImpl::RawModificationImplKeyType& RawModificationImpl::getId() const {
	return id_;
}

} // namespace modifications
} // namespace libaas

#endif /* __X_INCLUDE_X_RAWMODIFICATIONIMPL_HPP__ */
