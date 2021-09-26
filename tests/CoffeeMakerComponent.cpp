
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "CoffeeMakerComponent.hpp"


template<typename T>
T doAThing(T arg) {
  return arg;
}

void CoffeeMakerComponent::setUp() {
  // TODO: Implement set up logic...
}

void CoffeeMakerComponent::tearDown() {
  // TODO: Implement tear down logic...
}

void CoffeeMakerComponent::testComponentCreation() {

}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerComponent);

