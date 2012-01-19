#include <libaas/tools/FastaReader.hpp>
#include <libaas/tools/Digester.hpp>
#include <libaas/Error.hpp>

#include <boost/regex.hpp>

#include <vector>
#include <fstream>
#include <iostream>

using namespace libaas;

int main(int argc, const char* argv[])
{
    libaas::String fastaFile;
    libaas::String modFile;
    libaas::String regex = "(R|K)([^P])";
    if (argc == 3) {
        fastaFile = argv[1];
        modFile = argv[2];
    } else
        if (argc == 4) {
            fastaFile = argv[1];
            modFile = argv[2];
            regex = argv[3];
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

    tools::Digester d(regex);

    AminoAcidSequence::ModificationList ml;
    std::ifstream ifs(modFile.c_str());
    if (!ifs) {
        throw libaas::errors::RuntimeError("Cound not open " + modFile + ".");
    }
    while (!ifs.eof()) {
        libaas::String line;
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

    libaas::Size nrs = 0;
    libaas::Size nMods = 0;
    libaas::Size nLabs = 0;
    for (tools::FastaReader::AminoAcidSequences::const_iterator it =
            aass.begin(); it != aass.end(); ++it) {
        nrs += it->size();
        for (libaas::AminoAcidSequence::const_iterator ait = it->begin();
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

    return 0;
}