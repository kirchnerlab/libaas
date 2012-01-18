/*
 * FastaReader.hpp
 *
 *  Created on: 18.01.2012
 *      Author: mwilhelm
 */

#ifndef FASTAREADER_HPP_
#define FASTAREADER_HPP_

#include <libaas/AminoAcidSequence.hpp>
#include <libaas/tools/Digester.hpp>
#include <libaas/Types.hpp>

#include <boost/regex.hpp>

namespace libaas {
namespace tools {

class FastaReader
{
public:

    typedef std::vector<AminoAcidSequence> AminoAcidSequences;

    FastaReader(const libaas::String& filename, const Digester& digester,
        libaas::AminoAcidSequence::ModificationList& fixedModificationNames);

    ~FastaReader();

    void read(AminoAcidSequences& proteinIds) const;

private:
    typedef std::vector<std::pair<libaas::String, libaas::String> > DescSeq;
    void parse(DescSeq& ds) const;
    void digest(DescSeq& ds, AminoAcidSequences& proteinIds) const;
    void modify(AminoAcidSequences& proteinIds) const;

    libaas::String filename_;
    Digester digester_;
    libaas::AminoAcidSequence::ModificationList fixedModifications_;
};

} // namespace tools
} // namespace libaas

#endif /* FASTAREADER_HPP_ */
