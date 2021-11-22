
#include "CoffeeMakerUserEvents.hpp"

#include <SDL2/SDL.h>
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Utilities.hpp"

void CoffeeMakerUserEvents::setUp() {
  // TODO: Implement set up logic...
}

void CoffeeMakerUserEvents::tearDown() {
  // TODO: Implement tear down logic...
}

void CoffeeMakerUserEvents::testUserEventsListenedTo() {
  Scope<CoffeeMakerUserEventImpl> listener = CreateScope<CoffeeMakerUserEventImpl>();
  unsigned int called = 0;
  unsigned int expectedCalls = 1;
  listener->onSDLUserEventSpy = [&called] { called++; };
  SDL_UserEvent userEvent{
      .type = SDL_USEREVENT,
      .code = 123,
      .timestamp = 123456,
      .windowID = 1,
      .data1 = nullptr,
      .data2 = nullptr,
  };
  CoffeeMaker::UserEventHandler::HandleUserEvent(userEvent);

  CPPUNIT_ASSERT_EQUAL(expectedCalls, called);
}

void CoffeeMakerUserEvents::testUserEventsDeletedSelf() {
  CoffeeMakerUserEventImpl* listener = new CoffeeMakerUserEventImpl();
  size_t expectedListeners = 2;
  size_t expectedListenersPostCall = 0;

  CPPUNIT_ASSERT_EQUAL(expectedListeners, listener->NumListeners());

  listener->onSDLUserEventSpy = [&listener] {
    delete listener;
    listener = nullptr;
  };
  SDL_UserEvent userEvent{
      .type = SDL_USEREVENT,
      .code = 123,
      .timestamp = 123456,
      .windowID = 1,
      .data1 = nullptr,
      .data2 = nullptr,
  };

  CPPUNIT_ASSERT_NO_THROW(CoffeeMaker::UserEventHandler::HandleUserEvent(userEvent));
  CPPUNIT_ASSERT_EQUAL(expectedListenersPostCall, CoffeeMaker::IUserEventListener::NumListeners());
}

void CoffeeMakerUserEvents::testUserEventsCreatedMoreListeners() {
  Scope<CoffeeMakerUserEventImpl> listener1 = CreateScope<CoffeeMakerUserEventImpl>();
  Scope<CoffeeMakerUserEventImpl> listener2;
  Scope<CoffeeMakerUserEventImpl> listener3;
  size_t expectedListenersPostCall = 3;
  unsigned int listener2And3ExpectedHandledTimes = 0;
  unsigned int listener1ExpectedHandledTimes = 1;
  bool passOne = true;
  listener1->onSDLUserEventSpy = [&listener2, &listener3, &passOne] {
    if (passOne) {
      listener2 = CreateScope<CoffeeMakerUserEventImpl>();
      listener3 = CreateScope<CoffeeMakerUserEventImpl>();
      passOne = false;
    }
  };
  SDL_UserEvent userEvent{
      .type = SDL_USEREVENT,
      .code = 123,
      .timestamp = 123456,
      .windowID = 1,
      .data1 = nullptr,
      .data2 = nullptr,
  };

  CPPUNIT_ASSERT_NO_THROW(CoffeeMaker::UserEventHandler::HandleUserEvent(userEvent));

  CPPUNIT_ASSERT_EQUAL(expectedListenersPostCall, CoffeeMaker::IUserEventListener::NumListeners());
  CPPUNIT_ASSERT_EQUAL(listener1ExpectedHandledTimes, listener1->NumTimesEventHandled());
  CPPUNIT_ASSERT_EQUAL(listener2And3ExpectedHandledTimes, listener2->NumTimesEventHandled());
  CPPUNIT_ASSERT_EQUAL(listener2And3ExpectedHandledTimes, listener3->NumTimesEventHandled());

  CPPUNIT_ASSERT_NO_THROW(CoffeeMaker::UserEventHandler::HandleUserEvent(userEvent));

  CPPUNIT_ASSERT_EQUAL(listener1ExpectedHandledTimes + 1, listener1->NumTimesEventHandled());
  CPPUNIT_ASSERT_EQUAL(listener2And3ExpectedHandledTimes + 1, listener2->NumTimesEventHandled());
  CPPUNIT_ASSERT_EQUAL(listener2And3ExpectedHandledTimes + 1, listener3->NumTimesEventHandled());
}

void CoffeeMakerUserEvents::testUserEventsDeletedSubsequentListeners() {
  Scope<CoffeeMakerUserEventImpl> listener1 = CreateScope<CoffeeMakerUserEventImpl>();
  Scope<CoffeeMakerUserEventImpl> listener2 = CreateScope<CoffeeMakerUserEventImpl>();
  Scope<CoffeeMakerUserEventImpl> listener3 = CreateScope<CoffeeMakerUserEventImpl>();
  size_t expectedListenersPostCall = 0;
  unsigned int listener2And3ExpectedHandledTimes = 0;
  unsigned int listener1ExpectedHandledTimes = 1;
  unsigned int listener1ActualHandledTimes = 0;
  unsigned int listener2ActualHandledTimes = 0;
  unsigned int listener3ActualHandledTimes = 0;
  listener1->onSDLUserEventSpy = [&listener1, &listener2, &listener3, &listener1ActualHandledTimes] {
    listener1.reset();
    listener2.reset();
    listener3.reset();
    listener1ActualHandledTimes++;
  };
  listener2->onSDLUserEventSpy = [&listener2ActualHandledTimes] { listener2ActualHandledTimes++; };
  listener3->onSDLUserEventSpy = [&listener3ActualHandledTimes] { listener3ActualHandledTimes++; };

  SDL_UserEvent userEvent{
      .type = SDL_USEREVENT,
      .code = 123,
      .timestamp = 123456,
      .windowID = 1,
      .data1 = nullptr,
      .data2 = nullptr,
  };

  CPPUNIT_ASSERT_NO_THROW(CoffeeMaker::UserEventHandler::HandleUserEvent(userEvent));

  CPPUNIT_ASSERT_EQUAL(expectedListenersPostCall, CoffeeMaker::IUserEventListener::NumListeners());
  CPPUNIT_ASSERT_EQUAL(listener1ExpectedHandledTimes, listener1ActualHandledTimes);
  CPPUNIT_ASSERT_EQUAL(listener2And3ExpectedHandledTimes, listener2ActualHandledTimes);
  CPPUNIT_ASSERT_EQUAL(listener2And3ExpectedHandledTimes, listener3ActualHandledTimes);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerUserEvents);
