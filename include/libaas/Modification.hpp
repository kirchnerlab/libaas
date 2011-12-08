/*
 * Modification.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 *
 */

#ifndef __X_INCLUDE_X_MODIFICATION_HPP__
#define __X_INCLUDE_X_MODIFICATION_HPP__

#include <libaas/Stoichiometry.hpp>
#include <libaas/Specificity.hpp>

#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/flyweight/no_tracking.hpp>

//#include <iostream>

namespace libaas {

// forward definition
struct modification_id_extractor;

/** Modification
 *
 */
class Modification {

public:

    typedef int ModificationKeyType;
    typedef boost::flyweight<boost::flyweights::key_value<
            libaas::Modification::ModificationKeyType, libaas::Modification,
            libaas::modification_id_extractor>, boost::flyweights::no_tracking>
            ModificationRef;

    Modification(ModificationKeyType id);

    const ModificationKeyType& getId() const;

    //bool operator==(const Modification& s) const;
    //Modification& operator=(const Modification& rhs);

private:

    ModificationKeyType id_;
    Stoichiometry stoichiometry_;

    std::string name_;
    std::vector<std::string> altNames_;
    std::string description_;
    std::string comment_;
    bool approved_;
    int recordId_;
    std::vector<Specificity> specificities_;

}; // class Modification

struct modification_id_extractor {
    const Modification::ModificationKeyType& operator()(const Modification& m) const
    {
        return m.getId();
    }
};

//std::ostream& operator<<(std::ostream&, const Modification&);
//istream& operator>>(std::istream&, Modification&);

} // namespace libaas

#endif /* __X_INCLUDE_X_MODIFICATION_HPP__ */
