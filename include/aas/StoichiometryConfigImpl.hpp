/*
 * StoichiometryConfigImpl.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_AAS_STOICHIOMETRYCONFIGIMPL_HPP__
#define __LIBAAS_INCLUDE_AAS_STOICHIOMETRYCONFIGIMPL_HPP__

#include "aas/Element.hpp"
#include "aas/Types.hpp"

#include <map>
#include <iostream>

namespace aas {
namespace stoichiometries {

/** Representation of a stoichiometry configuration.
 *
 */
class StoichiometryConfigImpl
{

public:

    /**Convenience typedef of the stoichiometry configuration's data type.
     */
    typedef std::map<elements::ElementImpl::ElementImplSymbolType,
            elements::ElementImpl::ElementImplKeyType> DataType;
    /**Convenience typedef of the stoichiometry configuration's entry type.
     */
    typedef std::pair<elements::ElementImpl::ElementImplSymbolType,
            elements::ElementImpl::ElementImplKeyType> EntryType;

    /**Convenience typedef of the stoichiometry configuration's const_iterator.
     */
    typedef DataType::const_iterator const_iterator;
    /**Convenience typedef of the stoichiometry configuration's iterator.
     */
    typedef DataType::iterator iterator;
    /**Convenience typedef of the stoichiometry configuration's value_type.
     */
    typedef DataType::value_type value_type;

    /**Convenience typedef of the stoichiometry configuration's  key type.
     */
    typedef String StoichiometryConfigImplKeyType;

    /** Default constructor.
     * Creates an empty configuration in case the id does not match
     * DEFAULT_ELEMENT_CONFIG.
     * @param[in] id Key/Id of the stoichiometry configuration
     */
    StoichiometryConfigImpl(const StoichiometryConfigImplKeyType& id);

    /**Returns the key/id of the configuration.
     * @returns id of the stoichiometry configuration
     */
    const StoichiometryConfigImplKeyType& getId() const;

    /**Return const iterator to beginning.
     * @returns Const Iterator to beginning
     */
    const_iterator begin() const;

    /**Return iterator to beginning.
     * @returns Iterator to beginning
     */
    iterator begin();

    /**Return iterator to const end.
     * @returns Const iterator to end
     */
    const_iterator end() const;

    /**Return iterator to end.
     * @returns Iterator to end
     */
    iterator end();

    /**Inserts a mapping of element.getSymbol() to element.getId().
     * @param[in] element
     */
    void insertElement(const elements::Element& element);

    /**Inserts a mapping of and element symbol to the element.
     * @param[in] symbol Element symbol
     * @param[in] key Key/Id of the element
     */
    void insertElement(
        const elements::ElementImpl::ElementImplSymbolType& symbol,
        const elements::ElementImpl::ElementImplKeyType& key);

    /**Returns the id of the element which matches the given symbol.
     * @param[in] symbol Element symbol
     * @returns Id of the element
     * @throws Throws an exception if the given symbol is not present in the
     * configuration.
     */
    const elements::ElementImpl::ElementImplKeyType& getKeyForSymbol(
        const elements::ElementImpl::ElementImplSymbolType& symbol) const;

    /**Return mapping of symbol to element ids.
     * @returns Mapping of symbol to element id.
     */
    const DataType& getMapping() const;

    /**Sets element mapping.
     * @param[in] mapping Mapping of an element symbol to an element id
     */
    void setMapping(const DataType& mapping);

    /**Clones the properties of the object and sets the id to the given id.
     * @param[in] id Key/Id of the new stoichiometry configuration
     * @returns A new stoichiometry configuration
     */
    StoichiometryConfigImpl clone(
        const StoichiometryConfigImplKeyType& id) const;

    /**Sets a copy of the argument as the new content for the stoichiometry
     * configuration object.
     * The previous content is dropped.
     * @param[in] rhs Stoichiometry configuration to copy
     * @returns *this
     */
    StoichiometryConfigImpl& operator=(const StoichiometryConfigImpl& rhs);

    /**Compares the stoichiometry configuration against another.
     * @param[in] s Stoichiometry configuration object to compare *this with
     * @returns true if both stoichiometry configurations are the same, false
     * otherwise
     */
    bool operator==(const StoichiometryConfigImpl& s) const;

    /**Compares the stoichiometry configuration against another, with opposite
     * result of StoichiometryConfigurationImpl::operator==.
     * @param[in] s Stoichiometry configuration object to compare *this with
     * @returns true if the stoichiometry configuration are different, false
     * otherwise
     */
    bool operator!=(const StoichiometryConfigImpl& s) const;

    /**The Key/Id of the default stoichiometry configuration. Using this key
     * will result in a stoichiometry configuration holding the default mapping
     * of all standard elements.
     */
    static StoichiometryConfigImplKeyType DEFAULT_ELEMENT_CONFIG;

private:

    /**Key/Id of the stoichiometry configuration
     */
    StoichiometryConfigImplKeyType id_;
    /**Mapping of ElementImpl::ElementSymbolType to ElementImpl::ElementKeyType
     */
    DataType map_;

};
// class StoichiometryConfigImpl

std::ostream& operator<<(std::ostream&, const StoichiometryConfigImpl&);

} // namespace stoichiometries
} // namespace aas

#endif /* __LIBAAS_INCLUDE_AAS_STOICHIOMETRYCONFIGIMPL_HPP__ */
