#include "Game/Scene.hpp"

#include "Event.hpp"
#include "Game/Enemy.hpp"
#include "Game/Player.hpp"

int SceneManager::_currentSceneIndex = -1;
std::vector<Scene*> SceneManager::scenes = {};
Scene* SceneManager::_currentScene = nullptr;

void SceneManager::UpdateCurrentScene(float deltaTime) { _currentScene->Update(deltaTime); }

void SceneManager::PauseScene() { _currentScene->Pause(); }

void SceneManager::UnpauseScene() { _currentScene->Unpause(); }

void SceneManager::RenderCurrentScene() { _currentScene->Render(); }

void SceneManager::AddScene(Scene* scene) { scenes.push_back(scene); }

void SceneManager::LoadScene() {
  // NOTE: Handle first scene case
  if (_currentSceneIndex == -1) {
    _currentScene = scenes[++_currentSceneIndex];
    _currentScene->Init();
    CoffeeMaker::PushCoffeeMakerEvent(CoffeeMaker::ApplicationEvents::COFFEEMAKER_SCENE_LOAD);
    return;
  }
  // NOTE: If not the first scene, clean up and then move to next scene
  _currentScene->Destroy();
  if (_currentSceneIndex + 1 < (int)scenes.size()) {
    _currentScene = scenes[++_currentSceneIndex];
  } else {
    // NOTE: wrap scenes for now...
    _currentSceneIndex = 0;
    _currentScene = scenes[_currentSceneIndex];
  }
  _currentScene->Init();
  CoffeeMaker::PushCoffeeMakerEvent(CoffeeMaker::ApplicationEvents::COFFEEMAKER_SCENE_LOAD);
}

void SceneManager::LoadScene(unsigned long index) {
  if (scenes.size() >= index) {
    if (_currentScene != nullptr && _currentScene->IsLoaded()) {
      _currentScene->Destroy();
    }
    _currentSceneIndex = index;
    _currentScene = scenes[_currentSceneIndex];
    _currentScene->Init();
    CoffeeMaker::PushCoffeeMakerEvent(CoffeeMaker::ApplicationEvents::COFFEEMAKER_SCENE_LOAD);
  }
}

void SceneManager::DestroyAllScenes() {
  for (auto scene : scenes) {
    delete scene;
  }
}

int Scene::_sceneId = 0;

Scene::Scene() { _id = "Scene-" + std::to_string(++_sceneId); }

Scene::~Scene() {}

bool Scene::IsLoaded() { return _loaded; }
