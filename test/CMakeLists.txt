#
# configure/build libaas tests
#

##############################################################################
# check if have valgrind
##############################################################################
SET(HAVE_VALGRIND TRUE)
FIND_PROGRAM(VALGRIND_EXECUTABLE valgrind)
IF(VALGRIND_EXECUTABLE STREQUAL "VALGRIND_EXECUTABLE-NOTFOUND")
    MESSAGE(STATUS "WARNING: Could not find valgrind. Will NOT build memory tests.")
    SET(HAVE_VALGRIND FALSE)
ENDIF(VALGRIND_EXECUTABLE STREQUAL "VALGRIND_EXECUTABLE-NOTFOUND")

##############################################################################
# macro definitions
##############################################################################
MACRO(ADD_LIBAAS_TEST name exe src)
    STRING(REGEX REPLACE "test_([^ ]+).*" "\\1" test "${exe}" )
    # build the test
    ADD_EXECUTABLE(${exe} ${src})
    TARGET_LINK_LIBRARIES(${exe} ${TEST_LIBS})
    # add test to global list of unit test
    ADD_TEST(${name} ${exe})
    MESSAGE(STATUS "Adding test for ${name}: ${exe}.")
    # add target for the test
    STRING(REGEX REPLACE "test_([^ ]+).*" "unit_\\1" unittest_target "${exe}" )
    ADD_CUSTOM_TARGET(${unittest_target} COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${exe})
    IF (HAVE_VALGRIND) 
        #add memory test using valgrind
        STRING(REGEX REPLACE "test_([^ ]+).*" "mem_\\1" memtest_name "${exe}" )
        LIST(APPEND memtest_names ${memtest_name})
        LIST(APPEND exe_names ${exe})
        #Add target for the memory test
        ADD_CUSTOM_TARGET(${memtest_name} COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/memcheck.py ${CMAKE_CURRENT_BINARY_DIR}/${exe})
    ENDIF (HAVE_VALGRIND) 
    #Add target for the gcov coverage report for this test
    IF(ENABLE_COVERAGE)
        STRING(REGEX REPLACE "test_([^ ]+).*" "gcov_\\1" gcov_target "${exe}" )
        ADD_CUSTOM_TARGET(${gcov_target} COMMAND /bin/bash ${LIBAAS_BINARY_DIR}/scripts/for_cmake/unit_coverage.sh ${test})
    ENDIF(ENABLE_COVERAGE)
ENDMACRO(ADD_LIBAAS_TEST name exe src)


# include directories
INCLUDE_DIRECTORIES(
    ${LIBAAS_SOURCE_DIR}/test/include
    ${LIBAAS_SOURCE_DIR}/include
    ${LIBAAS_BINARY_DIR}/include
    ${LIBAAS_BINARY_DIR}/test/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#### Sources
SET(SRCS_RAWAMINOACID RawAminoAcid-test.cpp)
SET(SRCS_RAWMODIFICATION RawModification-test.cpp)
SET(SRCS_AMINOACIDSEQUENCE AminoAcidSequence-test.cpp)
SET(SRCS_ISOTOPE Isotope-test.cpp)
SET(SRCS_SPECIFICITY Specificity-test.cpp)
SET(SRCS_RESIDUE Residue-test.cpp)
SET(SRCS_STOICHIOMETRY Stoichiometry-test.cpp)
SET(SRCS_MODIFICATION Modification-test.cpp)
SET(SRCS_AMINOACID AminoAcid-test.cpp)
SET(SRCS_ELEMENT Element-test.cpp)
#### Libs
SET(TEST_LIBS aas)
IF (ENABLE_COVERAGE)
    SET(TEST_LIBS ${TEST_LIBS} gcov)
ENDIF(ENABLE_COVERAGE)
#### Tests
ADD_LIBAAS_TEST("RawAminoAcid" test_rawaminoacid ${SRCS_RAWAMINOACID})
ADD_LIBAAS_TEST("RawModification" test_rawmodification ${SRCS_RAWMODIFICATION})
ADD_LIBAAS_TEST("AminoAcidSequence" test_aminoacidsequence ${SRCS_AMINOACIDSEQUENCE})
ADD_LIBAAS_TEST("Isotope" test_isotope ${SRCS_ISOTOPE})
ADD_LIBAAS_TEST("Specificity" test_specificity ${SRCS_SPECIFICITY})
ADD_LIBAAS_TEST("Residue" test_residue ${SRCS_RESIDUE})
ADD_LIBAAS_TEST("Stoichiometry" test_stoichiometry ${SRCS_STOICHIOMETRY})
ADD_LIBAAS_TEST("Modification" test_modification ${SRCS_MODIFICATION})
ADD_LIBAAS_TEST("AminoAcid" test_aminoacid ${SRCS_AMINOACID})
ADD_LIBAAS_TEST("Element" test_element ${SRCS_ELEMENT})
LIST(LENGTH memtest_names numtests)
IF(numtests GREATER 0)
    MATH(EXPR numtests ${numtests}-1)
    FOREACH(i RANGE 0 ${numtests})
        LIST(GET memtest_names ${i} memtest_name)
        LIST(GET exe_names ${i} exe)
        MESSAGE(STATUS "Adding memory test for ${memtest_name}: ${exe}.")
        ADD_TEST(${memtest_name}
            ${CMAKE_CURRENT_SOURCE_DIR}/memtest.py ${CMAKE_CURRENT_BINARY_DIR}/${exe} ${CMAKE_BINARY_DIR})
    ENDFOREACH(i RANGE 0 ${numtests}-1)
ENDIF(numtests GREATER 0)

