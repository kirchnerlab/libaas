/*
 * AminoAcid.cpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2011,2012 Marc Kirchner
 *
 */

#include <libaas/AminoAcid.hpp>

int main() {

	// ========================================================================
	std::cout << "Create an amino acid" << std::endl;

	libaas::aminoAcids::AminoAcid aa('C');

	// ========================================================================
	std::cout << "Set a stoichiometry configuration" << std::endl;

// start creating a custom stoichiometry configuration
	libaas::StoichiometryConfigImpl::StoichiometryConfigImplKeyType custom_key =
			"My_Stoichiometry_Configuration 1";
	libaas::StoichiometryConfigImpl customConfig(custom_key);
	// create custom element ...
	libaas::elements::ElementImpl customElement(
			libaas::elements::ElementImpl::getNextId(), "C", 6);
	customElement.addIsotope(13.0034, 1.0);
	libaas::elements::Element customElementRef(customElement);
	// ... and add by instance of an element
	customConfig.insertElement(
			libaas::elements::Element(customElement.getId()));
	addStoichiometryConfig(customConfig);

	aa.setStoichiometryConfig(custom_key);

	// ========================================================================
	std::cout << "Retrieve the stoichiometry" << std::endl;

	aa.getStoichiometry();

	return 0;
}

