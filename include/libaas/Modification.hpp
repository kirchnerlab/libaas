/*
 * Modification.hpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#ifndef __X_INCLUDE_X_MODIFICATION_HPP__
#define __X_INCLUDE_X_MODIFICATION_HPP__

#include <libaas/RawModification.hpp>
#include <libaas/StoichiometryConfig.hpp>
#include <libaas/Stoichiometry.hpp>
#include <libaas/Specificity.hpp>

#include <iostream>
#include <vector>

namespace libaas {
namespace modifications {

/** Modification
 *
 */
class Modification {

public:
	/** Constructor
	 *
	 */
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
	void setStoichiometryConfig(
			const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid);
	const StoichiometryConfig& getStoichiometryConfig() const;

	const Stoichiometry& getStoichiometry() const;

	void addSpecificitiy(const Specificity& specificity);
	void setSpecificities(const std::vector<Specificity>& specificities);
	const std::vector<Specificity> getSpecificities() const;
	void reinitializeSpecificities();
	void clearSpecificities();

	const RawModificationImpl::RawModificationImplKeyType& getModificationId() const;
//	const Size& getAccession() const;
	const String& getPSIName() const;
	const String& getInterimName() const;
	const String& getDescription() const;
	const std::vector<String>& getAltDescriptions() const;
	const Stoichiometry& getRawStoichiometry() const;
	const std::vector<Specificity>& getRawSpecificities() const;
	Bool isVerified() const;

	bool operator==(const Modification& s) const;
	//Modification& operator=(const Modification& rhs);

	// Getter for modification stuff

private:

	/** Re-initializes the Modification.
	 *
	 * A call of this function will set the specificities to the default
	 * specificities of the RawModification and invokes the recalculation of
	 * the stoichiometry using the present stoichiometry configuration.
	 *
	 */
	void reinit();

	/** Recalculates the stoichiometry of the modification using the present
	 * stoichiometry configuration.
	 *
	 */
	void recalculateStoichiometry();

	RawModification modification_;
	StoichiometryConfig stoichiometryConfig_;
	libaas::Stoichiometry stoichiometry_;
	std::vector<Specificity> specificities_;

};
// class Modification

std::ostream& operator<<(std::ostream&, const Modification&);

} // namespace modifications
} // namespace libaas

#endif /* __X_INCLUDE_X_MODIFICATION_HPP__ */
