#ifndef _coffeemaker_event_hpp
#define _coffeemaker_event_hpp

#include <functional>
#include <list>
#include <memory>
#include <vector>

namespace CoffeeMaker {
  class Event;

  class Delegate {
    public:
    Delegate(std::function<void(const Event& event)> fn);
    ~Delegate();

    inline void Invoke(const Event& event) { _function(event); }
    inline bool operator==(const Delegate& rhs) { return _id == rhs._id; }

    private:
    std::function<void(const Event& event)> _function;
    int _id;

    static int _uid;
  };

  using EventListener = Delegate;
  using EventListeners = std::vector<EventListener>;
  using EventList = std::list<EventListener>;

  class Event {
    public:
    ~Event();
    void Emit();
    void AddListener(EventListener listener);
    void RemoveListener(EventListener listener);
    void RemoveAllListeners();

    private:
    EventListeners _listeners;
    EventList _list;
  };

}  // namespace CoffeeMaker

#endif
