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

#include <sstream>
#include <exception>
#include <stdexcept>

namespace libaas {

AminoAcidSequence::AminoAcidSequence(const libaas::String& aminoAcidSequence,
    const StoichiometryConfig& aminoAcidConfig)
{
    // TODO do we really want an empty aas in case the string is empty?
    if (!aminoAcidSequence.empty()) {
        // prepend peptide n-term if sequence starts without a n-term
        if (!aminoAcids::AminoAcid(aminoAcidSequence[0]).isNTerm()) {
            c_.push_back(aminoAcids::RawAminoAcidImpl::PEPTIDE_N_TERM);
        }

        typedef libaas::String::const_iterator IT;
        IT end = aminoAcidSequence.end();
        Residue r;
        for (IT it = aminoAcidSequence.begin(); it != end; ++it) {
            c_.push_back(*it);
            c_.back().applyAminoAcidStoichiometryConfig(aminoAcidConfig);
        }

        // append a peptide c-term if the sequence starts without a c-term
        if (!aminoAcids::AminoAcid(
            aminoAcidSequence[aminoAcidSequence.size() - 1]).isCTerm()) {
            c_.push_back(aminoAcids::RawAminoAcidImpl::PEPTIDE_C_TERM);
        }
    }
}

AminoAcidSequence::AminoAcidSequence(const_iterator first, const_iterator last)
{
    // When the original sequence has no N and/or C term, we add peptide C and N terms as default
    if (!(*first).isNTerm()) {
        c_.push_back(aminoAcids::RawAminoAcidImpl::PEPTIDE_N_TERM);
    }
    std::copy(first, last, std::back_inserter(c_));
//	for (AminoAcidSequence::const_iterator acid = first; acid != last; ++acid) {
//		c_.push_back(*acid);
//	}
    if (!c_[c_.size() - 1].isCTerm()) {
        c_.push_back(aminoAcids::RawAminoAcidImpl::PEPTIDE_C_TERM);
    }
}

void AminoAcidSequence::push_back(const Residue& value)
{
    // MAYBE optimize by storing n and c-term as member variables (will result in checked [], might be to slow)
    //If a C-terminal is passed, the previous C-terminal is replaced by it
    Residue last(
        aminoAcids::AminoAcid(aminoAcids::RawAminoAcidImpl::PEPTIDE_C_TERM));
    if (c_.size() == 0) {
        if (!value.isNTerm()) {
            c_.push_back(aminoAcids::RawAminoAcidImpl::PEPTIDE_N_TERM);
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

void AminoAcidSequence::pop_back()
{
    // TODO how do we deal with the sequence if it only contains c- and n-term?
    if (c_.size() > 0 && (c_[c_.size() - 1].isCTerm())) {
        Residue last = c_[c_.size() - 1];
        c_.pop_back();
        c_.pop_back();
        c_.push_back(last);
    } else {
        c_.pop_back();
    }
}

void AminoAcidSequence::makePeptideCTerm()
{
    if (size() == 0) {
        throw std::out_of_range("Unable to change amino acid sequence C-term"
            "to peptide C-term, because there is no C-term.");
    }
    if (c_.back().getAminoAcid().getRawAminoAcidKey()
            == aminoAcids::RawAminoAcidImpl::PEPTIDE_C_TERM) {
        return;
    }
    if (!c_.back().isCTerm()) {
        // TODO shall we append a peptide c-term in this case?
        throw std::out_of_range("Unable to change amino acid sequence C-term"
            "to peptide C-term, because there is no C-term.");
    }
    c_.back().changeType(aminoAcids::RawAminoAcidImpl::PEPTIDE_C_TERM);
    // TODO keep stoich config of c term?
}

void AminoAcidSequence::makePeptideNTerm()
{
    if (size() == 0) {
        throw std::out_of_range("Unable to change amino acid sequence N-term"
            "to protein N-term, because there is no N-term.");
    }
    if (c_.front().getAminoAcid().getRawAminoAcidKey()
            == aminoAcids::RawAminoAcidImpl::PEPTIDE_N_TERM) {
        return;
    }
    if (!c_.front().isNTerm()) {
        // TODO shall we prepend a peptide N-term in this case?
        throw std::out_of_range("Unable to change amino acid sequence N-term"
            "to peptide N-term, because there is no N-term.");
    }
    c_.front().changeType(aminoAcids::RawAminoAcidImpl::PEPTIDE_N_TERM);
    // TODO keep stoich config of n term?
}

void AminoAcidSequence::makeProteinCTerm()
{
    if (size() == 0) {
        throw std::out_of_range("Unable to change amino acid sequence C-term"
            "to protein C-term, because there is no C-term.");
    }
    if (c_.back().getAminoAcid().getRawAminoAcidKey()
            == aminoAcids::RawAminoAcidImpl::PROTEIN_C_TERM) {
        return;
    }
    if (!c_.back().isCTerm()) {
        // TODO shall we append a protein c-term in this case?
        throw std::out_of_range("Unable to change amino acid sequence C-term"
            "to protein C-term, because there is no C-term.");
    }
    c_.back().changeType(aminoAcids::RawAminoAcidImpl::PROTEIN_C_TERM);
    // TODO keep stoich config of c term?
}

void AminoAcidSequence::makeProteinNTerm()
{
    if (size() == 0) {
        throw std::out_of_range("Unable to change amino acid sequence N-term"
            "to protein N-term, because there is no N-term.");
    }
    if (c_.front().getAminoAcid().getRawAminoAcidKey()
            == aminoAcids::RawAminoAcidImpl::PROTEIN_N_TERM) {
        return;
    }
    if (!c_.front().isNTerm()) {
        // TODO shall we prepend a protein n-term in this case?
        throw std::out_of_range("Unable to change amino acid sequence N-term"
            "to protein N-term, because there is no N-term.");
    }
    c_.front().changeType(aminoAcids::RawAminoAcidImpl::PROTEIN_N_TERM);
    // TODO keep stoich config of n term?
}

void AminoAcidSequence::remove(
    const modifications::RawModificationImpl::RawModificationImplKeyType& modKey)
{
    for (AminoAcidSequence::iterator it = begin(); it != end(); ++it) {
        if (it->hasModification(modKey)) {
            it->removeModification();
        }
    }
}

void AminoAcidSequence::remove(const modifications::Modification& mod)
{
    for (AminoAcidSequence::iterator it = begin(); it != end(); ++it) {
        if (it->hasModification(mod)) {
            it->removeModification();
        }
    }
}

void AminoAcidSequence::append(const AminoAcidSequence& sequence)
{
    if (!sequence.empty()) {
        if (this != &sequence) {
            //The C-terminal is taken from the second sequence, so the
            //possible modifications of the C-terminal of the first sequence
            //get lost here
            if (c_.size() == 0) {
                // if we have a n-term mod at sequence, should we just use the sequence[0] instead of a new peptide n-term here?
                if (sequence.c_.front().isNTerm()) {
                    c_.push_back(sequence.c_.front());
                } else {
                    c_.push_back(aminoAcids::RawAminoAcidImpl::PEPTIDE_N_TERM);
                }
            }
            if (c_[c_.size() - 1].isCTerm()) {
                c_.pop_back();
            }
            std::copy(sequence.begin() + 1, sequence.end(),
                std::back_inserter(c_));
        } else {
            Residue last(
                aminoAcids::AminoAcid(
                    aminoAcids::RawAminoAcidImpl::PEPTIDE_C_TERM));
            if (c_[c_.size() - 1].isCTerm()) {
                last = c_.back();
                c_.pop_back();
            }
            std::copy(sequence.begin() + 1, sequence.end(),
                std::back_inserter(c_));
            c_.push_back(last);
        }
    }
}

libaas::AminoAcidSequence::iterator AminoAcidSequence::apply(
    const modifications::Modification& mod,
    const libaas::AminoAcidSequence::iterator& begin,
    const libaas::AminoAcidSequence::iterator& end) const
{
    libaas::AminoAcidSequence::iterator iter;
    aminoAcids::AminoAcid prevAcid('\0');
    aminoAcids::AminoAcid nextAcid;
    for (iter = begin; iter != end; ++iter) {
        if ((iter + 1) == (end)) {
            nextAcid = '\0';
        } else {
            nextAcid = (iter + 1)->getAminoAcid();
        }
        if (mod.isApplicable(prevAcid, iter->getAminoAcid(), nextAcid)) {
            iter->setModification(mod);
            return iter;
        }
        prevAcid = iter->getAminoAcid();
    }
    return iter;
}

std::vector<AminoAcidSequence> AminoAcidSequence::applyVariableModifications(
    const std::vector<
            modifications::RawModificationImpl::RawModificationImplKeyType>& mods,
    unsigned int maxModificationsPerPeptide) const
{
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
    unsigned int maxModificationsPerPeptide) const
{
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
    unsigned int maxModificationsPerPeptide) const
{
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
            modifications::RawModificationImpl::RawModificationImplKeyType>& mods)
{
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
    const std::vector<modifications::RawModification>& mods)
{
    ModificationList mmods;
    typedef std::vector<modifications::RawModification>::const_iterator IT;
    IT end = mods.end();
    for (IT iter = mods.begin(); iter != end; ++iter) {
        mmods.push_back(modifications::Modification(*iter));
    }
    applyFixedModifications(mmods);
}

void AminoAcidSequence::applyFixedModifications(const ModificationList& mods)
{
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
    const modifications::Modification& mod, const Size& pos)
{
    if (pos >= size()) {
        throw std::out_of_range(
            "AminoAcidSequence::applyModificationAtPosition(): Trying to apply modification at position out of bound");
    }

    // get prev amino acid
    aminoAcids::AminoAcid prev('\0');
    if (pos != 0) {
        prev = operator[](pos - 1).getAminoAcid();
    }

    // get next amino acid
    aminoAcids::AminoAcid next('\0');
    if (pos != size() - 1) {
        next = operator[](pos + 1).getAminoAcid();
    }

    // get pos amino acid
    Residue current = operator[](pos);
    if (current.isModified()) {
        throw std::out_of_range(
            "AminoAcidSequence::applyModificationAtPosition(): Residue is already modified. Cannot add more than one modification to one residue.");
    }
    // check if mod is applicable to this position
    if (!mod.isApplicable(prev, current.getAminoAcid(), next)) {
        throw std::out_of_range(
            "AminoAcidSequence::applyModificationAtPosition(): Cannot apply mod to this position.");
    }
    operator[](pos).setModification(mod);
}

void AminoAcidSequence::applyAminoAcidStoichiometryConfig(
    const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& aminoAcidConfigKey)
{
    applyAminoAcidStoichiometryConfig(StoichiometryConfig(aminoAcidConfigKey));
}

void AminoAcidSequence::applyAminoAcidStoichiometryConfig(
    const StoichiometryConfig& aminoAcidConfig)
{
    for (iterator it = begin(); it != end(); ++it) {
        it->applyAminoAcidStoichiometryConfig(aminoAcidConfig);
    }
}

void AminoAcidSequence::applyModificationStoichiometryConfig(
    const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& modificationConfigKey)
{
    applyModificationStoichiometryConfig(
        StoichiometryConfig(modificationConfigKey));
}

void AminoAcidSequence::applyModificationStoichiometryConfig(
    const StoichiometryConfig& modificationConfig)
{
    for (iterator it = begin(); it != end(); ++it) {
        it->applyModificationStoichiometryConfig(modificationConfig);
    }
}

Stoichiometry AminoAcidSequence::getStoichiometry() const
{
    // MAYBE optimize by storing the stoichiometry
    Stoichiometry ret;
    for (const_iterator iter = begin(); iter != end(); ++iter) {
        ret += iter->getStoichiometry();
    }
    return ret;
}

String AminoAcidSequence::toUnmodifiedSequenceString() const
{
    std::string s;
    for (const_iterator it = begin(); it != end(); ++it) {
        if (!it->isNTerm() && !it->isCTerm())
            s += it->getAminoAcid().getSymbol();
    }
    return s;
}

String AminoAcidSequence::toString(const Bool showTerminals) const
{
    std::string seq;
    for (const_iterator it = begin(); it != end(); ++it) {
        if (showTerminals || (!(*it).isNTerm() && !(*it).isCTerm()))
            seq += (*it).toString();
    }
    return seq;
}
String AminoAcidSequence::getModificationString() const
{
    std::ostringstream modoss;
    int pos = 0;
    for (const_iterator it = begin(); it != end(); ++it, ++pos) {
        if (it->isModified()) {
            if (!modoss.str().empty()) {
                modoss << "; ";
            }
            modifications::Modification mod = it->getModification();
            modoss << mod.getModificationId() << "("
                    << it->getAminoAcid().getSymbol() << ")@" << pos;
        }
    }
    return modoss.str();
}

std::ostream& operator<<(std::ostream& os, const AminoAcidSequence& o)
{
    typedef AminoAcidSequence::const_iterator IT;
    IT end = o.end();
    for (IT it = o.begin(); it != end; ++it) {
        os << *it << "\t";
    }
    return os;
}

} // namespace libaas
