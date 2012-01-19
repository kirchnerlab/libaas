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
#include <libaas/AminoAcid.hpp>

#include <vector>
#include <iostream>

namespace libaas {
namespace modifications {

/** Representation of a modification.
 *
 * This class is used as an internal data holder to allow the usage of flyweights.
 */
class RawModificationImpl
{

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
     * @returns Full name
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

    libaas::Stoichiometry::StoichiometryPtr getStoichiometryPtr() const;

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

    /**Checks whether this raw modification is applicable to the amino acid
     * current.
     * This function iterates over all specificities and calls
     * Specificity::isApplicable.
     * @param[in] prev Previous amino acid
     * @param[in] current Amino acid which should be modified with this
     * modification
     * @param[in] next Next amino acid
     * @returns true if the modification is applicable to the current amino acid,
     * false otherwise
     */
    Bool isApplicable(const aminoAcids::AminoAcid& prev,
        const aminoAcids::AminoAcid& current,
        const aminoAcids::AminoAcid& next) const;

    /**Sets a copy of the argument as the new content for the raw modification
     * object.
     * The previous content is dropped.
     * @param[in] rhs Raw modification to copy
     * @returns *this
     */
    RawModificationImpl& operator=(const RawModificationImpl& rhs);

    /**Compares the raw modification against another.
     * @param[in] m Raw moficifation object to compare *this with
     * @returns true if both raw modifications are the same, false otherwise
     */
    bool operator==(const RawModificationImpl& m) const;

    /**Compares the raw modification against another, with opposite result of
     * RawModificationImpl::operator==.
     * @param[in] m Raw modification object to compare *this with
     * @returns true if the raw modifications are different, false otherwise.
     */
    bool operator!=(const RawModificationImpl& m) const;

private:

    /** Key/Id of the raw modification.
     */
    RawModificationImplKeyType id_;
    /** Name of the raw modification.
     */
    String name_;
    /** Full name or description of the raw modification.
     */
    String fullName_;
    /** List of alternative names of the raw modification.
     */
    std::vector<String> altNames_;
    /** Stoichiometry of the raw modification
     */
    libaas::Stoichiometry::StoichiometryPtr stoichiometry_;
    /** List of specificities for the raw modification.
     */
    std::vector<Specificity> specificities_;
    /** Status of the raw modification.
     */
    Bool verified_;

    // unimod also contains references and a note
};
// class RawModificationImpl

std::ostream& operator<<(std::ostream&, const RawModificationImpl&);

inline const RawModificationImpl::RawModificationImplKeyType& RawModificationImpl::getId() const
{
    return id_;
}

} // namespace modifications
} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_RAWMODIFICATIONIMPL_HPP__ */
