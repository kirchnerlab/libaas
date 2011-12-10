/*
 * ModificationImpl.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/ModificationImpl.hpp>

namespace libaas {
namespace modifications {

/** Constructor
 *
 */
ModificationImpl::ModificationImpl(ModificationImplKeyType id) :
    id_(id)
{
}

void ModificationImpl::setAccession(const Size& accession)
{
    accession_ = accession;
}
const Size& ModificationImpl::getAccession() const
{
    return accession_;
}

void ModificationImpl::setPSIName(const String& psiName)
{
    psiName_ = psiName;
}

const String& ModificationImpl::getPSIName() const
{
    return psiName_;
}

void ModificationImpl::setInterimName(const String& interimName)
{
    interimName_ = interimName;
}

const String& ModificationImpl::getInterimName() const
{
    return interimName_;
}

void ModificationImpl::setDescription(const String& description)
{
    description_ = description;
}

const String& ModificationImpl::getDescription() const
{
    return description_;
}

void ModificationImpl::addAltDescription(const String& altDescription)
{
    altDescriptions_.push_back(altDescription);
}

void ModificationImpl::setAltDescriptions(
        const std::vector<String>& altDescriptions)
{
    altDescriptions_ = altDescriptions;
}

const std::vector<String>& ModificationImpl::getAltDescriptions() const
{
    return altDescriptions_;
}

void ModificationImpl::setStoichiometry(const Stoichiometry& stoichiometry)
{
    stoichiometry_ = stoichiometry;
}

const Stoichiometry& ModificationImpl::getStoichiometry() const
{
    return stoichiometry_;
}

void ModificationImpl::addSpecificity(const Specificity& specificity)
{
    specificities_.push_back(specificity);
}

void ModificationImpl::setSpecificities(
        const std::vector<Specificity>& specificities)
{
    specificities_ = specificities;
}

const std::vector<Specificity>& ModificationImpl::getSpecificities() const
{
    return specificities_;
}

void ModificationImpl::setVerified(Bool verified)
{
    verified_ = verified;
}

Bool ModificationImpl::isVerified() const
{
    return verified_;
}

bool ModificationImpl::operator==(const ModificationImpl& s) const
{
    return id_ == s.id_ && accession_ == s.accession_ && psiName_ == s.psiName_
            && interimName_ == s.interimName_ && description_ == s.description_
            && altDescriptions_ == s.altDescriptions_ && stoichiometry_ == s.stoichiometry_
            && specificities_ == s.specificities_ && verified_ == s.verified_;
}

std::ostream& operator<<(std::ostream& os, const ModificationImpl& o)
{
    os << o.getId() << ":" << o.getAccession() << "\t" << o.getPSIName()
            << "\t" << o.getInterimName() << "\t" << o.getDescription() << "\t";
    typedef std::vector<String>::const_iterator IT;
    for (IT it = o.getAltDescriptions().begin(); it != o.getAltDescriptions().end(); ++it) {
        os << *it << "|";
    }
    os << "\t" << o.getStoichiometry() << "\t"
            << o.getSpecificities() << "\t" << o.isVerified();
    return os;
}

} // namspace modifications
} // namespace libaas
