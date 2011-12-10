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

bool Specificity::operator==(const Specificity& s) const
{
    return site_ == s.site_ && classification_ == s.classification_
            && position_ == s.position_ && neutralLoss_ == s.neutralLoss_
            && comment_ == s.comment_;
}

std::ostream& operator<<(std::ostream& os, const Specificity& s) {
    // TODO
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Specificity>& s) {
    // TODO
    return os;
}

} // namespace modifications
} // namespace libaas
