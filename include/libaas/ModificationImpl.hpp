/*
 * ModificationImpl.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __X_INCLUDE_X_MODIFICATIONIMPL_HPP__
#define __X_INCLUDE_X_MODIFICATIONIMPL_HPP__

#include <libaas/Stoichiometry.hpp>
#include <libaas/Specificity.hpp>
#include <libaas/Types.hpp>

//#include <iostream>

namespace libaas {
namespace modifications {

/** Modification
 *
 */
class ModificationImpl {

public:

    typedef Int ModificationImplKeyType;

    ModificationImpl(ModificationImplKeyType id);

    const ModificationImplKeyType& getId() const;

    //bool operator==(const Modification& s) const;
    //Modification& operator=(const Modification& rhs);

private:

    ModificationImplKeyType id_;
    Stoichiometry stoichiometry_;

    String name_;
    std::vector<std::string> altNames_;
    String description_;
    String comment_;
    Bool approved_;
    Int recordId_;
    std::vector<Specificity> specificities_;

}; // class ModificationImpl

//std::ostream& operator<<(std::ostream&, const ModificationImpl&);

inline const ModificationImpl::ModificationImplKeyType& ModificationImpl::getId() const
{
    return id_;
}

} // namespace modifications
} // namespace libaas

#endif /* __X_INCLUDE_X_MODIFICATIONIMPL_HPP__ */
