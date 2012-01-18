/*
 * Digester.hpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2009,2010,2011,2012 Marc Kirchner
 * Copyright (c) 2010 Nathan Huesken
 *
 */

#ifndef DIGESTER_HPP_
#define DIGESTER_HPP_

#include <libaas/AminoAcidSequence.hpp>
#include <libaas/Types.hpp>

#include <boost/regex.hpp>

#include <vector>

namespace libaas {
namespace tools {

/**General digests class.
 * Digests peptides (AminoAcidSequences) using regular expressions.
 *
 * The regular expression are expected to be build in a way that the cleavage
 * appeares after the first submatch.
 */
class Digester
{
public:

    /**Convenience typedef of a list of amino acid sequences.
     */
    typedef std::vector<libaas::AminoAcidSequence> AminoAcidSequences;

    /** List of enzymes for which the regular expression is stored in R.
     */
    enum EnzymEnum
    {
        ARG_C_PROTEINASE = 0,
        ASP_N_ENDOPETIDASE,
        CHYMOTRYPSIN,
        LYSC,
        PEPSIN_A,
        TRYPSIN
    };

    /** Constructor.
     *  The regular expression MUST be in the format.
     *  (<beforeCleavage1>)(<afterCleavage1>)|(<beforeCleavage2)(<afterCleavage2>)| ...
     *  The parentheses are mandatory and the expression in the
     *  parentheses may not contain any parentheses resulting in more sub
     *  expressions.
     *  This ensures that the cleavage point is found by matching
     *  subexpressions.
     *  @param[in] re Regular expression identifying the positions of cleavages.
     */

    Digester(const libaas::String& re);

    /** Constructor taking a list of exceptions.
     *  The the same limitations applying to the regular expression apply
     *  to the exceptions. The exceptions mark points in the
     *  peptide where no cleavage may occur by the enzym.
     *  @param[in] re Regular expression identifying the positions of cleavages.
     *  @param[in] exceptions Regular expression identifying exceptions for cleavages.
     */
    Digester(const libaas::String& re, const libaas::String& exceptions);

    /** Constructor building a pre-defined enzym.
     *  Build a digester after the rules of a hardcoded enzym.
     *  @param[in] enzym Element of the EnzymElement list identifying the enzym.
     */
    Digester(const EnzymEnum enzym);

    /**
     * Digests the peptide \a seq; \a missedCleavages
     * indicates the maximum number of cleavages that are omitted.
     * @param[in] seq The sequence to digest.
     * @param[out] frags Vector that will be filled with the resulting sequences
     * @param[in] missedCleavages maximum number of missed cleavages that should
     *            be included in the result.
     * @return possible fragments are stored in \a frags.
     */
    void operator()(const libaas::AminoAcidSequence& seq,
        AminoAcidSequences& frags,
        libaas::UnsignedInt missedCleavages = 0) const;

private:

    /**Set of regular expressions for the build in digesters.
     */
    static libaas::String R_[];

    /**Regular expression of the digester.
     */
    boost::regex regular_expression_;

    /**Regular expressions marking the exceptions to the cleavage points given
     * by \a regular_expression.
     */
    boost::regex exceptions_;

    /**Indicates, if the exceptions should be used.
     */
    libaas::Bool exceptions_enabled_;
};

} // namespace tools
} // namespace libaas

#endif /* DIGESTER_HPP_ */
