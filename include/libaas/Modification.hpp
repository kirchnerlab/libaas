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

#include <iostream>

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
	void setModification(const RawModificationImpl::RawModificationImplKeyType& modid);
	const RawModification& getModification() const;

	void setStoichiometryConfig(const StoichiometryConfig& config);
	void setStoichiometryConfig(const StoichiometryConfigImpl::StoichiometryConfigImplKeyType& configid);
	const StoichiometryConfig& getStoichiometryConfig() const;

	bool operator==(const Modification& s) const;
	//Modification& operator=(const Modification& rhs);

private:

	RawModification modification_;
	StoichiometryConfig stoichiometryConfig_;

};
// class Modification

std::ostream& operator<<(std::ostream&, const Modification&);

}// namespace modifications
} // namespace libaas

#endif /* __X_INCLUDE_X_MODIFICATION_HPP__ */
