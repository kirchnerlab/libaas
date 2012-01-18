#include <libaas/RawModification.hpp>

#include <stdlib.h>

using namespace libaas::modifications;

int main(int argc, const char* argv[])
{

    libaas::Size n = 100000;
    libaas::String mod = "Acetyl";
    if (argc == 2) {
        mod = argv[1];
    } else
        if (argc == 3) {
            mod = argv[1];
            n = atoi(argv[2]);
        } else
            if (argc > 3) {
                std::cerr
                        << "Usage: simpleTest_rawModification <modification string> <#modifications>"
                        << std::endl;
                std::cerr
                        << "\tdefault modification string is \"Acetyl\" and #modifications is 100.000"
                        << std::endl;
            }

    std::cout << "Modification: " << mod << std::endl;
    std::cout << "#Modifications: " << n << std::endl;

    // n mods erzeugen
    std::vector<RawModification> a(n, RawModification(mod));
    // n mods kopieren
    std::vector<RawModification> b(a);
    // n mods zerstoeren
    a.clear();

    return 0;
}
