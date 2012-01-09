SET(SRCS
	AminoAcid.cpp
	RawAminoAcid.cpp
	RawAminoAcidImpl.cpp
	AminoAcidSequence.cpp
	Element.cpp
	ElementImpl.cpp
	Isotope.cpp
	Modification.cpp
	RawModification.cpp
	RawModificationImpl.cpp
	Residue.cpp
	Specificity.cpp
	Stoichiometry.cpp
	StoichiometryConfig.cpp
	StoichiometryConfigImpl.cpp
)

ADD_LIBRARY(aas ${SRCS})
TARGET_LINK_LIBRARIES(aas
	${Boost_REGEX_LIBRARY}
	${CMAKE_THREAD_LIBS_INIT}
)

INSTALL(TARGETS aas
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    COMPONENT libraries
)

