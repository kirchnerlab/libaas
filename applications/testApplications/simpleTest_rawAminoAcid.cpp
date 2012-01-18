#include <libaas/RawAminoAcid.hpp>

using namespace libaas::aminoAcids;

int main(int argc, const char* argv[])
{

    libaas::Size n = 100000;
    libaas::String aa = "C";
    if (argc == 2) {
        aa = argv[1];
    } else
        if (argc == 3) {
            aa = argv[1];
            n = atoi(argv[2]);
        } else
            if (argc > 3) {
                std::cerr
                        << "Usage: simpleTest_rawModification <amino acid string> <#aminoacids>"
                        << std::endl;
                std::cerr
                        << "\tdefault amino acid string is \"C\" and #aminoacids is 100.000"
                        << std::endl;
            }

    std::cout << "Amino acid: " << aa << std::endl;
    std::cout << "#Amino acids: " << n << std::endl;

    // n mods erzeugen
    std::vector<RawAminoAcid> a(n,
        RawAminoAcid(RawAminoAcidImpl::getKeyForAminoAcidString(aa)));
    // n mods kopieren
    std::vector<RawAminoAcid> b(a);
    // n mods zerstoeren
    a.clear();

    return 0;
}
