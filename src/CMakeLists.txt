SET(SRCS 
    Isotope.cpp
    Element.cpp
    Stoichiometry.cpp
    Modification.cpp
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

