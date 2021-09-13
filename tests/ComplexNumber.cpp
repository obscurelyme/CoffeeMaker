#include "ComplexNumberTest.hpp"
#include "Complex.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/extensions/HelperMacros.h>

// ComplexNumberTest::ComplexNumberTest(std::string name): CppUnit::TestCase(name) {}

// void ComplexNumberTest::runTest() {
//   CPPUNIT_ASSERT(Complex(10, 1) == Complex(10, 1));
//   CPPUNIT_ASSERT(!(Complex(1, 1) == Complex(2, 2)));
// }

// CppUnit::Test* ComplexNumberTest::suite() {
// 	CppUnit::TestSuite * complexNumberTestSuite = new CppUnit::TestSuite("ComplexNumberTests");

// 	complexNumberTestSuite->addTest(new CppUnit::TestCaller<ComplexNumberTest>("testAddition", &ComplexNumberTest::testAddition));
// 	complexNumberTestSuite->addTest(new CppUnit::TestCaller<ComplexNumberTest>("testEquality", &ComplexNumberTest::testEquality));

// 	return complexNumberTestSuite;
// }

void ComplexNumberTest::setUp() {
  _complex1 = new Complex(10, 1);
	_complex2 = new Complex(1, 1);
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
