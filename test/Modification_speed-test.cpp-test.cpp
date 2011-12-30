/*
 * Modification_speed-test.cpp-test.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/RawModification.hpp>

#include "vigra/unittest.hxx"

#include <iostream>
#include <vector>

using namespace libaas::modifications;

/** Short description.
 * Long description.
 */
struct ModificationSpeedTestSuite: vigra::test_suite {
    /** Constructor.
     * The Modification_speed-test.cppTestSuite constructor adds all Modification_speed-test.cpp tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    ModificationSpeedTestSuite() :
        vigra::test_suite("Modification_speed-test.cpp")
    {
        add(testCase(&ModificationSpeedTestSuite::createFlyweights));
    }

    void createFlyweights()
    {
        size_t n = 1000000;
        size_t mem_naiv = n * sizeof(RawModificationImpl) + sizeof(std::vector<
                RawModificationImpl>);
        size_t mem_fw = n * sizeof(RawModification) + sizeof(std::vector<
                RawModification>);
        std::cout << mem_naiv << std::endl;
        std::cout << mem_fw << std::endl;
    }

};

/** The main function that runs the tests for class Modification_speed-test.cpp.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ModificationSpeedTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

