/*
 * Specificity.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 * Copyright (c) 2010 Nathan Huesken
 * Copyright (c) 2010 Marc Kirchner
 *
 */

#include <libaas/Specificity.hpp>

#include <stdexcept>
#include <algorithm>

namespace libaas {
namespace modifications {

Specificity::Specificity(const libaas::aminoAcids::RawAminoAcid& site,
		const Position position, const Classification classification) :
		site_(site), position_(position), classification_(classification), neutralLosses_(), pepNeutralLosses_(), comment_(
				"") {
}

Specificity::Specificity(const libaas::String& site,
		const libaas::String& position, const libaas::String& classification) :
		neutralLosses_(), pepNeutralLosses_(), comment_("") {
	site_ = libaas::aminoAcids::RawAminoAcid(
			libaas::aminoAcids::RawAminoAcidImpl::getKeyForAminoAcidString(site));
	position_ = Specificity::parsePositionString(position);
	classification_ = Specificity::parseClassificationString(classification);
}

void Specificity::setSite(const libaas::aminoAcids::RawAminoAcid& aminoAcid) {
	site_ = aminoAcid;
}

const libaas::aminoAcids::RawAminoAcid& Specificity::getSite() const {
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

Bool Specificity::isApplicable(const libaas::aminoAcids::RawAminoAcid& prev,
		const libaas::aminoAcids::RawAminoAcid& current,
		const libaas::aminoAcids::RawAminoAcid& next) const {

	// TODO this test includes whether the current position is _excactly_ the same as the expected site (including thing such as stoichiometry and so on)
	// this has pros and cons. we have to decide which is the best alternative
	if (site_ != current) {
		// not the correct site
		return false;
	}

	switch (position_) {
	case PEPTIDE_N_TERM:
		if (!current.get().isNTerm()
				&& prev
						!= libaas::aminoAcids::RawAminoAcid(
								aminoAcids::RawAminoAcidImpl::PEPTIDE_N_TERM)) {
			return false;
		}
		break;
	case PROTEIN_N_TERM:
		if (!current.get().isNTerm()
				&& prev
						!= libaas::aminoAcids::RawAminoAcid(
								aminoAcids::RawAminoAcidImpl::PROTEIN_N_TERM)) {
			return false;
		}
		break;
	case PEPTIDE_C_TERM:
		if (!current.get().isCTerm()
				&& next
						!= libaas::aminoAcids::RawAminoAcid(
								aminoAcids::RawAminoAcidImpl::PEPTIDE_C_TERM)) {
			return false;
		}
		break;
	case PROTEIN_C_TERM:
		if (!current.get().isCTerm()
				&& next
						!= libaas::aminoAcids::RawAminoAcid(
								aminoAcids::RawAminoAcidImpl::PROTEIN_C_TERM)) {
			return false;
		}
		break;
	case ANYWHERE:
		break;
	}

	return true;
}

bool Specificity::operator==(const Specificity& s) const {
	return site_ == s.site_ && classification_ == s.classification_
			&& position_ == s.position_ && neutralLosses_ == s.neutralLosses_
			&& pepNeutralLosses_ == s.pepNeutralLosses_
			&& comment_ == s.comment_;
}

bool Specificity::operator!=(const Specificity& s) const {
	return !(operator ==(s));
}

Specificity& Specificity::operator=(const Specificity& rhs) {
	if (this != &rhs) {
		site_ = rhs.site_;
		classification_ = rhs.classification_;
		position_ = rhs.position_;
		neutralLosses_ = rhs.neutralLosses_;
		pepNeutralLosses_ = rhs.pepNeutralLosses_;
		comment_ = rhs.comment_;
	}
	return *this;
}

Specificity::Classification Specificity::parseClassificationString(
		const libaas::String& classification) {
	String classification_tmp = classification;
	std::transform(classification_tmp.begin(), classification_tmp.end(),
			classification_tmp.begin(), ::tolower);

	if (classification_tmp == "-") {
		return Specificity::NONE;
	} else if (classification_tmp == "post-translational") {
		return Specificity::POST_TRANSLATIONAL;
	} else if (classification_tmp == "co-translational") {
		return Specificity::CO_TRANSLATIONAL;
	} else if (classification_tmp == "pre-translational") {
		return Specificity::PRE_TRANSLATIONAL;
	} else if (classification_tmp == "chemical derivative") {
		return Specificity::CHEMICAL_DERIVATIVE;
	} else if (classification_tmp == "artefact") {
		return Specificity::ARTEFACT;
	} else if (classification_tmp == "n-linked glycosylation") {
		return Specificity::N_LINKED_GLYCOSYLATION;
	} else if (classification_tmp == "o-linked glycosylation") {
		return Specificity::O_LINKED_GLYCOSYLATION;
	} else if (classification_tmp == "other glycosylation") {
		return Specificity::OTHER_GLYCOSYLATION;
	} else if (classification_tmp == "synth. pep. protect. gp.") {
		return Specificity::SYNTH_PEP_PROTECT_GP;
	} else if (classification_tmp == "isotopic label") {
		return Specificity::ISOTOPIC_LABEL;
	} else if (classification_tmp == "non-standard residue") {
		return Specificity::NON_STANDARD_RESIDUE;
	} else if (classification_tmp == "multiple") {
		return Specificity::MULTIPLE;
	} else if (classification_tmp == "other") {
		return Specificity::OTHER;
	} else if (classification_tmp == "aa substitution") {
		return Specificity::AA_SUBSTITUTION;
	}
	throw std::out_of_range("Specificity::parseClassificationString(): ");
}

Specificity::Position Specificity::parsePositionString(
		const libaas::String& position) {
	String position_tmp = position;
	std::transform(position_tmp.begin(), position_tmp.end(),
			position_tmp.begin(), ::tolower);
	if (position_tmp == "any n-term") {
		return Specificity::PEPTIDE_N_TERM;
	} else if (position_tmp == "any c-term") {
		return Specificity::PEPTIDE_C_TERM;
	} else if (position_tmp == "protein n-term") {
		return Specificity::PROTEIN_N_TERM;
	} else if (position_tmp == "protein c-term") {
		return Specificity::PROTEIN_C_TERM;
	} else if (position_tmp == "anywhere") {
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
