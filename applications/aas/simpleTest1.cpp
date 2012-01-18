#include <libaas/RawModification.hpp>

using namespace libaas::modifications;

int main()
{

    libaas::Size n = 1000000;

    // n mods erzeugen
    std::vector<RawModification> a(n, RawModification("Acetyl"));
    // n mods kopieren
    std::vector<RawModification> b(a);
    // n mods zerstoeren
    a.clear();

    return 0;
}
