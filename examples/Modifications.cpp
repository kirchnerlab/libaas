/*
 * Modifications.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Modification.hpp>

#include <iostream>

using namespace libaas;
using namespace libaas::modifications;
using namespace libaas::aminoAcids;
using namespace libaas::elements;

int main() {

	// ========================================================================
	std::cout << "Use a standard modification" << std::endl;
	Modification acetyl("Acetyl");

	std::cout << "  Standard modification Acetyl: " << acetyl << std::endl;

	// ========================================================================
	std::cout << "Create a custom modification" << std::endl;

	// start creating custom raw modification
	RawModificationImpl::RawModificationImplKeyType id = "My Mod";
	libaas::String name = "My mod";
	libaas::String fullName = "My mod is special";
	libaas::Bool verified = true;
	RawModificationImpl customMod(id, name, fullName, verified);

	libaas::String altName = "My mod is super special";
	customMod.addAltName(altName);

	Stoichiometry myStoichiometry;
	myStoichiometry.set(Element(8), 1);
	myStoichiometry.set(Element(1), 1);
	customMod.setStoichiometry(myStoichiometry);

	// add custom raw modification
	addRawModification(customMod);

	Modification custom(id);

	std::cout << "  Custom modification " << id << ": " << custom << std::endl;

	// ========================================================================
	std::cout << "Add a custom specificity" << std::endl;

	Specificity spec1(AminoAcid('K'), Specificity::ANYWHERE,
			Specificity::CHEMICAL_DERIVATIVE);
	spec1.setComment("Some comment");
	acetyl.addCustomSpecificitiy(spec1);

	std::cout << " Custom specificity modification acetyl: " << acetyl
			<< std::endl;

	// ========================================================================
	std::cout << "Use a custom modification" << std::endl;

	// ========================================================================
	std::cout << "Retrieve the stoichiometry" << std::endl;

	std::cout << "  Retrieved stoichiometry of acetyl: "
			<< acetyl.getStoichiometry() << std::endl;

	// ========================================================================
	std::cout << "Set a stoichiometry configuration" << std::endl;

	// start creating a custom stoichiometry configuration
	StoichiometryConfigImpl::StoichiometryConfigImplKeyType custom_key =
			"My_Stoichiometry_Configuration 1";
	StoichiometryConfigImpl customConfig(custom_key);
	// create custom element ...
	ElementImpl customElement(ElementImpl::getNextId(), "C", 6);
	customElement.addIsotope(13.0034, 1.0);
	Element customElementRef(customElement);
	// ... and add by instance of an element
	customConfig.insertElement(Element(customElement.getId()));

	addStoichiometryConfig(customConfig);

	acetyl.setStoichiometryConfig(custom_key);
	std::cout << "  Retrieved stoichiometry with custom config of acetyl: "
			<< acetyl.getStoichiometry() << std::endl;

	return 0;
}
