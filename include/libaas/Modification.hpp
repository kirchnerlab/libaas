/*
 * Modification.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __LIBAAS_INCLUDE_LIBAAS_MODIFICATION_HPP__
#define __LIBAAS_INCLUDE_LIBAAS_MODIFICATION_HPP__

#include <libaas/RawModification.hpp>
#include <libaas/Specificity.hpp>
#include <libaas/Stoichiometry.hpp>
#include <libaas/StoichiometryConfig.hpp>

#include <iostream>
#include <vector>

namespace libaas {
namespace modifications {

/**Representation of an amino acid modification.
 *
 * This class is a wrapper for a RawModification. Furthermore, it provides
 * function to add custom specificities.
 */
class Modification {

public:
    Modification();
    Modification(const RawModification& modification);
    Modification(const RawModificationImpl::RawModificationImplKeyType& modid);

    Modification(const RawModification& modification,
            const StoichiometryConfig& config);
            Modification(
                    const RawModificationImpl::RawModificationImplKeyType& modid,
                    const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid);

    void setModification(const RawModification& modification);
    void setModification(
            const RawModificationImpl::RawModificationImplKeyType& modid);
    const RawModification& getModification() const;

    void setStoichiometryConfig(const StoichiometryConfig& config);
    void
            setStoichiometryConfig(
                    const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid);
    const StoichiometryConfig& getStoichiometryConfig() const;

    const Stoichiometry& getStoichiometry() const;

    void addCustomSpecificitiy(const Specificity& specificity);
    void setCustomSpecificities(const std::vector<Specificity>& specificities);
    const std::vector<Specificity> getCustomSpecificities() const;
    void clearCustomSpecificities();

    const std::vector<Specificity> getSpecificities() const;

    const RawModificationImpl::RawModificationImplKeyType
            & getModificationId() const;
    const String& getName() const;
    const String& getFullName() const;
    const std::vector<String>& getAltNames() const;
    const Stoichiometry& getRawStoichiometry() const;
    const std::vector<Specificity>& getRawSpecificities() const;
    Bool isVerified() const;

    bool operator==(const Modification& s) const;
    bool operator!=(const Modification& s) const;
    Modification& operator=(const Modification& rhs);

private:

    /** Re-initializes the modification.
     *
     * A call of this function will reset the custom specificities and invokes
     * the recalculation of the stoichiometry using the present stoichiometry
     * configuration.
     */
    void reinit();

    /** Recalculates the stoichiometry of the modification using the present
     * stoichiometry configuration.
     */
    void recalculateStoichiometry();

    RawModification modification_;
    StoichiometryConfig stoichiometryConfig_;
    libaas::Stoichiometry stoichiometry_;
    std::vector<Specificity> customSpecificities_;

};
// class Modification

std::ostream& operator<<(std::ostream&, const Modification&);

} // namespace modifications
} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_MODIFICATION_HPP__ */
