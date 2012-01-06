/*
 * AminoAcidSequence.cpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2011,2012 Marc Kirchner
 * Copyright (c) 2010 Nathan Huesken
 * Copyright (c) 2009 Marc Kirchner
 * Copyright (c) 2008 Thorben Kroeger
 *
 */

#include <libaas/AminoAcidSequence.hpp>

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/tokenizer.hpp>
#include <boost/assign.hpp>

#include <sstream>
#include <exception>
#include <stdexcept>

namespace libaas {

AminoAcidSequence::AminoAcidSequence(const libaas::String& aminoAcidSequence,
		const String& modificationString) {
	if (!aminoAcidSequence.empty()) {
		// prepend peptide n-term if sequence starts without a n-term
		if (!aminoAcids::AminoAcid(aminoAcidSequence[0]).get().isNTerm()) {
			c_.push_back(aminoAcids::AminoAcidImpl::PEPTIDE_N_TERM);
		}

		typedef libaas::String::const_iterator IT;
		IT end = aminoAcidSequence.end();
		for (IT it = aminoAcidSequence.begin(); it != end; ++it) {
			c_.push_back(*it);
		}

		// append a peptide c-term if the sequence starts without a c-term
		if (!aminoAcids::AminoAcid(
				aminoAcidSequence[aminoAcidSequence.size() - 1]).get().isCTerm()) {
			c_.push_back(aminoAcids::AminoAcidImpl::PEPTIDE_C_TERM);
		}
	}
	if (!modificationString.empty()) {
		applyModificationString(modificationString);
	}
}

AminoAcidSequence::AminoAcidSequence(const_iterator first,
		const_iterator last) {
	// When the original sequence has no N and/or C term, we add peptide C and N terms as default
	if (!(*first).isNTerm()) {
		c_.push_back(aminoAcids::AminoAcidImpl::PEPTIDE_N_TERM);
	}
	for (AminoAcidSequence::const_iterator acid = first; acid != last; ++acid) {
		c_.push_back(*acid);
	}
	if (!c_[c_.size() - 1].isCTerm()) {
		c_.push_back(aminoAcids::AminoAcidImpl::PEPTIDE_C_TERM);
	}
}

void AminoAcidSequence::push_back(const Residue& value) {
	//If a C-terminal is passed, the previous C-terminal is replaced by it
	Residue last(
			aminoAcids::AminoAcid(aminoAcids::AminoAcidImpl::PEPTIDE_C_TERM));
	if (c_.size() == 0) {
		if (!value.isNTerm()) {
			c_.push_back(aminoAcids::AminoAcidImpl::PEPTIDE_N_TERM);
		}
		c_.push_back(value);
	} else {
		if (c_[c_.size() - 1].isCTerm()) {
			//copy the C-terminal, in case there are mods
			last = c_[c_.size() - 1];
			c_.pop_back();
			c_.push_back(value);
		} else {
			c_.push_back(value);
		}
	}
	if (!value.isCTerm())
		c_.push_back(last);
}

void AminoAcidSequence::pop_back() {
	if (c_.size() > 0 && (c_[c_.size() - 1].isCTerm())) {
		Residue last = c_[c_.size() - 1];
		c_.pop_back();
		c_.pop_back();
		c_.push_back(last);
	} else {
		c_.pop_back();
	}
}

void AminoAcidSequence::makePeptideCTerm() {
	if (c_.back().getAminoacid().get_key()
			== aminoAcids::AminoAcidImpl::PEPTIDE_C_TERM) {
		return;
	}
	if (!c_.back().isCTerm()) {
		// TODO shall we append a peptide c-term in this case?
		throw std::out_of_range("Unable to change amino acid sequence N-term"
				"to peptide C-term, because there is no C-term.");
	}
	c_.back().changeType(aminoAcids::AminoAcidImpl::PEPTIDE_C_TERM);
}

void AminoAcidSequence::makePeptideNTerm() {
	if (c_.front().getAminoacid().get_key()
			== aminoAcids::AminoAcidImpl::PEPTIDE_N_TERM) {
		return;
	}
	if (!c_.front().isNTerm()) {
		// TODO shall we prepend a peptide N-term in this case?
		throw std::out_of_range("Unable to change amino acid sequence N-term"
				"to peptide N-term, because there is no N-term.");
	}
	c_.front().changeType(aminoAcids::AminoAcidImpl::PEPTIDE_N_TERM);
}

void AminoAcidSequence::makeProteinCTerm() {
	if (c_.back().getAminoacid().get_key()
			== aminoAcids::AminoAcidImpl::PROTEIN_C_TERM) {
		return;
	}
	if (!c_.back().isCTerm()) {
		// TODO shall we append a protein c-term in this case?
		throw std::out_of_range("Unable to change amino acid sequence N-term"
				"to protein N-term, because there is no N-term.");
	}
	c_.back().changeType(aminoAcids::AminoAcidImpl::PROTEIN_C_TERM);
}

void AminoAcidSequence::makeProteinNTerm() {
	if (c_.front().getAminoacid().get_key()
			== aminoAcids::AminoAcidImpl::PROTEIN_N_TERM) {
		return;
	}
	if (!c_.front().isNTerm()) {
		// TODO shall we prepend a protein n-term in this case?
		throw std::out_of_range("Unable to change amino acid sequence N-term"
				"to protein N-term, because there is no N-term.");
	}
	c_.front().changeType(aminoAcids::AminoAcidImpl::PROTEIN_N_TERM);
}

void AminoAcidSequence::applyModificationString(
		const String& modificationString) {
	// TODO fix protein pilot specific things
	// TODO fix exception handling
	typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;
	boost::char_separator<char> sep(";", "", boost::keep_empty_tokens);
	Tokenizer tokens(modificationString, sep);
	std::string field;
	boost::cmatch m;
	boost::regex regularModification("(.+)\\(.+\\)\\@([0-9]+)");
	boost::regex terminalModifictaion("(.+)\\@(.+)");
	for (Tokenizer::const_iterator tok_iter2 = tokens.begin();
			tok_iter2 != tokens.end(); ++tok_iter2) {
		field = *tok_iter2;
		boost::trim_left(field);
		replace(field.begin(), field.end(), ' ', '_');
		if (boost::regex_match(field.c_str(), m, regularModification)) {
			std::string modification(m[1].first, m[1].second);
			if (boost::algorithm::starts_with(modification, "No_")) {
				// ignore ProteinPilot's concept of reporting the absence
				// of fixed modifications.
				continue;
			}
			std::string positionStr(m[2].first, m[2].second);
			size_t position;
			std::istringstream iss1(positionStr);
			iss1 >> position;
			if (position >= 0 && position < size()) {
//				try {
				// TODO we currently ignore the amino acid which is specified in the modification string
				applyModificationAtPosition(modification, position);
//				} catch (std::exception& e) {
				// trying to access non existing modification
//					std::ostringstream oss;
//					std::string emsg(e.what());
//					oss << emsg << " at position " << position << " ("
//							<< aas[position].aminoAcid() << ")";
//				}
			} else {
//				mstk_fail(
//						"ProteinPilotLoader::ProteinPilotPeptideReader::"
//								"addModifications(): requested modification position not "
//								"available.");
			}
		} else if (boost::regex_match(field.c_str(), m, terminalModifictaion)) {
			std::string modification(m[1].first, m[1].second);
			if (boost::algorithm::starts_with(modification, "No_")) {
				// ignore ProteinPilot's concept of reporting the absence
				// of fixed modifications.
				continue;
			}
			std::string term(m[2].first, m[2].second);
			try {
				if (term == "N-term") {
					applyModificationAtPosition(modification, 0);
				} else if (term == "C-term") {
					applyModificationAtPosition(modification, size() - 1);
				} else {
					std::ostringstream oss;
					oss
							<< "ProteinPilotLoader::ProteinPilotPeptideReader::readNextRow(): Unknown terminal: "
							<< term;
//					mstk_fail(oss.str());
				}
			} catch (std::exception& e) {
				// trying to access non existing modification
//				std::ostringstream oss;
//				std::string emsg(e.what());
//				oss << emsg << " at position " << term;
//				throw mstk::RuntimeError(oss.str());
			}
		} else {
			std::ostringstream oss;
			oss
					<< "ProteinPilotLoader::ProteinPilotPeptideReader::readNextRow(): Unknown modification pattern: "
					<< field;
//			mstk_fail(oss.str());
		}
	}
}

void AminoAcidSequence::remove(
		const modifications::RawModificationImpl::RawModificationImplKeyType& modKey) {
	for (AminoAcidSequence::iterator it = begin(); it != end(); ++it) {
		if (it->hasModification(modKey)) {
			it->removeModification();
		}
	}
}

void AminoAcidSequence::remove(const modifications::Modification& mod) {
	for (AminoAcidSequence::iterator it = begin(); it != end(); ++it) {
		if (it->hasModification(mod)) {
			it->removeModification();
		}
	}
}

void AminoAcidSequence::append(const AminoAcidSequence& sequence) {
	if (this != &sequence) {
		//The C-terminal is taken from the second sequence, so the
		//possible modifications of the C-terminal of the first sequence
		//get lost here
		if (c_.size() == 0) {
			// TODO what if we have a n-term mod at sequence, should we just use the sequence[0] instead of a new peptide n-term here?
			c_.push_back(aminoAcids::AminoAcidImpl::PEPTIDE_N_TERM);
		}
		if (c_[c_.size() - 1].isCTerm()) {
			c_.pop_back();
		}
		std::copy(sequence.begin() + 1, sequence.end(), std::back_inserter(c_));
	} else {
		Residue last(
				aminoAcids::AminoAcid(
						aminoAcids::AminoAcidImpl::PEPTIDE_C_TERM));
		if (c_[c_.size() - 1].isCTerm()) {
			last = c_.back();
			c_.pop_back();
		}
		std::copy(sequence.begin() + 1, sequence.end(), std::back_inserter(c_));
		c_.push_back(last);
	}
}

libaas::AminoAcidSequence::iterator AminoAcidSequence::apply(
		const modifications::Modification& mod,
		const libaas::AminoAcidSequence::iterator& begin,
		const libaas::AminoAcidSequence::iterator& end) const {
	libaas::AminoAcidSequence::iterator iter;
	aminoAcids::AminoAcid prevAcid('\0');
	aminoAcids::AminoAcid nextAcid;
	for (iter = begin; iter != end; ++iter) {
		if ((iter + 1) == (end)) {
			nextAcid = '\0';
		} else {
			nextAcid = (iter + 1)->getAminoacid();
		}
		if (mod.isApplicable(prevAcid, iter->getAminoacid(), nextAcid)) {
			iter->setModification(mod);
			return iter;
		}
		prevAcid = iter->getAminoacid();
	}
	return iter;
}

std::vector<AminoAcidSequence> AminoAcidSequence::applyVariableModifications(
		const std::vector<
				modifications::RawModificationImpl::RawModificationImplKeyType>& mods,
		unsigned int maxModificationsPerPeptide) const {
	ModificationList mmods;
	typedef std::vector<
			modifications::RawModificationImpl::RawModificationImplKeyType>::const_iterator IT;
	IT end = mods.end();
	for (IT iter = mods.begin(); iter != end; ++iter) {
		mmods.push_back(modifications::Modification(*iter));
	}
	return applyVariableModifications(mmods);
}

std::vector<AminoAcidSequence> AminoAcidSequence::applyVariableModifications(
		const std::vector<modifications::RawModification>& mods,
		unsigned int maxModificationsPerPeptide) const {
	ModificationList mmods;
	typedef std::vector<modifications::RawModification>::const_iterator IT;
	IT end = mods.end();
	for (IT iter = mods.begin(); iter != end; ++iter) {
		mmods.push_back(modifications::Modification(*iter));
	}
	return applyVariableModifications(mmods);
}

std::vector<AminoAcidSequence> AminoAcidSequence::applyVariableModifications(
		const ModificationList& mods,
		unsigned int maxModificationsPerPeptide) const {
	// FIXME: check all boundary conditions in test
	typedef std::vector<AminoAcidSequence> SequenceList;
	typedef std::vector<unsigned int> NumModificationsList;
	SequenceList peptides;
	peptides.push_back(*this); // make a copy of the unmodified peptide
	NumModificationsList numModifications;
	numModifications.push_back(0);
	Size h = 1;
	for (ModificationList::const_iterator it = mods.begin(); it != mods.end();
			++it) {
		for (unsigned int i = 0; i < h; ++i) {
			AminoAcidSequence seq = peptides[i];
			unsigned int k = numModifications[i];
			// provide the "real" begin, as the terminals can get modified, too
			iterator begin = seq.c_.begin();
			if ((maxModificationsPerPeptide == 0)
					|| (k < maxModificationsPerPeptide)) {
				while (true) {
					begin = apply((*it), begin, seq.c_.end());
					if (begin != seq.c_.end()
							&& ((maxModificationsPerPeptide == 0)
									|| (k < maxModificationsPerPeptide))) {
						++k;
						peptides.push_back(seq);
						numModifications.push_back(k);
					} else {
						break;
					}
					++begin;
				}
			}
		}
		h = peptides.size();
	}
	return peptides;

}

void AminoAcidSequence::applyFixedModifications(
		const std::vector<
				modifications::RawModificationImpl::RawModificationImplKeyType>& mods) {
	ModificationList mmods;
	typedef std::vector<
			modifications::RawModificationImpl::RawModificationImplKeyType>::const_iterator IT;
	IT end = mods.end();
	for (IT iter = mods.begin(); iter != end; ++iter) {
		mmods.push_back(modifications::Modification(*iter));
	}
	applyFixedModifications(mmods);
}

void AminoAcidSequence::applyFixedModifications(
		const std::vector<modifications::RawModification>& mods) {
	ModificationList mmods;
	typedef std::vector<modifications::RawModification>::const_iterator IT;
	IT end = mods.end();
	for (IT iter = mods.begin(); iter != end; ++iter) {
		mmods.push_back(modifications::Modification(*iter));
	}
	applyFixedModifications(mmods);
}

void AminoAcidSequence::applyFixedModifications(const ModificationList& mods) {
	typedef ModificationList::const_iterator IT;
	IT end = mods.end();
	for (IT it = mods.begin(); it != end; ++it) {
		// iterate through all modifications and apply them to the complete peptide
		Size end = size() - 1;
		const modifications::Modification& mod = *it;
		for (Size pos = 1; pos < end; ++pos) {
			try {
				applyModificationAtPosition(mod, pos);
			} catch (std::out_of_range& e) {
				// nothing to do here
			}
		}
	}
}

void AminoAcidSequence::applyModificationAtPosition(
		const modifications::Modification& mod, const Size& pos) {
	if (pos >= size()) {
		throw std::out_of_range(
				"AminoAcidSequence::applyModificationAtPosition(): Trying to apply modification at position out of bound");
	}

	// get prev amino acid
	aminoAcids::AminoAcid prev('\0');
	if (pos != 0) {
		prev = operator[](pos - 1).getAminoacid();
	}

	// get next amino acid
	aminoAcids::AminoAcid next('\0');
	if (pos != size() - 1) {
		next = operator[](pos + 1).getAminoacid();
	}

	// get pos amino acid
	Residue current = operator[](pos);
	if (current.isModified()) {
		throw std::out_of_range(
				"AminoAcidSequence::applyModificationAtPosition(): Residue is already modified. Cannot add more than one modification to one residue.");
	}
	// check if mod is applicable to this position
	if (!mod.isApplicable(prev, current.getAminoacid(), next)) {
		throw std::out_of_range(
				"AminoAcidSequence::applyModificationAtPosition(): Cannot apply mod to this position.");
	}

	operator[](pos).setModification(mod);
}

Stoichiometry AminoAcidSequence::getStoichiometry() const {
	Stoichiometry ret;
	for (const_iterator iter = begin(); iter != end(); ++iter) {
		ret += iter->getStoichiometry();
	}
	return ret;
}

String AminoAcidSequence::toUnmodifiedSequenceString() const {
	std::string s;
	for (const_iterator it = begin(); it != end(); ++it) {
		if (!it->isNTerm() && !it->isCTerm())
			s += it->getAminoacid().get().getSymbol();
	}
	return s;
}

String AminoAcidSequence::toString(const Bool showTerminals) const {
	std::string seq;
	for (const_iterator it = begin(); it != end(); ++it) {
		if (showTerminals || (!(*it).isNTerm() && !(*it).isCTerm()))
			seq += (*it).toString();
	}
	return seq;
}
String AminoAcidSequence::getModificationString() const {
	std::ostringstream modoss;
	int pos = 0;
	for (const_iterator it = begin(); it != end(); ++it, ++pos) {
		if (it->isModified()) {
			if (!modoss.str().empty()) {
				modoss << "; ";
			}
			modifications::Modification mod = it->getModification();
			modoss << mod.getModificationId() << "("
					<< it->getAminoacid().get().getSymbol() << ")@" << pos;
		}
	}
	return modoss.str();
}

std::ostream& operator<<(std::ostream& os, const AminoAcidSequence& o) {
	typedef AminoAcidSequence::const_iterator IT;
	IT end = o.end();
	for (IT it = o.begin(); it != end; ++it) {
		os << *it << "\t";
	}
	return os;
}

} // namespace libaas
