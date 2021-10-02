#ifndef _scene_hpp
#define _scene_hpp

#include <string>
#include <vector>

class Scene {
  public:
  Scene();
  ~Scene();

  virtual void Render() = 0;
  virtual void Update() = 0;
  virtual void Init() = 0;
  virtual void Destroy() = 0;

  private:
  std::string _id;

  static int _sceneId;
};

class SceneManager {
  public:
  static void UpdateCurrentScene();
  static void RenderCurrentScene();
  static void LoadScene();
  static void LoadScene(int index);
  static void AddScene(Scene* scene);
  static std::vector<Scene*> scenes;

  private:
  static int _currentSceneIndex;
  static Scene* _currentScene;
};

#endif
