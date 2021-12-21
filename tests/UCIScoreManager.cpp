#include "UCIScoreManager.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include <filesystem>
#include <thread>

#include "Coroutine.hpp"
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
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ScoreManager::Destroy();
}

void UCIScoreManager::testScoreManagerWriteHighScores() {
  using Co = CoffeeMaker::Coroutine;
  unsigned int expectedFirstScore = 500;
  unsigned int expectedSecondScore = 200;
  unsigned int expectedThirdScore = 100;

  auto c = []() -> Co {
    std::cout << "Writing test scores..." << std::endl;
    co_await CoffeeMaker::WriteFileAwaiter{"scores.txt", "500|200|100"};
    std::cout << "Test scores written!" << std::endl;
  };

  c();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ScoreManager::Init();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ScoreManager::LoadHighScores();
  CPPUNIT_ASSERT_EQUAL(expectedFirstScore, ScoreManager::GetHighScores().firstPlace);
  CPPUNIT_ASSERT_EQUAL(expectedSecondScore, ScoreManager::GetHighScores().secondPlace);
  CPPUNIT_ASSERT_EQUAL(expectedThirdScore, ScoreManager::GetHighScores().thirdPlace);
  ScoreManager::Destroy();
  std::filesystem::remove("scores.txt");
}

void UCIScoreManager::testScoreManagerLoadHighScores() {
  ScoreManager::Init();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ScoreManager::IncrementScore(500);
  unsigned int expectedScore = 500;
  unsigned int actualScore = ScoreManager::GetScore();

  CPPUNIT_ASSERT_EQUAL(expectedScore, actualScore);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ScoreManager::Destroy();
}

void UCIScoreManager::testScoreManagerCurrentScorePlacementNoPlacement() {
  auto c = []() -> CoffeeMaker::Coroutine {
    std::cout << "Writing test scores..." << std::endl;
    co_await CoffeeMaker::WriteFileAwaiter{"scores.txt", "5000|2500|1000"};
    std::cout << "Test scores written!" << std::endl;
  };

  c();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ScoreManager::Init();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ScoreManager::LoadHighScores();
  ScoreManager::IncrementScore(999);
  int expectedPlacement = -1;
  int actualPlacement = ScoreManager::CurrentScorePlacement();

  CPPUNIT_ASSERT_EQUAL(expectedPlacement, actualPlacement);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ScoreManager::Destroy();
  std::filesystem::remove("scores.txt");
}

void UCIScoreManager::testScoreManagerCurrentScorePlacementThirdPlacement() {
  auto c = []() -> CoffeeMaker::Coroutine {
    std::cout << "Writing test scores..." << std::endl;
    co_await CoffeeMaker::WriteFileAwaiter{"scores.txt", "5000|2500|1000"};
    std::cout << "Test scores written!" << std::endl;
  };

  c();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ScoreManager::Init();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ScoreManager::LoadHighScores();
  ScoreManager::IncrementScore(1001);
  int expectedPlacement = 3;
  int actualPlacement = ScoreManager::CurrentScorePlacement();

  CPPUNIT_ASSERT_EQUAL(expectedPlacement, actualPlacement);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ScoreManager::Destroy();
  std::filesystem::remove("scores.txt");
}

void UCIScoreManager::testScoreManagerCurrentScorePlacementSecondPlacement() {
  auto c = []() -> CoffeeMaker::Coroutine {
    std::cout << "Writing test scores..." << std::endl;
    co_await CoffeeMaker::WriteFileAwaiter{"scores.txt", "5000|2500|1000"};
    std::cout << "Test scores written!" << std::endl;
  };

  c();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  ScoreManager::Init();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ScoreManager::LoadHighScores();
  ScoreManager::IncrementScore(2501);
  int expectedPlacement = 2;
  int actualPlacement = ScoreManager::CurrentScorePlacement();

  CPPUNIT_ASSERT_EQUAL(expectedPlacement, actualPlacement);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ScoreManager::Destroy();
  std::filesystem::remove("scores.txt");
}

void UCIScoreManager::testScoreManagerCurrentScorePlacementFirstPlacement() {
  auto c = []() -> CoffeeMaker::Coroutine {
    std::cout << "Writing test scores..." << std::endl;
    co_await CoffeeMaker::WriteFileAwaiter{"scores.txt", "5000|2500|1000"};
    std::cout << "Test scores written!" << std::endl;
  };

  c();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ScoreManager::Init();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ScoreManager::LoadHighScores();
  ScoreManager::IncrementScore(5001);
  int expectedPlacement = 1;
  int actualPlacement = ScoreManager::CurrentScorePlacement();

  CPPUNIT_ASSERT_EQUAL(expectedPlacement, actualPlacement);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ScoreManager::Destroy();
  std::filesystem::remove("scores.txt");
}

void UCIScoreManager::testScoreManagerListensToUserEvent() {
  ScoreManager::Init();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
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
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ScoreManager::Destroy();
}

void UCIScoreManager::testScoreManagerListensToUserEventWithMultiplier() {
  ScoreManager::Init();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ScoreManager::LoadHighScores();
  int expectedScore = 30;

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
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ScoreManager::Destroy();
}

CPPUNIT_TEST_SUITE_REGISTRATION(UCIScoreManager);
