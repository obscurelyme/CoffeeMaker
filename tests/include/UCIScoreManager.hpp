
#ifndef _coffeemaker_uciscoremanager_hpp
#define _coffeemaker_uciscoremanager_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class UCIScoreManager : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(UCIScoreManager);
  CPPUNIT_TEST(testScoreManagerInit);
  CPPUNIT_TEST(testScoreManagerLoadHighScores);
  CPPUNIT_TEST(testScoreManagerCurrentScorePlacementNoPlacement);
  CPPUNIT_TEST(testScoreManagerCurrentScorePlacementThirdPlacement);
  CPPUNIT_TEST(testScoreManagerCurrentScorePlacementSecondPlacement);
  CPPUNIT_TEST(testScoreManagerCurrentScorePlacementFirstPlacement);
  CPPUNIT_TEST(testScoreManagerListensToUserEvent);
  CPPUNIT_TEST(testScoreManagerListensToUserEventWithMultiplier);
  CPPUNIT_TEST_SUITE_END();

  public:
  void setUp();
  void tearDown();

  void testScoreManagerInit();
  void testScoreManagerLoadHighScores();
  void testScoreManagerCurrentScorePlacementNoPlacement();
  void testScoreManagerCurrentScorePlacementThirdPlacement();
  void testScoreManagerCurrentScorePlacementSecondPlacement();
  void testScoreManagerCurrentScorePlacementFirstPlacement();
  void testScoreManagerListensToUserEvent();
  void testScoreManagerListensToUserEventWithMultiplier();
};

#endif
