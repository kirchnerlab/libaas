/*
 * RawModificationSpeedTest.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/RawModification.hpp>

#include <vector>

using namespace libaas::modifications;

int main() {

	size_t n = 1000000;
	std::vector<RawModification> l;

	for (size_t i = 0; i < n; ++i) {
		l.push_back(RawModification("Acetyl"));
	}

	return 0;
}
