SET(SRCS 
    Isotope.cpp
    ElementImpl.cpp
    Element.cpp
    Stoichiometry.cpp
    ModificationImpl.cpp
    Modification.cpp
    AminoAcidImpl.cpp
    AminoAcid.cpp
    Residue.cpp
    AminoAcidSequence.cpp
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

