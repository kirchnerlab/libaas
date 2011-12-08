/*
 * ModificationImpl.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 *
 */

#ifndef __X_INCLUDE_X_MODIFICATIONIMPL_HPP__
#define __X_INCLUDE_X_MODIFICATIONIMPL_HPP__

#include <libaas/Stoichiometry.hpp>
#include <libaas/Specificity.hpp>

//#include <iostream>

namespace libaas {

// forward definition
struct modification_id_extractor;

/** Modification
 *
 */
class ModificationImpl {

public:

    typedef int ModificationImplKeyType;

    ModificationImpl(ModificationImplKeyType id);

    const ModificationImplKeyType& getId() const;

    //bool operator==(const Modification& s) const;
    //Modification& operator=(const Modification& rhs);

private:

    ModificationImplKeyType id_;
    Stoichiometry stoichiometry_;

    std::string name_;
    std::vector<std::string> altNames_;
    std::string description_;
    std::string comment_;
    bool approved_;
    int recordId_;
    std::vector<Specificity> specificities_;

}; // class ModificationImpl

//std::ostream& operator<<(std::ostream&, const ModificationImpl&);
//istream& operator>>(std::istream&, ModificationImpl&);

} // namespace libaas

#endif /* __X_INCLUDE_X_MODIFICATIONIMPL_HPP__ */
