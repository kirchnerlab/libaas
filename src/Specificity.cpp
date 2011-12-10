/*
 * Specificity.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Specificity.hpp>

namespace libaas {
namespace modifications {

/** Constructor
 *
 */
Specificity::Specificity()
{

}

void Specificity::setSite(const libaas::aminoAcids::AminoAcid& aminoAcid)
{
    site_ = aminoAcid;
}

const libaas::aminoAcids::AminoAcid& Specificity::getSite() const
{
    return site_;
}

void Specificity::setClassification(const Classification& classification)
{
    classification_ = classification;
}

const Specificity::Classification& Specificity::getClassification() const
{
    return classification_;
}

void Specificity::setPosition(const Position& position)
{
    position_ = position;
}
const Specificity::Position& Specificity::getPosition() const
{
    return position_;
}

void Specificity::setNeutralLoss(const Stoichiometry& stoichiometry)
{
    neutralLoss_ = stoichiometry;
}

const Stoichiometry& Specificity::getNeutralLoss() const
{
    return neutralLoss_;
}

void Specificity::setComment(const String& comment)
{
    comment_ = comment;
}

const String& Specificity::getComment() const
{
    return comment_;
}

bool Specificity::operator==(const Specificity& s) const
{
    return site_ == s.site_ && classification_ == s.classification_
            && position_ == s.position_ && neutralLoss_ == s.neutralLoss_
            && comment_ == s.comment_;
}

std::ostream& operator<<(std::ostream& os, const Specificity& s)
{
    os << s.getSite() << "\t" << s.getClassification() << "\t"
            << s.getPosition() << "\t" << s.getPosition() << "\t"
            << s.getNeutralLoss() << "\t" << s.getComment();
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Specificity>& s)
{
    typedef std::vector<Specificity>::const_iterator IT;
    for (IT it = s.begin(); it != s.end(); ++it) {
        os << *it << "|";
    }
    return os;
}

} // namespace modifications
} // namespace libaas
