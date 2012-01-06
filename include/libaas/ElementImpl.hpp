/*
 * ElementImpl.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_LIBAAS_ELEMENTIMPL_HPP__
#define __LIBAAS_INCLUDE_LIBAAS_ELEMENTIMPL_HPP__

#include <libaas/Isotope.hpp>
#include <libaas/Types.hpp>

#include <string>
#include <vector>
#include <map>
#include <iostream>

namespace libaas {
namespace elements {

/**Representation of an element.
 *
 * This class holds all information about an element.
 */
class ElementImpl {

public:

	/**Convenience typedef of the symbol type of an element.
	 */
	typedef String ElementImplSymbolType;
	/**Convenience typedef of the key type of an element.
	 */
	typedef Size ElementImplKeyType;

	/**Default constructor to create a standard element.
	 *
	 * This constructor has access to static variables containing all
	 * information necessary to create and fill the internal variables.
	 *
	 * @param[in] id Key/Id of the element
	 * @throws Throws an exceptions of the given id is not recognized in the
	 * list of standard elements.
	 */
	ElementImpl(const ElementImplKeyType& id);

	/**Constructor to create a custom element.
	 * @param[in] id Key/Id of the element
	 * @param[in] symbol Symbol of the element
	 * @param[in] atomicNumber Atomic number of the element
	 */
	ElementImpl(const ElementImplKeyType& id, const String& symbol,
			const Size& atomicNumber);

	/**Constructor to create a custom element.
	 * @param[in] id Key/Id of the element
	 * @param[in] symbol Symbol of the element
	 * @param[in] atomicNumber Atomic number of the element
	 * @param[in] isotopes List of isotopes
	 */
	ElementImpl(const ElementImplKeyType& id, const String& symbol,
			const Size& atomicNumber, const std::vector<Isotope>& isotopes);

	/**Returns the key/id of the element.
	 * @returns Key/Id of the element.
	 */
	const ElementImplKeyType& getId() const;

	/**Returns the element symbol.
	 * @returns Symbol of the element.
	 */
	const String& getSymbol() const;

	/**Returns the atomic number of the element.
	 * @return Atomic number of the element
	 */
	const Size& getAtomicNumber() const;

	/**Returns the list of isotopes of the element.
	 * @returns List of isotopes of the element.
	 */
	const std::vector<Isotope>& getIsotopes() const;

	/**Adds an isotope to the element.
	 * @param[in] isotope Isotope
	 */
	void addIsotope(const Isotope& isotope);

	/**Adds an isotope to the element.
	 * @param[in] mass Mass
	 * @param[in] frequency Frequency of the
	 */
	void addIsotope(const Double& mass, const Double& frequency);

	/**Clears the list of isotopes.
	 */
	void clearIsotopes();

	/**Sets the list of isotopes of the element.
	 * @param[in] isotopes List of isotopes
	 */
	void setIsotopes(const std::vector<Isotope>& isotopes);

	/**Sets a copy of the argument as the new content for the element object.
	 * The previous content is dropped.
	 * @param[in] rhs Element to copy
	 * @returns *this
	 */
	ElementImpl& operator=(const ElementImpl& rhs);

	/**Compares the element against another.
	 * @param[in] e Element object to compare *this with
	 * @returns true if both elements are the same, false otherwise
	 */
	bool operator==(const ElementImpl& e) const;

	/**Compares the element against another, with opposite result of
	 * ElementImpl::operator==.
	 * @param[in] e Element object to compare *this with
	 * @returns true if the elements are different, false otherwise.
	 */
	bool operator!=(const ElementImpl& e) const;

	/**Returns the number of standard elements.
	 * @returns The number of standard elements.
	 */
	static libaas::Size getNumberOfStandardElements();

	/**Returns a free key/id which is available to use for a custom element.
	 * @returns Free key/id
	 */
	static ElementImplKeyType getNextId();

	/**Returns the default mapping of an element symbol to an element key.
	 * This mapping is used to create the default stoichiometry configuration.
	 * @returns Default mapping of an element symbol to the element key.
	 */
	static std::map<ElementImplSymbolType, ElementImplKeyType>
	getDefaultMapping();

private:

	/** Key/Id of the element.
	 */
	ElementImplKeyType id_;
	/** Symbol of the element.
	 */
	String symbol_;
	/** Atomic number of the element.
	 */
	Size atomicNumber_;
	/** Isotopes possible for this element.
	 */
	std::vector<Isotope> isotopes_;

	/**Indicates a possible free Id.
	 */
	static ElementImplKeyType freeId;

};
// class ElementImpl

std::ostream& operator<<(std::ostream&, const ElementImpl&);

inline const ElementImpl::ElementImplKeyType& ElementImpl::getId() const {
	return id_;
}

} // namespace elements
} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_ELEMENTIMPL_HPP__ */
