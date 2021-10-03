
#include "CoffeeMakerEvents.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include <iostream>

#include "Event.hpp"

using namespace CoffeeMaker;

void CoffeeMakerEvents::setUp() {
  // TODO: Implement set up logic...
}

void CoffeeMakerEvents::tearDown() {
  // TODO: Implement tear down logic...
}

void CoffeeMakerEvents::testFunctionCreation() {
  Event onClick;

  Delegate myFn{[&onClick](const Event& event) {
    // TODO: Implement
    std::cout << &onClick << " || " << &event << std::endl;
  }};

  Delegate myFn2{[&onClick](const Event& event) {
    // TODO: Implement
    std::cout << &onClick << " || " << &event << std::endl;
  }};

  CPPUNIT_ASSERT_EQUAL(false, myFn2 == myFn);
}

void CoffeeMakerEvents::testFunctionComparison() {}

void CoffeeMakerEvents::testEmitEvents() {
  Event onClick;
  int callCount = 0;

  Delegate fn{[&onClick, &callCount](const Event& event) {
    // call with the correct event
    std::cout << &onClick << " || " << &event << std::endl;
    callCount++;
    CPPUNIT_ASSERT_EQUAL(true, true);
  }};

  onClick.AddListener(fn);
  onClick.Emit();
  CPPUNIT_ASSERT_EQUAL(1, callCount);
}

void CoffeeMakerEvents::testRemoveEvents() {
  Event onClick;
  int callCount = 0;

  Delegate fn{[&onClick, &callCount](const Event& event) {
    // do nothing...
    std::cout << &onClick << " || " << &event << std::endl;
    callCount++;
  }};

  onClick.AddListener(fn);
  onClick.Emit();
  onClick.RemoveListener(fn);
  onClick.Emit();

  CPPUNIT_ASSERT_EQUAL(1, callCount);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerEvents);
