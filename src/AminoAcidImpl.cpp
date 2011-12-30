/*
 * AminoAcidImpl.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/AminoAcidImpl.hpp>
#include <libaas/Element.hpp>

#include <stdexcept>

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

const libaas::elements::ElementImpl::ElementImplKeyType stoi_elements[] = { 1,
		6, 7, 8, 16 };

const libaas::Char stoi_chars[] = { 'A', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K',
		'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'Y',
		AminoAcidImpl::PEPTIDE_N_TERM, AminoAcidImpl::PEPTIDE_C_TERM,
		AminoAcidImpl::PROTEIN_N_TERM, AminoAcidImpl::PROTEIN_C_TERM };

const Char AminoAcidImpl::PEPTIDE_N_TERM = '0';
const Char AminoAcidImpl::PEPTIDE_C_TERM = '1';
const Char AminoAcidImpl::PROTEIN_N_TERM = '2';
const Char AminoAcidImpl::PROTEIN_C_TERM = '3';

Size findIdOfAminoAcidKey(const AminoAcidImpl::AminoAcidImplKeyType& key) {
	for (Size i = 0; i < nEntries_aminoAcids; ++i) {
		if (stoi_chars[i] == key) {
			return i;
		}
	}
	throw std::out_of_range(
			"AminoAcidImpl::findIdOfAminoAcidKey(): Cannot find given key in standard list of amino acids.");
}

AminoAcidImpl::AminoAcidImplKeyType AminoAcidImpl::getKeyForAminoAcidString(const libaas::String& aminoAcid) {
	// TODO use aminoAcid.toLower()
	if (aminoAcid.length() == 1) {
		try {
			findIdOfAminoAcidKey(aminoAcid[0]);
			return aminoAcid[0];
		} catch (std::out_of_range& e) {
			throw std::out_of_range("AminoAcidImpl::getKeyForString(): Given string does not contain a valid amino acid (one-letter code).");
		}
	} else if (aminoAcid == "N-term") {
		return AminoAcidImpl::PROTEIN_N_TERM;
	} else if (aminoAcid == "C-term") {
		return AminoAcidImpl::PROTEIN_C_TERM;
	} else {
	    // TODO implement getKeyForAminoAcidString correctly
		throw std::out_of_range("AminoAcidImpl::getKeyForAminoAcidString(): Not implemented yet.");
	}
	throw std::out_of_range("AminoAcidImpl::getKeyForAminoAcidString(): Cannot find amino acid.");
}

/** Constructor
 *
 */
AminoAcidImpl::AminoAcidImpl(const AminoAcidImpl::AminoAcidImplKeyType& id) {
	// TODO In some cases, id is \0 this is a quick fix
	if (id != '\0') {
		Size k = findIdOfAminoAcidKey(id);
		id_ = id;
		symbol_ = stoi_chars[k];
		for (Size i = 0; i < 5; ++i) {
			stoichiometry_.set(libaas::elements::Element(stoi_elements[i]),
					stoi_table[k][i]);
		}
	}
}

AminoAcidImpl::AminoAcidImpl(const AminoAcidImplKeyType& id, const char symbol,
		const libaas::Stoichiometry& stoichiometry) :
		id_(id), symbol_(symbol), stoichiometry_(stoichiometry) {
}

Char AminoAcidImpl::getSymbol() const {
	return symbol_;
}

const libaas::Stoichiometry& AminoAcidImpl::getStoichiometry() const {
	return stoichiometry_;
}

Bool AminoAcidImpl::isNTerm() const {
	return symbol_ == PROTEIN_N_TERM || symbol_ == PEPTIDE_N_TERM;
}

Bool AminoAcidImpl::isCTerm() const {
	return symbol_ == PROTEIN_C_TERM || symbol_ == PEPTIDE_C_TERM;
}

AminoAcidImpl& AminoAcidImpl::operator=(const AminoAcidImpl& a) {
	if (this != &a) {
		id_ = a.id_;
		symbol_ = a.symbol_;
		stoichiometry_ = a.stoichiometry_;
	}
	return *this;
}

bool AminoAcidImpl::operator==(const AminoAcidImpl& b) const {
	return id_ == b.id_ && symbol_ == b.symbol_
			&& stoichiometry_ == b.stoichiometry_;
}

bool AminoAcidImpl::operator!=(const AminoAcidImpl& b) const {
	return !(operator ==(b));
}

std::ostream& operator<<(std::ostream& os, const AminoAcidImpl& o) {
	os << o.getId() << ":" << o.getSymbol() << " - " << o.getStoichiometry();
	return os;
}

}// namespace aminoAcids
} // namespace libaas
