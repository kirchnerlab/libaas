/*
 * Element-test.cpp
 *
 * Copyright (c) 2011 Mathias Wilhelm
 * Copyright (c) 2011 Marc Kirchner
 *
 */

#include <libaas/Element.hpp>

#include "vigra/unittest.hxx"

#include <iostream>
#include <vector>

using namespace libaas::elementTable;

/** Short description.
 * Long description.
 */
struct ElementTestSuite: vigra::test_suite {
    /** Constructor.
     * The ElementTestSuite constructor adds all Element tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    ElementTestSuite() :
        vigra::test_suite("Element")
    {
        add(testCase(&ElementTestSuite::testElement));
        add(testCase(&ElementTestSuite::testElementRef));
        add(testCase(&ElementTestSuite::testAddElement));
        add(testCase(&ElementTestSuite::testAddElementRef));
        add(testCase(&ElementTestSuite::testOverrideUninitializedElement));
        add(testCase(&ElementTestSuite::testOverrideInitializedElement));
    }

    // test general functionality of Element
    void testElement()
    {
        // test getter and setter
        ElementImpl::ElementImplKeyType k_t1 = 100;
        std::string s_t1 = "As";
        size_t an_t1 = 100;
        ElementImpl t1(k_t1, s_t1, an_t1);
        t1.addIsotope(10, 0.9);
        t1.addIsotope(11, 0.1);

        shouldEqual(t1.getId(), k_t1);
        shouldEqual(t1.getSymbol(), s_t1);
        shouldEqual(t1.getAtomicNumber(), an_t1);

        Isotope i1 = t1.getIsotopes()[0];
        shouldEqual(i1.getMass(), 10);
        shouldEqual(i1.getFrequency(), 0.9);
        Isotope i2 = t1.getIsotopes()[1];
        shouldEqual(i2.getMass(), 11);
        shouldEqual(i2.getFrequency(), 0.1);

        ElementImpl t2 = t1;
        shouldEqual(t1, t2);
        t2.addIsotope(12, 0.4);
        shouldEqual(t1 == t2, false);
        shouldEqual(t1 != t2, true);

        // test free id stuff
        ElementImpl::ElementImplKeyType nEntries = 103;
        ElementImpl::ElementImplKeyType numberOfStandardElements =
                ElementImpl::getNumberOfStandardElements();
        shouldEqual(numberOfStandardElements, nEntries);
        ElementImpl::ElementImplKeyType freeId = ElementImpl::getNextId();
        shouldEqual(freeId, (ElementImpl::ElementImplKeyType) 104);
        freeId = ElementImpl::getNextId();
        shouldEqual(freeId, (ElementImpl::ElementImplKeyType) 105);

        // test a standard element
        ElementImpl::ElementImplKeyType k1 = 16;
        Element e(k1);

        std::vector<Isotope> is;
        is.push_back(Isotope(31.972070, 0.9502));
        is.push_back(Isotope(32.971456, 0.0075));
        is.push_back(Isotope(33.967866, 0.0421));
        is.push_back(Isotope(35.967080, 0.0002));

        shouldEqual(e.get().getId(), (ElementImpl::ElementImplKeyType) 16);
        shouldEqual(e.get().getSymbol(), "S");
        shouldEqual(e.get().getAtomicNumber(), (size_t) 16);
        const std::vector<Isotope>& isotopes = e.get().getIsotopes();
        typedef std::vector<Isotope>::const_iterator IT;
        IT it1, it2;
        for (it1 = isotopes.begin(), it2 = is.begin(); it1 != isotopes.end()
                && it2 != is.end(); ++it1, ++it2) {
            shouldEqual(*it1, *it2);
        }
        shouldEqual(it1 == isotopes.end() && it2 == is.end(), true);
    }

    // test whether the flyweights work as intended
    void testElementRef()
    {
        ElementImpl::ElementImplKeyType k1 = 2, k2 = 3;

        // create two different elements without using the factory
        ElementImpl e_2(k1);
        ElementImpl e_3(k2);

        // create the same elements again, but using the flyweight implementation
        Element er_2(k1);
        Element er_3(k2);

        // testing equality
        shouldEqual(e_2, er_2.get());
        shouldEqual(e_3, er_3.get());

        // testing whether the id extractor works as correctly
        shouldEqual(er_2.get_key(), er_2.get().getId());
        shouldEqual(er_3.get_key(), er_3.get().getId());

        // retrieve the same elements again
        Element er_t2(k1);
        Element er_t3(k2);

        // test whether the old references and new references point to the same
        // object
        shouldEqual(&er_2.get(), &er_t2.get());
        shouldEqual(&er_3.get(), &er_t3.get());
    }

    // testing static function to add an element
    void testAddElement() {
        // setting up test data
        ElementImpl::ElementImplKeyType k1 = 1;
        libaas::String symbol = "HH";
        libaas::String symbol2 = "HHH";
        libaas::Size atomicNumber = 1;
        std::vector<Isotope> is;
        libaas::Double mass = 12.23;
        libaas::Double frequency = 24.45;
        Isotope isotope(mass, frequency);
        is.push_back(isotope);

        // adding not existing element
        shouldEqual(ElementTable::addElement(k1, symbol, atomicNumber, is), true);
        Element e_r(k1);
        ElementImpl e(k1, symbol, atomicNumber);
        e.setIsotopes(is);
        // added element should be equal to the one intended
        shouldEqual(e_r,e);

        // a second try to add an element with the same id should fail
        shouldEqual(ElementTable::addElement(k1, symbol2, atomicNumber, is), false);
        // and the element added in the frist place should stay the same
        shouldEqual(Element(k1), e);
        ElementImpl e2(k1, symbol2, atomicNumber);
        e.setIsotopes(is);
        shouldEqual(Element(k1) == e2, false);
    }

    // test whether we can add a reference to the flyweight table of elements
    void testAddElementRef()
    {
        // first est should result in an out_of_range exceptions since the
        // default ElementTable does no contain an Element with ID 2000
        bool thrown = false;
        try {
            Element test(2000);
        } catch (std::out_of_range& e) {
            thrown = true;
        }
        shouldEqual(thrown, true);

        // create an arbitrary element
        ElementImpl::ElementImplKeyType k1 = 2000;
        ElementImpl t(k1, "Fu", 2000);
        t.addIsotope(100, 0.99);
        t.addIsotope(101, 0.01);
        // add element to the flyweight table
        Element tr(t);

        // test equality of the original element and the const ref
        shouldEqual(t, tr);
        shouldEqual(t.getId(), tr.get_key());

        // retrieve the element directly from the flyweight table
        Element tr_t(k1);

        // test equality of two const refs of the same element
        shouldEqual(tr, tr_t);
        // test reference pointer to ensure it is the same object
        shouldEqual(&tr.get(), &tr_t.get());
    }

    // testing to override uninitialized elements
    void testOverrideUninitializedElement() {
        // create different Element Mo(42)
        ElementImpl::ElementImplKeyType k1 = 42;
        ElementImpl t(k1, "Dp", 2000);
        // store it arbitrary element in flyweight table
        Element tr(t);
        // retrieve element id k1
        Element tr_t(k1);

        // getSymbol results Dp instead of Mo (the standard element)
        shouldEqual(tr_t.get().getSymbol(), "Dp");
    }

    // testing to override initialized elements
    // This does not work! This test shows this...hopefully
    void testOverrideInitializedElement() {
        ElementImpl::ElementImplKeyType k1 = 21;
        Element tr_1(k1);

        ElementImpl t(k1, "Dp", 2000);
        // flyweight checks the id of the element t and recognizes it, since it
        // was retrieved(initialized) earlier
        // as a consequence, the flyweight factory returns the known object
        // instead of overriding it with the given one!
        Element tr_2(t);

        shouldEqual(tr_2.get().getSymbol() != "Dp", true);
    }

};

/** The main function that runs the tests for class Element.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ElementTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

