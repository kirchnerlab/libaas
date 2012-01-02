/*
 * Elements.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Element.hpp>

#include <iostream>

using namespace libaas::elements;

int main() {

	// ========================================================================
	std::cout << "Retrieve a standard element" << std::endl;

	ElementImpl::ElementImplKeyType c_key = 6;
	Element C(c_key);
	std::cout << "  Standard element C: " << C << std::endl;

	// ========================================================================
	std::cout << "Create a custom element" << std::endl;

	ElementImpl::ElementImplKeyType custom_key = ElementImpl::getNextId();
	libaas::String symbol = "C";
	libaas::Size atomicNumber = 6;
	ElementImpl customElement(custom_key, symbol, atomicNumber);
	customElement.addIsotope(13.0034, 1.0);
	std::cout << "  Custom element " << symbol << ": " << customElement
			<< std::endl;

	// ========================================================================
	std::cout << "Add a custom element" << std::endl;

	// ------------------------------------------------------------------------
	std::cout << " a) manually" << std::endl;

	Element customElementRef(customElement);
	std::cout << "  Added custom element " << symbol << ": " << customElementRef
			<< std::endl;

	// ------------------------------------------------------------------------
	std::cout << " b) by convenience functions" << std::endl;

	if (addElement(customElement)) {
		std::cout << "  Custom element added correctly" << std::endl;
	} else {
		std::cout << "  Custom element not added correctly" << std::endl;
	}

	if (addElement(customElement.getId(), customElement.getSymbol(), customElement.getAtomicNumber(), customElement.getIsotopes())) {
		std::cout << "  Custom element added correctly" << std::endl;
	} else {
		std::cout << "  Custom element not added correctly" << std::endl;
	}

	// ========================================================================
	std::cout << "Retrieve a custom element" << std::endl;

	Element retrievedCustomElementRef(custom_key);
	std::cout << "  Retrieved custom element " << symbol << ": "
			<< retrievedCustomElementRef << std::endl;

	// ========================================================================
	std::cout << "Override a standard element" << std::endl;

	// ------------------------------------------------------------------------
	std::cout << " a) from scratch" << std::endl;

	ElementImpl::ElementImplKeyType N_key = 7;
	libaas::String new_N_symbol = "C";
	libaas::Size new_N_atomicNumber = 6;
	ElementImpl new_N(N_key, new_N_symbol, new_N_atomicNumber);
	new_N.addIsotope(14.0031, 0.5);
	new_N.addIsotope(15.0001, 0.5);
	Element new_N_ref(new_N);
	std::cout << "  Overridden standard element N: " << Element(N_key)
			<< std::endl;
	std::cout << "  Non-overridden standard element N: " << ElementImpl(N_key)
			<< std::endl;

	// ------------------------------------------------------------------------
	std::cout << " b) using the standard element" << std::endl;

	ElementImpl O(8);
	O.clearIsotopes();
	O.addIsotope(15.9994, 1.0);
	Element overriddenStandardElement(O);
	std::cout << "  Overridden standard element O: "
			<< overriddenStandardElement << std::endl;
	std::cout << "  Non-overridden standard element O: " << ElementImpl(8)
			<< std::endl;
	// but the default O is no longer available as flyweight

	return 0;
}
