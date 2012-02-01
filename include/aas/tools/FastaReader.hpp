/*
 * FastaReader.hpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2010,2011,2012 Marc Kirchner
 *
 */

#ifndef FASTAREADER_HPP_
#define FASTAREADER_HPP_

#include "aas/AminoAcidSequence.hpp"
#include "aas/tools/Digester.hpp"
#include "aas/Types.hpp"

#include <boost/regex.hpp>

namespace aas {
namespace tools {

/**General fasta-file reader.
 *
 */
class FastaReader
{
public:

    /**Convenience typedef for a list of amino acid sequences.
     */
    typedef std::vector<AminoAcidSequence> AminoAcidSequences;

    /**Constructor.
     *
     * @param[in] filename fasta file
     * @param[in] digester Digester used to digest the sequences
     * @param[in] fixedModifications Fixed modifications which are applied after the digester
     */
    FastaReader(const aas::String& filename, const Digester& digester =
            Digester(""),
        const aas::AminoAcidSequence::ModificationList& fixedModifications =
                aas::AminoAcidSequence::ModificationList());

    /**Destructor.
     */
    ~FastaReader();

    /**Reads the fasta file, digests all sequences and applies fixed modifications.
     * @param[out] aminoAcidSequences Resulting amino acid sequences
     */
    void read(AminoAcidSequences& aminoAcidSequences) const;

private:

    /**Convenience typedef for a fasta entry list.
     */
    typedef std::vector<std::pair<aas::String, aas::String> > DescSeq;

    /**Parses the fasta file.
     *
     * @param[out] ds A list containing the header information and the sequence of
     */
    void parse(DescSeq& ds) const;

    /**Digests the given list of sequences.
     *
     * @param[in] ds List of header information (first) and the sequence (second)
     * @param[out] aminoAcidSequences List of resulting amino acid sequences
     */
    void digest(const DescSeq& ds,
        AminoAcidSequences& aminoAcidSequences) const;

    /**Applies fixed modifcations to all amino acid sequences.
     *
     * @param[inout] aminoAcidSequences List of amino acid sequences
     */
    void modify(AminoAcidSequences& aminoAcidSequences) const;

    /**Fasta file name.
     */
    aas::String filename_;

    /**Digester which is used to digest the amino acid sequences.
     */
    Digester digester_;

    /**List of modifications which are applied as fixed modifications.
     */
    aas::AminoAcidSequence::ModificationList fixedModifications_;
};

} // namespace tools
} // namespace aas

#endif /* FASTAREADER_HPP_ */
