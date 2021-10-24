```cpp

void(*globalCallback)(void*) = [](void* data2) {
  std::cout << "Called here..." << std::end;
  // work with data2 back on the main thread
};

/**
 * Ideally this comes from SDL_RegisterEvents, so
 * this is a contrived example.
 */
Uint32 MY_EVENT = 1245;

Uint32 CallbackOnFixedInterval(Uint32 interval, void*) {
  SDL_Event event;
  SDL_UserEvent userEvent;
  SomeData* data = nullptr;

  userEvent.type = SDL_USEREVENT;
  userEvent.code = MY_EVENT;      // a way to uniquely identify this event

  // load data and assign pointer here.
  loadData(data);

  // unsafe cast to from function pointer to void pointer
  // because userEvent.data1 wants a void pointer.
  userEvent.data1 = reinterpret_cast<void*>(globalCallback);
  userEvent.data2 = static_cast<void*>(data);

  event.type = SDL_USEREVENT;
  event.user = userEvent;

  // Push event into SDL's queue
  SDL_PushEvent(&event);

  return interval;
}



// In the core game loop
...
while (!quit) {
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_USEREVENT) {
      if (event.code == MY_EVENT) {
        // Here is where things get wonky...
         void (*p)(void*) = reinterpret_cast<void (*)(void*)>(event.user.data1);
          p(event.user.data2);  // Invoke globalCallback with that SDL_Surface pointer
      }
    }
  }
}
...

```
