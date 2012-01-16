/*
 * RawAminoAcid.cpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2011,2012 Marc Kirchner
 *
 */

#include <libaas/RawAminoAcid.hpp>

int main()
{

    // ========================================================================
    std::cout << "Retrieve a standard raw amino acid" << std::endl;
    libaas::aminoAcids::RawAminoAcid cystein('C');

    // ========================================================================
    std::cout << "Create a custom raw amino acid" << std::endl;
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

    // ========================================================================
    std::cout << "Add a custom raw amino acid" << std::endl;
    libaas::aminoAcids::addRawAminoAcid(customAminoAcid);

    // ========================================================================
    std::cout << "Override a standard raw amino acid" << std::endl;
    libaas::aminoAcids::RawAminoAcidImpl serine('S');
    serine.setFullName("Serine is a proteinogenic amino acid");
    libaas::aminoAcids::addRawAminoAcid(serine);

    // ========================================================================
    std::cout << "Retrieve the stoichiometry" << std::endl;
    serine.getStoichiometry();

    return 0;
}

