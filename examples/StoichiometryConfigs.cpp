/*
 * StoichiometryConfigs.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/StoichiometryConfig.hpp>

#include <iostream>

using namespace libaas;
using namespace libaas::elements;

int main() {

	// ========================================================================
	std::cout << "Retrieve default stoichiometry configuration" << std::endl;

	// in order to show how to override the default configuration, we are not
	// allowed to retrieve the default config within this application before we
	// override it.

	/*
	 StoichiometryConfig defaultStoichiometry(
	 StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG);
	 std::cout << "  Default stoichiometry configuration: "
	 << defaultStoichiometry << std::endl;
	 */

	// ========================================================================
	std::cout << "Create a custom stoichiometry configuration" << std::endl;

	StoichiometryConfigImpl::StoichiometryConfigImplKeyType custom_key =
			"My_Stoichiometry_Configuration 1";
	StoichiometryConfigImpl customConfig(custom_key);
	// add element mapping manually
	ElementImpl::ElementImplSymbolType es1 = "O";
	ElementImpl::ElementImplKeyType ek1 = 8;
	customConfig.insertElement(es1, ek1);
	// add element mapping by instance of an element
	Element C(6);
	customConfig.insertElement(C);
	// create custom element ...
	ElementImpl customElement(ElementImpl::getNextId(), "my O 18", 8);
	customElement.addIsotope(17.9992, 1.0);
	Element customElementRef(customElement);
	// ... and add by instance of an element
	customConfig.insertElement(Element(customElement.getId()));

	std::cout << "  Custom stoichiometry configuration " << customConfig
			<< std::endl;

	// ========================================================================
	std::cout << "Add a custom stoichiometry configuration" << std::endl;

	// ------------------------------------------------------------------------
	std::cout << " a) manually" << std::endl;

	StoichiometryConfig customConfigRef(customConfig);
	std::cout << "  Added custom stoichiometry configuration: "
			<< customConfigRef << std::endl;

	// ------------------------------------------------------------------------
	std::cout << " b) by convenience functions" << std::endl;
	if (addStoichiometryConfig(customConfig)) {
		std::cout << "  Custom stoichiometry configuration added correctly."
				<< std::endl;
	} else {
		std::cout << "  Custom stoichiometry configuration not added correctly."
				<< std::endl;
	}

	if (addStoichiometryConfig(custom_key, customConfig.getMapping())) {
		std::cout << "  Custom stoichiometry configuration added correctly."
				<< std::endl;
	} else {
		std::cout << "  Custom stoichiometry configuration not added correctly."
				<< std::endl;
	}

	// ========================================================================
	std::cout << "Retrieve a custom stoichiometry configuration" << std::endl;

	StoichiometryConfig retrievedCustomConfig(custom_key);
	std::cout << "  Retrieved custom stoichiometry configuration: "
			<< retrievedCustomConfig << std::endl;

	// ========================================================================
	std::cout << "Override the default stoichiometry configuration"
			<< std::endl;

	// ------------------------------------------------------------------------
	std::cout << " b) using standard mapping" << std::endl;
	StoichiometryConfigImpl defaultConfig(
			StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG);
	defaultConfig.insertElement(Element(customElement.getId()));
	StoichiometryConfig defaultConfigRef(defaultConfig);
	std::cout << "  New default stoichiometry configuration: " << defaultConfig
			<< std::endl;
	std::cout
			<< "  Current default stoichiometry configuration: "
			<< StoichiometryConfig(
					StoichiometryConfigImpl::DEFAULT_ELEMENT_CONFIG)
			<< std::endl;

	return 0;
}
