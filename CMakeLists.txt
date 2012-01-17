PROJECT(LIBAAS)

# require at least cmake 2.6
cmake_minimum_required(VERSION 2.6)
# include macro definitions
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/macros/require_out_of_src_build.cmake)
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#############################################################################
# versioning
#############################################################################
include(macros/GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC MSTK_VERSION)

#############################################################################
# build libraries
#############################################################################

# require boost
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD OFF)
FIND_PACKAGE(Boost COMPONENTS regex REQUIRED)
IF (NOT ( Boost_MAJOR_VERSION EQUAL 1 AND Boost_MINOR_VERSION GREATER 39))
    MESSAGE(SEND_ERROR "Require Boost >= 1.40.0")
ENDIF (NOT(Boost_MAJOR_VERSION EQUAL 1 AND Boost_MINOR_VERSION GREATER 39))
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
MESSAGE(STATUS "${Boost_INCLUDE_DIRS}")
MESSAGE(STATUS "${Boost_LIBRARY_DIRS}")

# require out-of-source build
MACRO_REQUIRE_OUT_OF_SRC_BUILD("LIBAAS requires out-of-source builds.")

# more warnings against everything
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion -Wall" )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX0X_FLAGS}" )

CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/libaas/config.hpp.cmake 
    ${LIBAAS_BINARY_DIR}/include/libaas/config.hpp
)

# testing and memtests
OPTION(ENABLE_TESTING "Compile tests" ON)
OPTION(ENABLE_COVERAGE "Enable GCov coverage analysis (defines a 'coverage' target and enforces static build of libaas)" OFF)
OPTION(ENABLE_EXAMPLES "Compile examples" OFF)

# global include dirs
INCLUDE_DIRECTORIES(
    ${LIBAAS_SOURCE_DIR}/include
    ${LIBAAS_BINARY_DIR}/include
)

#threads
#this is needed for boost::flyweight thread safety.
# We might be able to disable this if Threads is not found, see boost::flyweight thread safety
find_package(Threads REQUIRED)

#############################################################################
# syncing docs
#############################################################################
#ADD_CUSTOM_TARGET(syncdocs COMMAND ${LIBAAS_SOURCE_DIR}/scripts/sync-docs-gh-pages.sh ${LIBAAS_SOURCE_DIR} ${LIBAAS_BINARY_DIR})
#ADD_DEPENDENCIES(syncdocs doc)

#############################################################################
# code coverage analysis
#############################################################################
IF (ENABLE_COVERAGE)
    SET (ENABLE_EXAMPLES ON)
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    CONFIGURE_FILE(${LIBAAS_SOURCE_DIR}/cmake/scripts/coverage.sh.in
        ${LIBAAS_BINARY_DIR}/cmake/scripts/coverage.sh
        @ONLY IMMEDIATE
    )
    CONFIGURE_FILE(${LIBAAS_SOURCE_DIR}/cmake/scripts/unit_coverage.sh.in
        ${LIBAAS_BINARY_DIR}/cmake/scripts/unit_coverage.sh
        @ONLY IMMEDIATE
    )
    CONFIGURE_FILE(${LIBAAS_SOURCE_DIR}/test/gcov.css
        ${LIBAAS_BINARY_DIR}/test/scripts/coverage/gcov.css
        @ONLY IMMEDIATE
    )
    ADD_CUSTOM_TARGET(
        coverage COMMAND /bin/bash ${LIBAAS_BINARY_DIR}/cmake/scripts/coverage.sh
    )
ENDIF(ENABLE_COVERAGE)

#############################################################################
# regression tests
#############################################################################
SET(UPDATE_TYPE git)
IF (ENABLE_TESTING)
  INCLUDE(CTest)
  ENABLE_TESTING()
  ADD_SUBDIRECTORY(test)
ENDIF (ENABLE_TESTING)

#############################################################################
# build lib
#############################################################################
ADD_SUBDIRECTORY(src)

############################################################################
# examples
############################################################################
IF (ENABLE_EXAMPLES)
    ADD_SUBDIRECTORY(examples)
ENDIF (ENABLE_EXAMPLES)

ADD_SUBDIRECTORY(applications)

#############################################################################
# documentation
#############################################################################
# doxygen support
CONFIGURE_FILE(${LIBAAS_SOURCE_DIR}/doc/Doxyfile.cmake
    ${LIBAAS_BINARY_DIR}/doc/Doxyfile
    @ONLY IMMEDIATE
    )
FIND_PACKAGE(Doxygen)

# target for doxygen
ADD_CUSTOM_TARGET(doc COMMAND ${DOXYGEN} ${LIBAAS_BINARY_DIR}/doc/Doxyfile)

#############################################################################
# installation
#############################################################################
# location, location, location
IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
SET(CMAKE_INSTALL_PREFIX
"/usr/local" CACHE PATH "libaas install prefix" FORCE
)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
# headers
INSTALL(DIRECTORY ${LIBAAS_SOURCE_DIR}/include/libaas
    DESTINATION include
    COMPONENT headers
    REGEX "/.git$" EXCLUDE
    PATTERN "config.hpp.cmake" EXCLUDE)

# config.h
INSTALL(FILES ${LIBAAS_BINARY_DIR}/include/libaas/config.hpp
    DESTINATION include/libaas
    COMPONENT headers)

# documentation
INSTALL(DIRECTORY ${LIBAAS_BINARY_DIR}/doc
    DESTINATION share/libaas
    COMPONENT documentation
    PATTERN "Doxyfile" EXCLUDE)

##############################################################################
## packaging
##############################################################################
## FIXME: make sure that the documentation is compiled and pdfs are 
##        generated prior to packaging!
#
set(CPACK_PACKAGE_NAME "libaas")
set(CPACK_PACKAGE_VENDOR "massquito.net")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An amino acid sequence library.")

# CPack version strings
SET(CPACK_PACKAGE_VERSION_MAJOR 1)
SET(CPACK_PACKAGE_VERSION_MINOR 0)
SET(CPACK_PACKAGE_VERSION_PATCH 1)

SET(CPACK_RESOURCE_FILE_README "${LIBAAS_SOURCE_DIR}/README")
SET(CPACK_RESOURCE_FILE_LICENSE "${LIBAAS_SOURCE_DIR}/LICENSE")

set(CPACK_COMPONENTS_ALL libraries headers documentation examples)
set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ Development Headers")
set(CPACK_COMPONENT_DOCUMENTATION_DISPLAY_NAME "C++ Interface Documentation")
set(CPACK_COMPONENT_EXAMPLES_DISPLAY_NAME "Compiled Examples")

set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION
    "Compiled libraries.")
set(CPACK_COMPONENT_HEADERS_DESCRIPTION
    "C++ header files for libaas development.")
set(CPACK_COMPONENT_DOCUMENTATION_DESCRIPTION
    "The C++ libaas interface documentation (Doxygen).")
set(CPACK_COMPONENT_EXAMPLES_DESCRIPTION
    "Compiled examples.")

INCLUDE(CPack)

MESSAGE(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
