
#ifndef _coffeemaker_coffeemakeruserevents_hpp
#define _coffeemaker_coffeemakeruserevents_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <functional>

#include "Events/UserEvents.hpp"

class CoffeeMakerUserEventImpl : public CoffeeMaker::IUserEventListener {
  public:
  CoffeeMakerUserEventImpl() : onSDLUserEventSpy(nullptr), _numTimesUserEventHandled(0){};
  virtual ~CoffeeMakerUserEventImpl() { onSDLUserEventSpy = nullptr; }
  void OnSDLUserEvent(const SDL_UserEvent&) {
    if (onSDLUserEventSpy != nullptr) {
      onSDLUserEventSpy();
    }
    _numTimesUserEventHandled++;
  }

  unsigned int NumTimesEventHandled() const { return _numTimesUserEventHandled; }

  std::function<void(void)> onSDLUserEventSpy;

  private:
  unsigned int _numTimesUserEventHandled;
};

class CoffeeMakerUserEventSpy {
  public:
  CoffeeMakerUserEventSpy() {}
  ~CoffeeMakerUserEventSpy() {}
};

class CoffeeMakerUserEvents : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(CoffeeMakerUserEvents);
  CPPUNIT_TEST(testUserEventsListenedTo);
  CPPUNIT_TEST(testUserEventsDeletedSelf);
  CPPUNIT_TEST(testUserEventsCreatedMoreListeners);
  CPPUNIT_TEST(testUserEventsDeletedSubsequentListeners);
  CPPUNIT_TEST_SUITE_END();

  public:
  void setUp();
  void tearDown();
  void testUserEventsListenedTo();
  void testUserEventsDeletedSelf();
  void testUserEventsCreatedMoreListeners();
  void testUserEventsDeletedSubsequentListeners();
};

#endif
