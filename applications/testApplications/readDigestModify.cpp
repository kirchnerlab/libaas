#include <aas/tools/FastaReader.hpp>
#include <aas/tools/Digester.hpp>
#include <aas/Error.hpp>

#include <boost/regex.hpp>

#include <vector>
#include <fstream>
#include <iostream>

using namespace aas;

int main(int argc, const char* argv[])
{
    aas::String fastaFile;
    aas::String modFile;
    aas::String regex = "(R|K)([^P])";
    if (argc == 3) {
        fastaFile = argv[1];
        modFile = argv[2];
    } else
        if (argc == 4) {
            fastaFile = argv[1];
            modFile = argv[2];
            aas::String r = argv[3];
            if (r == "x") {
                regex = "";
            } else {
                regex = argv[3];
            }
        } else {
            std::cerr
                    << "Usage: readDigestModify <fasta> <modifications> <regex>"
                    << std::endl;
            std::cerr << "\t default regex is \"(R|K)([^P])\"(trypsin)"
                    << std::endl;
            return 1;
        }

    std::cout << "Fasta file: " << fastaFile << std::endl;
    std::cout << "Modification file: " << modFile << std::endl;
    std::cout << "Digester regex: " << regex << std::endl;

    tools::Digester d(regex);

    AminoAcidSequence::ModificationList ml;
    std::ifstream ifs(modFile.c_str());
    if (!ifs) {
        throw aas::errors::RuntimeError("Cound not open " + modFile + ".");
    }
    while (!ifs.eof()) {
        aas::String line;
        std::getline(ifs, line);
        if (line.empty()) {
            // ignore whitespace
            continue;
        }
        ml.push_back(modifications::Modification(line));
    }

    tools::FastaReader fr(fastaFile, d, ml);

    tools::FastaReader::AminoAcidSequences aass;
    fr.read(aass);

    aas::Size nrs = 0;
    aas::Size nMods = 0;
    aas::Size nLabs = 0;
    stoichiometries::Stoichiometry sum;
    for (tools::FastaReader::AminoAcidSequences::const_iterator it =
            aass.begin(); it != aass.end(); ++it) {
        sum += it->getStoichiometry();
        nrs += it->size();
        for (aas::AminoAcidSequence::const_iterator ait = it->begin();
                ait != it->end(); ++ait) {
            if (ait->isModified()) {
                ++nMods;
            }
            if (ait->isLabeled()) {
                ++nLabs;
            }
        }
    }

    std::cout << "Number of sequences: " << aass.size() << std::endl;
    std::cout << "Number of residues: " << nrs << std::endl;
    std::cout << "Number of modifications: " << nMods << std::endl;
    std::cout << "Number of labels: " << nLabs << std::endl;
    std::cout << "Summed stoichiometry: " << sum.toString() << std::endl;

    return 0;
}
