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

/** Representation of a modification.
 *
 * This class is used as an internal data holder to allow the usage of flyweights.
 */
class RawModificationImpl {

public:

	/**Convenience typedef.
	 */
	typedef String RawModificationImplKeyType;

	/**Default constructor to instantiate a standard modification.
	 * @param[in] id Key/Id of the modification
	 * @throws Throws an exception if the given id is not in the list of standard modifications.
	 */
	RawModificationImpl(const RawModificationImplKeyType& id);

	/**Constructor to create custom modifications.
	 * @param[in] id Key/Id of the modification
	 * @param[in] name Name of the modification
	 * @param[in] fullName Full name of the modification (description)
	 * @param[in] verified Verified
	 */
	RawModificationImpl(
			const RawModificationImpl::RawModificationImplKeyType& id,
			const libaas::String& name, const libaas::String& fullName,
			const libaas::Bool& verified);

	/**Retruns the id of the modification.
	 * @returns Id of the modification
	 */
	const RawModificationImplKeyType& getId() const;

	/**Sets the name of the modification.
	 * @param[in] name Name
	 */
	void setName(const String& name);

	/**Returns the name of the modification.
	 * @returns Name
	 */
	const String& getName() const;

	/**Sets the full name (description) of the modification.
	 * @param[in] fullName Full name
	 */
	void setFullName(const String& fullName);

	/**Returns the full name (description) of the modification.
	 * @retruns Full name
	 */
	const String& getFullName() const;

	/**Adds an alternative name.
	 * @param[in] altName Alternative name
	 */
	void addAltName(const String& altName);

	/**Sets alternative names.
	 * @param[in] altNames Alternative names
	 */
	void setAltNames(const std::vector<String>& altNames);

	/**Returns all alternative names.
	 * @returns List of alternative names
	 */
	const std::vector<String>& getAltNames() const;

	/**Sets the stoichiometry of the modification
	 * @param[in] stoichiometry Stoichiometry
	 */
	void setStoichiometry(const Stoichiometry& stoichiometry);

	/**Returns the stoichiometry of the modification.
	 *
	 * In case this is a standard modification, the stoichiometry is calculated
	 * by using the default stoichiometry configuration.
	 *
	 * @returns The stoichiometry of the modification
	 */
	const Stoichiometry& getStoichiometry() const;

	/**Adds a specificity to the modification.
	 * @param[in] specificity Specificity
	 */
	void addSpecificity(const Specificity& specificity);

	/**Sets specificities.
	 * @param[in] specificities List of specificities
	 */
	void setSpecificities(const std::vector<Specificity>& specificities);

	/**Returns all specificities of the modification.
	 * @returns List of specificities
	 */
	const std::vector<Specificity>& getSpecificities() const;

	/**Set the status of the modification.
	 * @param[in] verified Verfified
	 */
	void setVerified(Bool verified);

	/**Returns the status of the modification.
	 * @returns True if the modification is verified, otherwise false.
	 */
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
