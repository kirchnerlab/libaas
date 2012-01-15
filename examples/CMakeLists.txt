#
# configure/build libaas examples
#

# include directories
INCLUDE_DIRECTORIES(
    ${LIBAAS_SOURCE_DIR}/test/include
    ${LIBAAS_SOURCE_DIR}/include
    ${LIBAAS_BINARY_DIR}/include
    ${LIBAAS_BINARY_DIR}/test/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#### Sources
ADD_EXECUTABLE(Elements Elements.cpp)
TARGET_LINK_LIBRARIES(Elements aas)

ADD_EXECUTABLE(StoichiometryConfigs StoichiometryConfigs.cpp)
TARGET_LINK_LIBRARIES(StoichiometryConfigs aas)

ADD_EXECUTABLE(RawModifications RawModifications.cpp)
TARGET_LINK_LIBRARIES(RawModifications aas)

ADD_EXECUTABLE(Modifications Modifications.cpp)
TARGET_LINK_LIBRARIES(Modifications aas)

ADD_EXECUTABLE(RawModificationSpeedTest RawModificationSpeedTest.cpp)
TARGET_LINK_LIBRARIES(RawModificationSpeedTest aas)

ADD_EXECUTABLE(Complex1 Complex1.cpp)
TARGET_LINK_LIBRARIES(Complex1 aas)

ADD_EXECUTABLE(RawAminoAcid RawAminoAcid.cpp)
TARGET_LINK_LIBRARIES(RawAminoAcid aas)

ADD_EXECUTABLE(AminoAcid AminoAcid.cpp)
TARGET_LINK_LIBRARIES(AminoAcid aas)

ADD_EXECUTABLE(Residue Residue.cpp)
TARGET_LINK_LIBRARIES(Residue aas)

ADD_EXECUTABLE(AminoAcidSequence AminoAcidSequence.cpp)
TARGET_LINK_LIBRARIES(AminoAcidSequence aas)

