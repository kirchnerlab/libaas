/*
 * RawModificationImpl.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/RawModificationImpl.hpp>

namespace libaas {
namespace modifications {

/** Constructor
 *
 */
RawModificationImpl::RawModificationImpl(RawModificationImplKeyType id) :
		id_(id) {
}

void RawModificationImpl::setAccession(const Size& accession) {
	accession_ = accession;
}
const Size& RawModificationImpl::getAccession() const {
	return accession_;
}

void RawModificationImpl::setPSIName(const String& psiName) {
	psiName_ = psiName;
}

const String& RawModificationImpl::getPSIName() const {
	return psiName_;
}

void RawModificationImpl::setInterimName(const String& interimName) {
	interimName_ = interimName;
}

const String& RawModificationImpl::getInterimName() const {
	return interimName_;
}

void RawModificationImpl::setDescription(const String& description) {
	description_ = description;
}

const String& RawModificationImpl::getDescription() const {
	return description_;
}

void RawModificationImpl::addAltDescription(const String& altDescription) {
	altDescriptions_.push_back(altDescription);
}

void RawModificationImpl::setAltDescriptions(
		const std::vector<String>& altDescriptions) {
	altDescriptions_ = altDescriptions;
}

const std::vector<String>& RawModificationImpl::getAltDescriptions() const {
	return altDescriptions_;
}

void RawModificationImpl::setStoichiometry(const Stoichiometry& stoichiometry) {
	stoichiometry_ = stoichiometry;
}

const Stoichiometry& RawModificationImpl::getStoichiometry() const {
	return stoichiometry_;
}

void RawModificationImpl::addSpecificity(const Specificity& specificity) {
	specificities_.push_back(specificity);
}

void RawModificationImpl::setSpecificities(
		const std::vector<Specificity>& specificities) {
	specificities_ = specificities;
}

const std::vector<Specificity>& RawModificationImpl::getSpecificities() const {
	return specificities_;
}

void RawModificationImpl::setVerified(Bool verified) {
	verified_ = verified;
}

Bool RawModificationImpl::isVerified() const {
	return verified_;
}

bool RawModificationImpl::operator==(const RawModificationImpl& s) const {
	return id_ == s.id_ && accession_ == s.accession_ && psiName_ == s.psiName_
			&& interimName_ == s.interimName_ && description_ == s.description_
			&& altDescriptions_ == s.altDescriptions_
			&& stoichiometry_ == s.stoichiometry_
			&& specificities_ == s.specificities_ && verified_ == s.verified_;
}

std::ostream& operator<<(std::ostream& os, const RawModificationImpl& o) {
	os << o.getId() << ":" << o.getAccession() << "\t" << o.getPSIName() << "\t"
			<< o.getInterimName() << "\t" << o.getDescription() << "\t";
	typedef std::vector<String>::const_iterator IT;
	for (IT it = o.getAltDescriptions().begin();
			it != o.getAltDescriptions().end(); ++it) {
		os << *it << "|";
	}
	os << "\t" << o.getStoichiometry();
	os << "\t" << o.getSpecificities() << "\t" << o.isVerified();
	return os;
}

} // namspace modifications
} // namespace libaas
