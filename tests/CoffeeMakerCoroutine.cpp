
#include "CoffeeMakerCoroutine.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include <filesystem>

#include "Coroutine.hpp"

void CoffeeMakerCoroutine::setUp() {
  // TODO: Implement set up logic...
}

void CoffeeMakerCoroutine::tearDown() {
  // TODO: Implement tear down logic...
}

void CoffeeMakerCoroutine::testCoroutineCreation() {
  using Co = CoffeeMaker::Coroutine;
  int x = 0;

  Co c = [&]() -> Co {
    x++;
    co_await CoffeeMaker::Suspend{};
    x++;
    std::cout << "returning...\n";
    co_return;
  }();

  c.Resume();

  CPPUNIT_ASSERT_EQUAL(2, x);
  std::cout << "test done...\n";
}

void CoffeeMakerCoroutine::testCoroutineAwaiter() {
  using Co = CoffeeMaker::Coroutine;

  auto c = []() -> Co {
    std::cout << "before awaiter" << std::endl;
    co_await CoffeeMaker::TimeoutAwaiter{1000};
    std::cout << "after awaiter" << std::endl;
  };

  Co myCoro = c();
  std::cout << "Return to caller\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  std::cout << "Test complete\n";
}

void CoffeeMakerCoroutine::testCoroutineReadFileAwaiter() {
  using Co = CoffeeMaker::Coroutine;
  std::string result;
  std::string expectedString = "Hello, World!";

  auto c = [&result, &expectedString]() -> Co {
    std::cout << "before awaiter" << std::endl;
    co_await CoffeeMaker::WriteFileAwaiter{"testfile.txt", expectedString};
    std::string text = co_await CoffeeMaker::ReadFileAwaiter{"testfile.txt"};
    std::cout << "after awaiter: " << text << std::endl;
    result = text;
  };

  Co myCoro = c();
  std::cout << "Return to caller\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::cout << "Test complete\n";
  std::filesystem::remove("testfile.txt");

  CPPUNIT_ASSERT_EQUAL(expectedString, result);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerCoroutine);
