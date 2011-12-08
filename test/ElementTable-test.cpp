/*
 * ElementTable-test.cpp
 *
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include "vigra/unittest.hxx"

#include <iostream>

/** Short description.
 * Long description.
 */
struct ElementTableTestSuite : vigra::test_suite
{
    /** Constructor.
     * The ElementTableTestSuite constructor adds all ElementTable tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    ElementTableTestSuite() :
        vigra::test_suite("ElementTable")
    {
        add(testCase(&ElementTableTestSuite::testInstance));
        add(testCase(&ElementTableTestSuite::testAddElement));
    }

    void testInstance()
    {
//        ElementTable toe;
//        shouldEqual(toe.size(), static_cast<size_t>(104));
//        Element e = toe.get(8);
//        shouldEqual(e.getId(), static_cast<size_t>(8));
//        shouldEqual(e.getAtomicNumber(), static_cast<size_t>(8));
//        shouldEqual(e.getSymbol(), std::string("O"));
//        std::vector<Element::Isotope> isos = e.getIsotopes();
//        shouldEqual(isos.size(), static_cast<size_t>(3));
//        double expectedMass[] = { 15.9949141, 16.9991322, 17.9991616 };
//        double expectedFreq[] = { 0.997590, 0.000374, 0.002036 };
//        typedef std::vector<Element::Isotope>::const_iterator CI;
//        size_t k = 0;
//        for (CI i = isos.begin(); i != isos.end(); ++i, ++k) {
//            shouldEqual(expectedMass[k], i->mass);
//            shouldEqual(expectedFreq[k], i->frequency);
//        }
//        for (size_t k = 0; k < 104; ++k) {
//            std::cerr << toe.get(k) << std::endl;
//        }
    }

    void testAddElement()
    {
//        ElementTable toe;
//        shouldEqual(toe.size(), static_cast<size_t>(104));
//        Element e = toe.create();
//        shouldEqual(toe.size(), static_cast<size_t>(105));
//        e.setAtomicNumber(7331);
//        e.setSymbol("Leet");
//        Element f = toe.get(e.getId());
//        shouldEqual(f.getAtomicNumber(), e.getAtomicNumber());
//        shouldEqual(f.getSymbol(), e.getSymbol());
    }
};

/** The main function that runs the tests for class ElementTable.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ElementTableTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

