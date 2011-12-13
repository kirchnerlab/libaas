SET(SRCS 
	AminoAcid.cpp
	AminoAcidImpl.cpp
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
	${CMAKE_THREAD_LIBS_INIT}
)

INSTALL(TARGETS aas
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    COMPONENT libraries
)

