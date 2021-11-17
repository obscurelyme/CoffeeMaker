
#include "UCIEchelon.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Game/Echelon.hpp"

void UCIEchelon::setUp() {
  // TODO: Implement set up logic...
}

void UCIEchelon::tearDown() {
  // TODO: Implement tear down logic...
}

void UCIEchelon::testCreateEchelon() {
  Echelon e{400.0f, 48.0f, 2.0f, 1.0f, "TEST_ECHELON"};
  CPPUNIT_ASSERT_EQUAL(true, true);
}

void UCIEchelon::testCreateIEchelonItem() {
  using Vec2 = CoffeeMaker::Math::Vector2D;
  Echelon e{400.0f, 48.0f, 2.0f, 1.0f, "TEST_ECHELON"};
  EchelonTester::EchelonImpl impl1{50.0f};
  EchelonTester::EchelonImpl impl2{50.0f};
  EchelonTester::EchelonImpl impl3{50.0f};
  EchelonTester::EchelonImpl impl4{50.0f};
  EchelonTester::EchelonImpl impl5{50.0f};

  e.Add(&impl1);
  impl1.SyncToEchelon();
  e.Add(&impl2);
  impl2.SyncToEchelon();
  e.Add(&impl3);
  impl3.SyncToEchelon();
  e.Add(&impl4);
  impl4.SyncToEchelon();
  e.Add(&impl5);
  impl5.SyncToEchelon();

  e.Update(1.0f);

  Vec2 implPos1 = impl1.GetPosition();
  Vec2 implPos2 = impl2.GetPosition();
  Vec2 implPos3 = impl3.GetPosition();
  Vec2 implPos4 = impl4.GetPosition();
  Vec2 implPos5 = impl5.GetPosition();

  CPPUNIT_ASSERT_EQUAL(implPos1.x, 1.0f);
  CPPUNIT_ASSERT_EQUAL(implPos1.y, 0.0f);

  CPPUNIT_ASSERT_EQUAL(implPos2.x, 53.0f);
  CPPUNIT_ASSERT_EQUAL(implPos2.y, 0.0f);

  CPPUNIT_ASSERT_EQUAL(implPos3.x, 105.0f);
  CPPUNIT_ASSERT_EQUAL(implPos3.y, 0.0f);

  CPPUNIT_ASSERT_EQUAL(implPos4.x, 157.0f);
  CPPUNIT_ASSERT_EQUAL(implPos4.y, 0.0f);

  CPPUNIT_ASSERT_EQUAL(implPos5.x, 209.0f);
  CPPUNIT_ASSERT_EQUAL(implPos5.y, 0.0f);
}

void UCIEchelon::testRemoveIEchelonItem() {
  using Vec2 = CoffeeMaker::Math::Vector2D;
  Echelon e{400.0f, 48.0f, 2.0f, 1.0f, "TEST_ECHELON"};
  EchelonTester::EchelonImpl impl1{50.0f};
  EchelonTester::EchelonImpl impl2{50.0f};
  EchelonTester::EchelonImpl impl3{50.0f};
  EchelonTester::EchelonImpl impl4{50.0f};
  EchelonTester::EchelonImpl impl5{50.0f};

  e.Add(&impl1);
  impl1.SyncToEchelon();
  e.Add(&impl2);
  impl2.SyncToEchelon();
  e.Add(&impl3);
  impl3.SyncToEchelon();
  e.Add(&impl4);
  impl4.SyncToEchelon();
  e.Add(&impl5);
  impl5.SyncToEchelon();

  e.Update(1.0f);
  e.Update(1.0f);

  impl2.RemoveFromEchelon();

  e.Update(1.0f);
  e.Update(1.0f);

  Vec2 implPos1 = impl1.GetPosition();
  Vec2 implPos2 = impl2.GetPosition();
  Vec2 implPos3 = impl3.GetPosition();
  Vec2 implPos4 = impl4.GetPosition();
  Vec2 implPos5 = impl5.GetPosition();

  CPPUNIT_ASSERT_EQUAL(implPos1.x, 4.0f);
  CPPUNIT_ASSERT_EQUAL(implPos1.y, 0.0f);

  CPPUNIT_ASSERT_EQUAL(implPos2.x, 54.0f);
  CPPUNIT_ASSERT_EQUAL(implPos2.y, 0.0f);

  CPPUNIT_ASSERT_EQUAL(implPos3.x, 108.0f);
  CPPUNIT_ASSERT_EQUAL(implPos3.y, 0.0f);

  CPPUNIT_ASSERT_EQUAL(implPos4.x, 160.0f);
  CPPUNIT_ASSERT_EQUAL(implPos4.y, 0.0f);

  CPPUNIT_ASSERT_EQUAL(implPos5.x, 212.0f);
  CPPUNIT_ASSERT_EQUAL(implPos5.y, 0.0f);
}

void UCIEchelon::testDesyncedIEchelonItem() {
  using Vec2 = CoffeeMaker::Math::Vector2D;
  Echelon e{400.0f, 48.0f, 2.0f, 1.0f, "TEST_ECHELON"};
  EchelonTester::EchelonImpl impl1{50.0f};
  EchelonTester::EchelonImpl impl2{50.0f};
  EchelonTester::EchelonImpl impl3{50.0f};
  EchelonTester::EchelonImpl impl4{50.0f};
  EchelonTester::EchelonImpl impl5{50.0f};

  e.Add(&impl1);
  impl1.SyncToEchelon();
  e.Add(&impl2);
  impl2.SyncToEchelon();
  e.Add(&impl3);
  impl3.SyncToEchelon();
  e.Add(&impl4);
  impl4.SyncToEchelon();
  e.Add(&impl5);
  impl5.SyncToEchelon();

  e.Update(1.0f);
  e.Update(1.0f);

  impl2.DesyncFromEchelon();

  e.Update(1.0f);
  e.Update(1.0f);

  Vec2 implPos1 = impl1.GetPosition();
  Vec2 implPos2 = impl2.GetPosition();
  Vec2 implPos3 = impl3.GetPosition();
  Vec2 implPos4 = impl4.GetPosition();
  Vec2 implPos5 = impl5.GetPosition();

  CPPUNIT_ASSERT_EQUAL(implPos1.x, 4.0f);
  CPPUNIT_ASSERT_EQUAL(implPos1.y, 0.0f);

  CPPUNIT_ASSERT_EQUAL(implPos2.x, 54.0f);
  CPPUNIT_ASSERT_EQUAL(implPos2.y, 0.0f);

  CPPUNIT_ASSERT_EQUAL(implPos3.x, 108.0f);
  CPPUNIT_ASSERT_EQUAL(implPos3.y, 0.0f);

  CPPUNIT_ASSERT_EQUAL(implPos4.x, 160.0f);
  CPPUNIT_ASSERT_EQUAL(implPos4.y, 0.0f);

  CPPUNIT_ASSERT_EQUAL(implPos5.x, 212.0f);
  CPPUNIT_ASSERT_EQUAL(implPos5.y, 0.0f);
}

void UCIEchelon::testResyncedIEchelonItem() {
  using Vec2 = CoffeeMaker::Math::Vector2D;
  Echelon e{400.0f, 48.0f, 2.0f, 1.0f, "TEST_ECHELON"};
  EchelonTester::EchelonImpl impl1{50.0f};
  EchelonTester::EchelonImpl impl2{50.0f};
  EchelonTester::EchelonImpl impl3{50.0f};
  EchelonTester::EchelonImpl impl4{50.0f};
  EchelonTester::EchelonImpl impl5{50.0f};

  e.Add(&impl1);
  impl1.SyncToEchelon();
  e.Add(&impl2);
  impl2.SyncToEchelon();
  e.Add(&impl3);
  impl3.SyncToEchelon();
  e.Add(&impl4);
  impl4.SyncToEchelon();
  e.Add(&impl5);
  impl5.SyncToEchelon();

  e.Update(1.0f);
  e.Update(1.0f);

  impl2.DesyncFromEchelon();

  e.Update(1.0f);
  e.Update(1.0f);

  impl2.SyncToEchelon();

  e.Update(1.0f);

  Vec2 implPos1 = impl1.GetPosition();
  Vec2 implPos2 = impl2.GetPosition();
  Vec2 implPos3 = impl3.GetPosition();
  Vec2 implPos4 = impl4.GetPosition();
  Vec2 implPos5 = impl5.GetPosition();

  CPPUNIT_ASSERT_EQUAL(implPos1.x, 5.0f);
  CPPUNIT_ASSERT_EQUAL(implPos1.y, 0.0f);

  CPPUNIT_ASSERT_EQUAL(implPos2.x, 57.0f);
  CPPUNIT_ASSERT_EQUAL(implPos2.y, 0.0f);

  CPPUNIT_ASSERT_EQUAL(implPos3.x, 109.0f);
  CPPUNIT_ASSERT_EQUAL(implPos3.y, 0.0f);

  CPPUNIT_ASSERT_EQUAL(implPos4.x, 161.0f);
  CPPUNIT_ASSERT_EQUAL(implPos4.y, 0.0f);

  CPPUNIT_ASSERT_EQUAL(implPos5.x, 213.0f);
  CPPUNIT_ASSERT_EQUAL(implPos5.y, 0.0f);
}

CPPUNIT_TEST_SUITE_REGISTRATION(UCIEchelon);
