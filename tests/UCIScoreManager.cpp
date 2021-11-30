#include "UCIScoreManager.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Game/Events.hpp"
#include "Game/ScoreManager.hpp"

void UCIScoreManager::setUp() {
  // TODO: Implement set up logic...
}

void UCIScoreManager::tearDown() {
  // TODO: Implement tear down logic...
}

void UCIScoreManager::testScoreManagerInit() {
  ScoreManager::Init();
  ScoreManager::Destroy();
}

void UCIScoreManager::testScoreManagerLoadHighScores() {
  ScoreManager::Init();
  ScoreManager::IncrementScore(500);
  unsigned int expectedScore = 500;
  unsigned int actualScore = ScoreManager::GetScore();

  CPPUNIT_ASSERT_EQUAL(expectedScore, actualScore);
  ScoreManager::Destroy();
}

void UCIScoreManager::testScoreManagerCurrentScorePlacementNoPlacement() {
  ScoreManager::Init();
  ScoreManager::LoadHighScores();
  ScoreManager::IncrementScore(999);
  int expectedPlacement = -1;
  int actualPlacement = ScoreManager::CurrentScorePlacement();

  CPPUNIT_ASSERT_EQUAL(expectedPlacement, actualPlacement);
  ScoreManager::Destroy();
}

void UCIScoreManager::testScoreManagerCurrentScorePlacementThirdPlacement() {
  ScoreManager::Init();
  ScoreManager::LoadHighScores();
  ScoreManager::IncrementScore(1001);
  int expectedPlacement = 3;
  int actualPlacement = ScoreManager::CurrentScorePlacement();

  CPPUNIT_ASSERT_EQUAL(expectedPlacement, actualPlacement);
  ScoreManager::Destroy();
}

void UCIScoreManager::testScoreManagerCurrentScorePlacementSecondPlacement() {
  ScoreManager::Init();
  ScoreManager::LoadHighScores();
  ScoreManager::IncrementScore(2501);
  int expectedPlacement = 2;
  int actualPlacement = ScoreManager::CurrentScorePlacement();

  CPPUNIT_ASSERT_EQUAL(expectedPlacement, actualPlacement);
  ScoreManager::Destroy();
}

void UCIScoreManager::testScoreManagerCurrentScorePlacementFirstPlacement() {
  ScoreManager::Init();
  ScoreManager::LoadHighScores();
  ScoreManager::IncrementScore(5001);
  int expectedPlacement = 1;
  int actualPlacement = ScoreManager::CurrentScorePlacement();

  CPPUNIT_ASSERT_EQUAL(expectedPlacement, actualPlacement);
  ScoreManager::Destroy();
}

void UCIScoreManager::testScoreManagerListensToUserEvent() {
  ScoreManager::Init();
  ScoreManager::LoadHighScores();
  int expectedScore = 10;

  SDL_UserEvent userEvent{
      .type = UCI::Events::PLAYER_INCREMENT_SCORE,
      .timestamp = 123456,
      .windowID = 1,
      .code = -1,
      .data1 = nullptr,
      .data2 = nullptr,
  };

  CoffeeMaker::UserEventHandler::HandleUserEvent(userEvent);

  int actualScore = ScoreManager::GetScore();

  CPPUNIT_ASSERT_EQUAL(expectedScore, actualScore);
  ScoreManager::Destroy();
}

void UCIScoreManager::testScoreManagerListensToUserEventWithMultiplier() {
  ScoreManager::Init();
  ScoreManager::LoadHighScores();
  int expectedScore = 20;

  SDL_UserEvent userEvent{
      .type = UCI::Events::PLAYER_INCREMENT_SCORE,
      .timestamp = 123456,
      .windowID = 1,
      .code = ScoreManager::Multiplier::Super,
      .data1 = nullptr,
      .data2 = nullptr,
  };

  CoffeeMaker::UserEventHandler::HandleUserEvent(userEvent);

  int actualScore = ScoreManager::GetScore();

  CPPUNIT_ASSERT_EQUAL(expectedScore, actualScore);
  ScoreManager::Destroy();
}

CPPUNIT_TEST_SUITE_REGISTRATION(UCIScoreManager);
