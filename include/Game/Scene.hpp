#ifndef _scene_hpp
#define _scene_hpp

#include <SDL2/SDL.h>

#include <string>
#include <vector>

#include "Event.hpp"

class SceneManager;

class Scene : public CoffeeMaker::IUserEventListener {
  public:
  Scene();
  virtual ~Scene();

  virtual void Render() = 0;
  virtual void Update(float deltaTime) = 0;
  virtual void Init() = 0;
  virtual void Destroy() = 0;
  virtual void Pause() = 0;
  virtual void Unpause() = 0;
  virtual bool IsLoaded();
  bool IsPaused();

  friend class SceneManager;

  /**
   * @brief Handler function for any SDL_UserEvent
   * pushed into SDL's loop.
   * @param event
   */
  virtual void OnSDLUserEvent(const SDL_UserEvent&){};

  private:
  std::string _id;
  static int _sceneId;

  protected:
  bool _loaded;
  bool _paused;
};

class SceneManager {
  public:
  static void PauseScene();
  static void UnpauseScene();
  static void UpdateCurrentScene(float deltaTime);
  static void RenderCurrentScene();
  static bool LoadScene();
  static bool LoadScene(unsigned long index);
  static void AddScene(Scene* scene);
  static void DestroyAllScenes();
  static void DestroyCurrentScene();
  static bool CurrentScenePaused();
  static bool IsInit();

  static std::vector<Scene*> scenes;

  private:
  static int _currentSceneIndex;
  static Scene* _currentScene;
};

#endif
