/*
 * Specificity.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Specificity.hpp>

#include <stdexcept>

namespace libaas {
namespace modifications {

Specificity::Specificity(const libaas::aminoAcids::AminoAcid& site,
		const Position position, const Classification classification) :
		site_(site), position_(position), classification_(classification) {
}

Specificity::Specificity(const libaas::String& site,
		const libaas::String& position, const libaas::String& classification) {
	site_ = libaas::aminoAcids::AminoAcid(
			libaas::aminoAcids::AminoAcidImpl::getKeyForAminoAcidString(site));
	position_ = Specificity::parsePositionString(position);
	classification_ = Specificity::parseClassificationString(classification);
}

void Specificity::setSite(const libaas::aminoAcids::AminoAcid& aminoAcid) {
	site_ = aminoAcid;
}

const libaas::aminoAcids::AminoAcid& Specificity::getSite() const {
	return site_;
}

void Specificity::setClassification(const Classification& classification) {
	classification_ = classification;
}

const Specificity::Classification& Specificity::getClassification() const {
	return classification_;
}

void Specificity::setPosition(const Position& position) {
	position_ = position;
}
const Specificity::Position& Specificity::getPosition() const {
	return position_;
}

void Specificity::addNeutralLoss(const Stoichiometry& stoichiometry) {
	neutralLosses_.push_back(stoichiometry);
}

void Specificity::setNeutralLosses(
		const std::vector<Stoichiometry>& stoichiometries) {
	neutralLosses_ = stoichiometries;
}

const std::vector<Stoichiometry>& Specificity::getNeutralLosses() const {
	return neutralLosses_;
}

void Specificity::clearNeutralLosses() {
	neutralLosses_.clear();
}

void Specificity::addPepNeutralLoss(const Stoichiometry& stoichiometry) {
	pepNeutralLosses_.push_back(stoichiometry);
}

void Specificity::setPepNeutralLosses(
		const std::vector<Stoichiometry>& stoichiometries) {
	pepNeutralLosses_ = stoichiometries;
}

const std::vector<Stoichiometry>& Specificity::getPepNeutralLosses() const {
	return pepNeutralLosses_;
}

void Specificity::clearPepNeutralLosses() {
	pepNeutralLosses_.clear();
}

void Specificity::setComment(const String& comment) {
	comment_ = comment;
}

const String& Specificity::getComment() const {
	return comment_;
}

bool Specificity::operator==(const Specificity& s) const {
	return site_ == s.site_ && classification_ == s.classification_
			&& position_ == s.position_ && neutralLosses_ == s.neutralLosses_
			&& pepNeutralLosses_ == pepNeutralLosses_ && comment_ == s.comment_;
}

Specificity::Classification Specificity::parseClassificationString(
		const libaas::String& classification) {
	if (classification == "-") {
		return Specificity::NONE;
	} else if (classification == "Post-translational") {
		return Specificity::POST_TRANSLATIONAL;
	} else if (classification == "Co-translational") {
		return Specificity::CO_TRANSLATIONAL;
	} else if (classification == "Pre-translational") {
		return Specificity::PRE_TRANSLATIONAL;
	} else if (classification == "Chemical derivative") {
		return Specificity::CHEMICAL_DERIVATIVE;
	} else if (classification == "Artefact") {
		return Specificity::ARTEFACT;
	} else if (classification == "N-linked glycosylation") {
		return Specificity::N_LINKED_GLYCOSYLATION;
	} else if (classification == "O-linked glycosylation") {
		return Specificity::O_LINKED_GLYCOSYLATION;
	} else if (classification == "Other glycosylation") {
		return Specificity::OTHER_GLYCOSYLATION;
	} else if (classification == "Synth. pep. protect. gp.") {
		return Specificity::SYNTH_PEP_PROTECT_GP;
	} else if (classification == "Isotopic label") {
		return Specificity::ISOTOPIC_LABEL;
	} else if (classification == "Non-standard residue") {
		return Specificity::NON_STANDARD_RESIDUE;
	} else if (classification == "Multiple") {
		return Specificity::MULTIPLE;
	} else if (classification == "Other") {
		return Specificity::OTHER;
	} else if (classification == "AA substitution") {
		return Specificity::AA_SUBSTITUTION;
	}
	throw std::out_of_range("Specificity::parseClassificationString(): ");
}

Specificity::Position Specificity::parsePositionString(
		const libaas::String& position) {
	if (position == "Any N-term") {
		return Specificity::PEPTIDE_N_TERM;
	} else if (position == "Any C-term") {
		return Specificity::PEPTIDE_C_TERM;
	} else if (position == "Protein N-term") {
		return Specificity::PROTEIN_N_TERM;
	} else if (position == "Protein C-term") {
		return Specificity::PROTEIN_C_TERM;
	} else if (position == "Anywhere") {
		return Specificity::ANYWHERE;
	}
	throw std::out_of_range("Specificity::parsePositionString(): ");
}

std::ostream& operator<<(std::ostream& os, const Specificity& s) {
	os << s.getSite() << "\t" << s.getClassification() << "\t"
			<< s.getPosition() << "\t" << s.getPosition() << "\t"
			<< s.getNeutralLosses() << "\t" << s.getPepNeutralLosses() << "\t"
			<< s.getComment();
	return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Specificity>& s) {
	typedef std::vector<Specificity>::const_iterator IT;
	for (IT it = s.begin(); it != s.end(); ++it) {
		os << *it << "|";
	}
	return os;
}

} // namespace modifications
} // namespace libaas
