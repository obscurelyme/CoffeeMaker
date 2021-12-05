
#include "CoffeeMakerDateTime.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

void CoffeeMakerDateTime::setUp() {
  // TODO: Implement set up logic...
}

void CoffeeMakerDateTime::tearDown() {
  // TODO: Implement tear down logic...
}

void CoffeeMakerDateTime::testDateTimeFormatTemplate() {
  auto now = CoffeeMaker::DateTime::Now();
  auto nowMs = CoffeeMaker::DateTime::ToMilliseconds(now);
  std::string formattedDateTime = CoffeeMaker::DateTime::Format("{:%H:%M:%S}", now);
  std::string expectedString = CoffeeMaker::DateTime::Format("{:%H:%M:%S}", nowMs);

  CPPUNIT_ASSERT_EQUAL(expectedString, formattedDateTime);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerDateTime);
