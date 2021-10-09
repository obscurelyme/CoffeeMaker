
#ifndef _coffeemaker_cheapasteroidsenemy_hpp
#define _coffeemaker_cheapasteroidsenemy_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "TestBed.hpp"

class CheapAsteroidsEnemy : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(CheapAsteroidsEnemy);
  CPPUNIT_TEST(testEnemySpawnPosition);
  CPPUNIT_TEST_SUITE_END();

  public:
  void setUp();
  void tearDown();

  void testEnemySpawnPosition();

  private:
  CoffeeMaker::Test::TestBed* _testBed;
};

#endif
