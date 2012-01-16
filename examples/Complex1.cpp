/*
 * Complex1.cpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2011,2012 Marc Kirchner
 *
 */

#include <libaas/AminoAcidSequence.hpp>

int main()
{

    // ========================================================================
    std::cout
            << "Create an amino acid with a custom modification using a different element configuration"
            << std::endl;
    // ========================================================================
    std::cout << "  create/add custom element" << std::endl;

    libaas::elements::ElementImpl custom13C(
        libaas::elements::ElementImpl::getNextId(), "13C", 6);
    custom13C.addIsotope(libaas::elements::Isotope(12.0, 0.01));
    custom13C.addIsotope(libaas::elements::Isotope(13.0033554, 0.99));
    libaas::elements::addElement(custom13C);

    // ========================================================================
    std::cout << "  create/add stoichiometry configuration" << std::endl;
    libaas::StoichiometryConfigImpl::StoichiometryConfigImplKeyType configKey =
            "Label Config";
    libaas::StoichiometryConfigImpl customConfig(configKey);
    customConfig.insertElement(custom13C.getSymbol(), custom13C.getId());
    libaas::addStoichiometryConfig(customConfig);

    // ========================================================================
    std::cout << "  create/add custom raw modification" << std::endl;
    libaas::modifications::RawModificationImpl::RawModificationImplKeyType modKey =
            "Label:13C(7)";
    libaas::modifications::RawModificationImpl customRawMod(modKey,
        "Label:13C(7)", "13C(7) custom label", false);
    libaas::Stoichiometry customModStoichiometry;
    customModStoichiometry.set(
        libaas::elements::Element(
            libaas::elements::ElementImpl::getDefaultKeyForElementSymbol("C")),
        7);
    customModStoichiometry.set(
        libaas::elements::Element(
            libaas::elements::ElementImpl::getDefaultKeyForElementSymbol(
                "13C")), 7);
    customRawMod.setStoichiometry(customModStoichiometry);
    customRawMod.addSpecificity(
        libaas::modifications::Specificity(
            libaas::aminoAcids::RawAminoAcid('Y'),
            libaas::modifications::Specificity::ANYWHERE,
            libaas::modifications::Specificity::ISOTOPIC_LABEL));
    customRawMod.addSpecificity(
        libaas::modifications::Specificity(
            libaas::aminoAcids::RawAminoAcid('F'),
            libaas::modifications::Specificity::ANYWHERE,
            libaas::modifications::Specificity::ISOTOPIC_LABEL));
    libaas::modifications::addRawModification(customRawMod);

    // ========================================================================
    std::cout
            << "  create a modification using the custom raw modification and custom stoichiometry configuration"
            << std::endl;
    libaas::modifications::Modification customMod(modKey, configKey);

    // ========================================================================
    std::cout << "  create/add raw amino acid" << std::endl;
    libaas::aminoAcids::RawAminoAcidImpl::RawAminoAcidImplKeyType customAminoAcidKey =
            'U';
    libaas::Stoichiometry customAAStoichiometry;
    customAAStoichiometry.set(
        libaas::elements::Element(
            libaas::elements::ElementImpl::getDefaultKeyForElementSymbol("C")),
        3);
    customAAStoichiometry.set(
        libaas::elements::Element(
            libaas::elements::ElementImpl::getDefaultKeyForElementSymbol("H")),
        7);
    customAAStoichiometry.set(
        libaas::elements::Element(
            libaas::elements::ElementImpl::getDefaultKeyForElementSymbol("N")),
        1);
    customAAStoichiometry.set(
        libaas::elements::Element(
            libaas::elements::ElementImpl::getDefaultKeyForElementSymbol("O")),
        2);
    customAAStoichiometry.set(
        libaas::elements::Element(
            libaas::elements::ElementImpl::getDefaultKeyForElementSymbol(
                "Se")), 1);
    libaas::aminoAcids::RawAminoAcidImpl customAminoAcid(customAminoAcidKey,
        'U', customAAStoichiometry);
    customAminoAcid.setThreeLetterCode("Sec");
    customAminoAcid.setFullName("Selenocysteine");
    libaas::aminoAcids::addRawAminoAcid(customAminoAcid);

    // ========================================================================
    std::cout << "  create custom modification which binds to U" << std::endl;
    libaas::modifications::RawModificationImpl::RawModificationImplKeyType acetylKey =
            "Acetyl";
    libaas::modifications::RawModificationImpl rawAcetyl(acetylKey);

    libaas::modifications::Modification customAcetyl(acetylKey);
    customAcetyl.setCustomSpecificities(customAcetyl.getSpecificities());
    customAcetyl.addCustomSpecificity(
        libaas::modifications::Specificity(
            libaas::aminoAcids::RawAminoAcid(customAminoAcidKey),
            libaas::modifications::Specificity::ANYWHERE,
            libaas::modifications::Specificity::POST_TRANSLATIONAL));

    // ========================================================================
    std::cout << "  create residue and set amino acid and custom modification"
            << std::endl;
    libaas::AminoAcidSequence aas("ACQUY");
    aas.applyModificationAtPosition(customMod, 5);
    aas.applyModificationAtPosition(customAcetyl, 4);

    // ========================================================================
    std::cout << "Human readable stoichiometry: "
            << aas.getStoichiometry().toString() << std::endl;
    std::cout << "Stoichiometry including isotopic information: "
            << aas.getStoichiometry() << std::endl;
    std::cout << "Amino acid sequence including its modificaitons: "
            << aas.toString(false) << std::endl;

    return 0;
}
