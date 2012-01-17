#include <libaas/AminoAcidSequence.hpp>

#include <vector>
#include <iostream>

using namespace libaas;

int main() {

    std::vector<AminoAcidSequence> aass;

    aass.push_back(AminoAcidSequence("ACGTQQCS"));
    aass.push_back(AminoAcidSequence("ACGTQQCS"));
    aass.push_back(AminoAcidSequence("ACGTQQCS"));

    libaas::Size n = 0;
    for (std::vector<AminoAcidSequence>::const_iterator it = aass.begin(); it != aass.end(); ++it) {
        n+=it->size();
    }

    std::cout << n << std::endl;

	return 0;
}
