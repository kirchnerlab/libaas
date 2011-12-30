/*
 * RawModificationImpl.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_LIBAAS_RAWMODIFICATIONIMPL_HPP__
#define __LIBAAS_INCLUDE_LIBAAS_RAWMODIFICATIONIMPL_HPP__

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
			const libaas::String& name, const libaas::String& fullName,
			const libaas::Bool& verified);

	const RawModificationImplKeyType& getId() const;

	void setName(const String& name);
	const String& getName() const;

	void setFullName(const String& fullName);
	const String& getFullName() const;

	void addAltName(const String& altName);
	void setAltNames(const std::vector<String>& altName);
	const std::vector<String>& getAltNames() const;

	void setStoichiometry(const Stoichiometry& stoichiometry);
	const Stoichiometry& getStoichiometry() const;

	void addSpecificity(const Specificity& specificity);
	void setSpecificities(const std::vector<Specificity>& specificities);
	const std::vector<Specificity>& getSpecificities() const;

	void setVerified(Bool verified);
	Bool isVerified() const;

	bool operator==(const RawModificationImpl& s) const;
	bool operator!=(const RawModificationImpl& s) const;
	RawModificationImpl& operator=(const RawModificationImpl& rhs);

private:

	RawModificationImplKeyType id_;

	String name_;
	String fullName_;
	std::vector<String> altNames_;
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

#endif /* __LIBAAS_INCLUDE_LIBAAS_RAWMODIFICATIONIMPL_HPP__ */
