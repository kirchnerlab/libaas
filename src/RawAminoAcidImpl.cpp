/*
 * RawAminoAcidImpl.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/RawAminoAcidImpl.hpp>
#include <libaas/Element.hpp>

#include <stdexcept>
#include <algorithm>

namespace libaas {
namespace aminoAcids {

const libaas::Size nEntries_aminoAcids = 24;

const libaas::Double stoi_table[][5] = { { 5, 3, 1, 1, 0 }, /*0=A*/
                                         { 5, 3, 1, 1, 1 }, /*1=C*/
                                         { 5, 4, 1, 3, 0 }, /*2=D*/
                                         { 7, 5, 1, 3, 0 }, /*3=E*/
                                         { 9, 9, 1, 1, 0 }, /*4=F*/
                                         { 3, 2, 1, 1, 0 }, /*5=G*/
                                         { 7, 6, 3, 1, 0 }, /*6=H*/
                                         { 11, 6, 1, 1, 0 }, /*7=I*/
                                         { 12, 6, 2, 1, 0 }, /*8=K*/
                                         { 11, 6, 1, 1, 0 }, /*9=L*/
                                         { 9, 5, 1, 1, 1 }, /*10=M*/
                                         { 6, 4, 2, 2, 0 }, /*11=N*/
                                         { 7, 5, 1, 1, 0 }, /*12=P*/
                                         { 8, 5, 2, 2, 0 }, /*13=Q*/
                                         { 12, 6, 4, 1, 0 }, /*14=R*/
                                         { 5, 3, 1, 2, 0 }, /*15=S*/
                                         { 7, 4, 1, 2, 0 }, /*16=T*/
                                         { 9, 5, 1, 1, 0 }, /*17=V*/
                                         { 10, 11, 2, 1, 0 }, /*18=W*/
                                         { 9, 9, 1, 2, 0 }, /*19=Y*/
                                         { 1, 0, 0, 0, 0 }, /*20, N-terminal*/
                                         { 1, 0, 0, 1, 0 }, /*21, C-terminal*/
                                         { 1, 0, 0, 0, 0 }, /*22, Protein N-terminal*/
                                         { 1, 0, 0, 1, 0 } /*23, Protein C-terminal*/
};

const libaas::elements::ElementImpl::ElementImplKeyType stoi_elements[] =
        { 1, 6, 7, 8, 16 };

const libaas::Char stoi_chars[] = { 'A', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                                    'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S',
                                    'T', 'V', 'W', 'Y',
                                    RawAminoAcidImpl::PEPTIDE_N_TERM,
                                    RawAminoAcidImpl::PEPTIDE_C_TERM,
                                    RawAminoAcidImpl::PROTEIN_N_TERM,
                                    RawAminoAcidImpl::PROTEIN_C_TERM };

const libaas::String three_letter[] = { "Ala", "Cys", "Asp", "Glu", "Phe",
                                        "Gly", "His", "Ile", "Lys", "Leu",
                                        "Met", "Asn", "Pro", "Gln", "Arg",
                                        "Ser", "Thr", "Val", "Trp", "Tyr",
                                        "PeN", "PeC", "PrN", "PrC" };

const libaas::String fullNames[] = { "Alanine", "Cysteine", "Aspartic acid",
                                     "Glutamic acid", "Phenylalanine",
                                     "Glycine", "Histidine", "Isoleucine",
                                     "Lysine", "Leucine", "Methionine",
                                     "Asparagine", "Proline", "Glutamine",
                                     "Arginine", "Serine", "Threonine",
                                     "Valine", "Tryptophan", "Tyrosine",
                                     "Peptide N-term", "Peptide C-term",
                                     "Protein N-term", "Protein C-term" };

const Char RawAminoAcidImpl::PEPTIDE_N_TERM = '0';
const Char RawAminoAcidImpl::PEPTIDE_C_TERM = '1';
const Char RawAminoAcidImpl::PROTEIN_N_TERM = '2';
const Char RawAminoAcidImpl::PROTEIN_C_TERM = '3';

Size findIdOfAminoAcidKey(const RawAminoAcidImpl::RawAminoAcidImplKeyType& key)
{
    for (Size i = 0; i < nEntries_aminoAcids; ++i) {
        if (stoi_chars[i] == key) {
            return i;
        }
    }
    throw std::out_of_range(
        "RawAminoAcidImpl::findIdOfAminoAcidKey(): Cannot find given key in standard list of amino acids.");
}

Size findIdOfAminoAcidThreeLetter(const libaas::String& tlc)
{
    for (Size i = 0; i < nEntries_aminoAcids; ++i) {
        if (three_letter[i] == tlc) {
            return i;
        }
    }
    // Cannot find three letter code. search case insensitive.
    String rhs = tlc;
    std::transform(rhs.begin(), rhs.end(), rhs.begin(), ::tolower);
    for (Size i = 0; i < nEntries_aminoAcids; ++i) {
        String lhs = three_letter[i];
        std::transform(lhs.begin(), lhs.end(), lhs.begin(), ::tolower);
        if (rhs == lhs) {
            return i;
        }
    }
    throw std::out_of_range(
        "RawAminoAcidImpl::findIdOfAminoAcidThreeLetter(): Cannot find given three letter code in standard list of amino acids.");
}

Size findIdOfAminoAcid(const libaas::String& name)
{
    for (Size i = 0; i < nEntries_aminoAcids; ++i) {
        if (fullNames[i] == name) {
            return i;
        }
    }
    // Cannot find full name. search case insensitive.
    String rhs = name;
    std::transform(rhs.begin(), rhs.end(), rhs.begin(), ::tolower);
    for (Size i = 0; i < nEntries_aminoAcids; ++i) {
        String lhs = fullNames[i];
        std::transform(lhs.begin(), lhs.end(), lhs.begin(), ::tolower);
        if (rhs == lhs) {
            return i;
        }
    }
    throw std::out_of_range(
        "RawAminoAcidImpl::findIdOfAminoAcid(): Cannot find given name in standard list of amino acids.");
}

RawAminoAcidImpl::RawAminoAcidImplKeyType RawAminoAcidImpl::getKeyForAminoAcidString(
    const libaas::String& aminoAcid)
{
    String aminoAcid_tmp = aminoAcid;
    std::transform(aminoAcid_tmp.begin(), aminoAcid_tmp.end(),
        aminoAcid_tmp.begin(), ::tolower);
    if (aminoAcid.length() == 1) {
        String aminoAcid_tmp = aminoAcid;
        std::transform(aminoAcid_tmp.begin(), aminoAcid_tmp.end(),
            aminoAcid_tmp.begin(), ::toupper);
        findIdOfAminoAcidKey(aminoAcid_tmp[0]);
        return aminoAcid_tmp[0];
    } else
        if (aminoAcid_tmp == "n-term") {
            return RawAminoAcidImpl::PROTEIN_N_TERM;
        } else
            if (aminoAcid_tmp == "c-term") {
                return RawAminoAcidImpl::PROTEIN_C_TERM;
            } else
                if (aminoAcid_tmp == "protein n-term") {
                    return RawAminoAcidImpl::PROTEIN_N_TERM;
                } else
                    if (aminoAcid_tmp == "protein c-term") {
                        return RawAminoAcidImpl::PROTEIN_C_TERM;
                    } else
                        if (aminoAcid_tmp == "peptide n-term") {
                            return RawAminoAcidImpl::PEPTIDE_N_TERM;
                        } else
                            if (aminoAcid_tmp == "pepetide c-term") {
                                return RawAminoAcidImpl::PEPTIDE_C_TERM;
                            } else
                                if (aminoAcid.size() == 3) {
                                    return stoi_chars[findIdOfAminoAcidThreeLetter(
                                        aminoAcid)];
                                } else {
                                    return stoi_chars[findIdOfAminoAcid(
                                        aminoAcid)];
                                }
    throw std::out_of_range(
        "RawAminoAcidImpl::getKeyForAminoAcidString(): Cannot find amino acid.");
}

RawAminoAcidImpl::RawAminoAcidImpl(
    const RawAminoAcidImpl::RawAminoAcidImplKeyType& id) :
        id_(id), symbol_(id), threeLetterCode_(""), fullName_(""), stoichiometry_()
{
    if (id != '\0') {
        Size k = findIdOfAminoAcidKey(id);
        id_ = id;
        symbol_ = stoi_chars[k];
        threeLetterCode_ = three_letter[k];
        fullName_ = fullNames[k];
        for (Size i = 0; i < 5; ++i) {
            stoichiometry_.set(libaas::elements::Element(stoi_elements[i]),
                stoi_table[k][i]);
        }
    }
}

RawAminoAcidImpl::RawAminoAcidImpl(const RawAminoAcidImplKeyType& id,
    const char symbol, const libaas::Stoichiometry& stoichiometry) :
        id_(id), symbol_(symbol), threeLetterCode_(""), fullName_(""), stoichiometry_(
            stoichiometry)
{
}

void RawAminoAcidImpl::setSymbol(const Char& symbol)
{
    symbol_ = symbol;
}

Char RawAminoAcidImpl::getSymbol() const
{
    return symbol_;
}

void RawAminoAcidImpl::setStoichiometry(const Stoichiometry& stoichiometry)
{
    stoichiometry_ = stoichiometry;
}

const libaas::Stoichiometry& RawAminoAcidImpl::getStoichiometry() const
{
    return stoichiometry_;
}

void RawAminoAcidImpl::setThreeLetterCode(const String& threeLetterCode)
{
    threeLetterCode_ = threeLetterCode;
}

const String& RawAminoAcidImpl::getThreeLetterCode() const
{
    return threeLetterCode_;
}

void RawAminoAcidImpl::setFullName(const String& fullName)
{
    fullName_ = fullName;
}

const String& RawAminoAcidImpl::getFullName() const
{
    return fullName_;
}

Bool RawAminoAcidImpl::isNTerm() const
{
    return symbol_ == PROTEIN_N_TERM || symbol_ == PEPTIDE_N_TERM;
}

Bool RawAminoAcidImpl::isCTerm() const
{
    return symbol_ == PROTEIN_C_TERM || symbol_ == PEPTIDE_C_TERM;
}

RawAminoAcidImpl& RawAminoAcidImpl::operator=(const RawAminoAcidImpl& a)
{
    if (this != &a) {
        id_ = a.id_;
        symbol_ = a.symbol_;
        stoichiometry_ = a.stoichiometry_;
    }
    return *this;
}

bool RawAminoAcidImpl::operator==(const RawAminoAcidImpl& a) const
{
    return id_ == a.id_ && symbol_ == a.symbol_
            && threeLetterCode_ == a.threeLetterCode_
            && fullName_ == a.fullName_ && stoichiometry_ == a.stoichiometry_;
}

bool RawAminoAcidImpl::operator!=(const RawAminoAcidImpl& a) const
{
    return !(operator ==(a));
}

std::ostream& operator<<(std::ostream& os, const RawAminoAcidImpl& o)
{
    os << o.getId() << ":" << o.getFullName() << " (" << o.getThreeLetterCode()
            << ", " << o.getSymbol() << ") - " << o.getStoichiometry();
    return os;
}

} // namespace aminoAcids
} // namespace libaas
