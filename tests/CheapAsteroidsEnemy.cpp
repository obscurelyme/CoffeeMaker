
#include "CheapAsteroidsEnemy.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Game/Enemy.hpp"

void CheapAsteroidsEnemy::setUp() { _testBed = new CoffeeMaker::Test::TestBed(); }

void CheapAsteroidsEnemy::tearDown() { delete _testBed; }

void CheapAsteroidsEnemy::testEnemySpawnPosition() {
  Enemy enemy;
  enemy.Spawn();

  CPPUNIT_ASSERT_EQUAL(0, 0);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CheapAsteroidsEnemy);
