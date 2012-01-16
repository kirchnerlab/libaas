/*
 * Residue.cpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2011,2012 Marc Kirchner
 *
 */

#include <libaas/Residue.hpp>

int main()
{

    // ========================================================================
    std::cout << "	Create a Residue" << std::endl;

    libaas::Residue res('A');

    // ========================================================================
    std::cout << "	Set/Change the amino acid" << std::endl;

    res.changeType('C');

    // ========================================================================
    std::cout << "	Set/Change the modification" << std::endl;

    res.setModification("Acetyl");

    // ========================================================================
    std::cout << "  Apply stoichiometry configurations" << std::endl;
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

    res.applyAminoAcidStoichiometryConfig(custom_key);
    res.applyModificationStoichiometryConfig(
        libaas::StoichiometryConfig(custom_key));

    // ========================================================================
    std::cout << "	Retrieve the stoichiometry" << std::endl;

    res.getStoichiometry();

    return 0;
}
