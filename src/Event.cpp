#include "Event.hpp"

#include <algorithm>
#include <iostream>

using namespace CoffeeMaker;

int Delegate::_uid = 0;

Delegate::Delegate(std::function<void(const Event& event)> cb) {
  _function = cb;
  _id = ++_uid;
}

Delegate::~Delegate() { _function = nullptr; }

void Event::Emit() {
  auto e = [this](EventListener& listener) {
    // Invoke all listeners
    listener.Invoke(*this);
  };
  std::for_each(_listeners.begin(), _listeners.end(), e);
}

void Event::AddListener(EventListener listener) {
  // insert into the array
  _listeners.emplace_back(listener);
}

void Event::RemoveListener(EventListener listener) {
  for (auto it = _listeners.begin(); it != _listeners.end();) {
    if (listener == *it) {
      it = _listeners.erase(it);
    } else {
      ++it;
    }
  }
}

void Event::RemoveAllListeners() { _listeners.clear(); }
