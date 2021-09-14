#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "ComplexNumberTest.hpp"
#include "Complex.hpp"

void ComplexNumberTest::setUp() {
  _complex1 = new Complex(10, 1);
	_complex2 = new Complex(20, 2);
	_complex3 = new Complex(11, 2);
}

void ComplexNumberTest::tearDown() {
  delete _complex1;
  delete _complex2;
  delete _complex3;
}

void ComplexNumberTest::testEquality() {
	CPPUNIT_ASSERT(*_complex1 == *_complex1);
	CPPUNIT_ASSERT(!(*_complex2 == *_complex1));
}

void ComplexNumberTest::testAddition() {
	CPPUNIT_ASSERT(*_complex1 + *_complex1 == *_complex2);
}

CPPUNIT_TEST_SUITE_REGISTRATION(ComplexNumberTest);
