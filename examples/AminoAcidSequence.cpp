/*
 * AminoAcidSequence.cpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2011,2012 Marc Kirchner
 *
 */

#include <libaas/AminoAcidSequence.hpp>

int main()
{

    // ========================================================================
    std::cout << "	Create an amino acid sequence" << std::endl;

    libaas::AminoAcidSequence aas("DCGTQS");

    // ========================================================================
    std::cout << "	Add a standard modification" << std::endl;

    libaas::modifications::Modification mod1("Acetyl");
    aas.applyModificationAtPosition(mod1, 2);

    libaas::modifications::Modification mod2("Oxidation");
    libaas::AminoAcidSequence::ModificationList ml;
    ml.push_back(mod2);
    aas.applyFixedModifications(ml);

    // ========================================================================
    std::cout << "	Add a custom modification" << std::endl;

    // start creating custom raw modification
    libaas::modifications::RawModificationImpl::RawModificationImplKeyType id =
            "My Mod";
    libaas::String name = "My mod";
    libaas::String fullName = "My mod is special";
    libaas::Bool verified = true;
    libaas::modifications::RawModificationImpl customMod(id, name, fullName,
        verified);

    libaas::String altName = "My mod is super special";
    customMod.addAltName(altName);

    libaas::Stoichiometry myStoichiometry;
    myStoichiometry.set(libaas::elements::Element(8), 1);
    myStoichiometry.set(libaas::elements::Element(1), 1);
    customMod.setStoichiometry(myStoichiometry);

    customMod.addSpecificity(
        libaas::modifications::Specificity(
            libaas::aminoAcids::RawAminoAcid('D'),
            libaas::modifications::Specificity::ANYWHERE,
            libaas::modifications::Specificity::ARTEFACT));

    // add custom raw modification
    addRawModification(customMod);

    aas.applyModificationAtPosition(id, 1);

    // ========================================================================
    std::cout << "	Remove a modifications" << std::endl;

    // ========================================================================
    std::cout << "    a remove mod by key" << std::endl;

    aas.remove("Oxidation");

    // ========================================================================
    std::cout << "    b remove mod by ref" << std::endl;

    aas.remove(mod1);

    // ========================================================================
    std::cout << "  Apply stoichiometry config" << std::endl;
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

    aas.applyAminoAcidStoichiometryConfig(custom_key);

    aas.applyModificationStoichiometryConfig(custom_key);

    // ========================================================================
    std::cout << "	Retrieve the stoichiometry" << std::endl;

    aas.getStoichiometry();

    return 0;
}
