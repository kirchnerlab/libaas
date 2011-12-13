/*
 * RawModification.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/RawModification.hpp>

namespace libaas {
namespace modifications {

bool operator<(const RawModification& lhs, const RawModification& rhs) {
	return lhs.get_key() < rhs.get_key();
}

bool operator<=(const RawModification& lhs, const RawModification& rhs) {
	return lhs.get_key() <= rhs.get_key();
}

bool operator>(const RawModification& lhs, const RawModification& rhs) {
	return lhs.get_key() > rhs.get_key();
}

bool operator>=(const RawModification& lhs, const RawModification& rhs) {
	return lhs.get_key() >= rhs.get_key();
}

} // namespace modifications
} // namespace libaas
