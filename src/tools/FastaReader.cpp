/*
 * FastaReader.cpp
 *
 *  Created on: 18.01.2012
 *      Author: mwilhelm
 */

#include <libaas/tools/FastaReader.hpp>
#include <libaas/Error.hpp>

#include <fstream>

namespace libaas {
namespace tools {

FastaReader::FastaReader(const libaas::String& filename,
    const Digester& digester,
    libaas::AminoAcidSequence::ModificationList& fixedModifications) :
        filename_(filename), digester_(digester)
{
    typedef libaas::AminoAcidSequence::ModificationList::iterator VSSI;
    try {
        // build modifications vectors: fixed mods
        for (VSSI modit = fixedModifications.begin();
                modit != fixedModifications.end(); ++modit) {
            fixedModifications_.push_back(*modit);
        }
    } catch (libaas::errors::RuntimeError& e) {
        throw;
    }
}

FastaReader::~FastaReader()
{
}

void FastaReader::read(AminoAcidSequences& proteinIds) const
{
    DescSeq ds;
    // read the fasta file
    parse(ds);
    // digest the protein sequences and apply modifications
    digest(ds, proteinIds);
    // apply modifications
    modify(proteinIds);
}

void FastaReader::parse(DescSeq& ds) const
{
    // simple state machine to parse FASTA format files
    enum State
    {
        STATE_START, STATE_DESC, STATE_SEQ
    };
    State state = STATE_START;
    // open file
    std::ifstream ifs(filename_.c_str());
    if (!ifs) {
        throw libaas::errors::RuntimeError(
            "Cound not open " + filename_ + ".");
    }
    libaas::String desc, seq;
    while (!ifs.eof()) {
        libaas::String line;
        std::getline(ifs, line);
        if (line.empty()) {
            // ignore whitespace
            continue;
        }
        if (line[0] == '>' || line[0] == ';') {
            switch (state) {
                case STATE_START:
                    desc = line;
                    state = STATE_DESC;
                    break;
                case STATE_DESC:
                    // ignore
                    break;
                case STATE_SEQ:
                    // we finished a sequence. Store the sequence and
                    // the description.
                    ds.push_back(std::make_pair(desc, seq));
                    seq.clear();
                    state = STATE_DESC;
                    desc = line;
                    break;
            }
        } else {
            // we have a sequence
            switch (state) {
                case STATE_START:
                    // format error -- entries need to start with a description
                    throw libaas::errors::RuntimeError(
                        "Syntax error in FASTA file.");
                    break;
                case STATE_DESC:
                    // start a new sequence
                    seq = line;
                    state = STATE_SEQ;
                    break;
                case STATE_SEQ:
                    // attach line to existing sequence
                    seq += line;
                    break;
            }
        }
    }
    // we allow empty files; hence the final state is either STATE_START
    // or STATE_SEQ. Everything else is an error.
    switch (state) {
        case STATE_DESC:
            throw libaas::errors::RuntimeError("Syntax error in FASTA file.");
            break;
        case STATE_SEQ:
            // push the remaining sequence
            ds.push_back(std::make_pair(desc, seq));
            break;
        case STATE_START:
            // nothing to do
            break;
    }
}

void FastaReader::digest(DescSeq& ds, AminoAcidSequences& proteinIds) const
{
    typedef Digester::AminoAcidSequences VAAS;
    VAAS peptides;
    for (DescSeq::iterator i = ds.begin(); i != ds.end(); ++i) {
        peptides.clear();
        digester_(i->second, peptides);
        for (VAAS::const_iterator pi = peptides.begin(); pi != peptides.end();
                ++pi) {
            proteinIds.push_back(*pi);
        }
    }
}

void FastaReader::modify(AminoAcidSequences& proteinIds) const
{
    for (AminoAcidSequences::iterator it = proteinIds.begin();
            it != proteinIds.end(); ++it) {
        it->applyFixedModifications(fixedModifications_);
    }
}

} // namespace tools
} // namespace libaas
