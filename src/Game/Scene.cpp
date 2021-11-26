#include "Game/Scene.hpp"

#include "Event.hpp"
#include "Game/Enemy.hpp"
#include "Game/Player.hpp"
#include "Logger.hpp"

int SceneManager::_currentSceneIndex = -1;
std::vector<Scene*> SceneManager::scenes = {};
Scene* SceneManager::_currentScene = nullptr;

void SceneManager::UpdateCurrentScene(float deltaTime) { _currentScene->Update(deltaTime); }

void SceneManager::PauseScene() {
  _currentScene->Pause();
  _currentScene->_paused = true;
}

void SceneManager::UnpauseScene() {
  _currentScene->Unpause();
  _currentScene->_paused = false;
}

void SceneManager::RenderCurrentScene() { _currentScene->Render(); }

void SceneManager::AddScene(Scene* scene) { scenes.push_back(scene); }

bool SceneManager::LoadScene() {
  // NOTE: Handle first scene case
  if (_currentSceneIndex == -1) {
    _currentScene = scenes[++_currentSceneIndex];
    _currentScene->Init();
    CoffeeMaker::PushCoffeeMakerEvent(CoffeeMaker::ApplicationEvents::COFFEEMAKER_SCENE_LOAD);
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
  return true;
}

bool SceneManager::LoadScene(unsigned long index) {
  if (static_cast<int>(index) < 0 || index >= scenes.size()) {
    // Scene does not exist
    CoffeeMaker::Logger::Critical("Scene does not exist");
    return false;
  }
  if (scenes.size() >= index) {
    if (_currentScene != nullptr && _currentScene->IsLoaded()) {
      _currentScene->Destroy();
    }
    _currentSceneIndex = index;
    _currentScene = scenes[_currentSceneIndex];
    _currentScene->Init();
    CoffeeMaker::PushCoffeeMakerEvent(CoffeeMaker::ApplicationEvents::COFFEEMAKER_SCENE_LOAD);
  }
  return true;
}

bool SceneManager::IsInit() { return _currentSceneIndex != -1; }

void SceneManager::DestroyAllScenes() {
  for (auto scene : scenes) {
    delete scene;
  }
}

void SceneManager::DestroyCurrentScene() { _currentScene->Destroy(); }

bool SceneManager::CurrentScenePaused() { return _currentScene->IsPaused(); }

int Scene::_sceneId = 0;

Scene::Scene() { _id = "Scene-" + std::to_string(++_sceneId); }

Scene::~Scene() {}

bool Scene::IsLoaded() { return _loaded; }

bool Scene::IsPaused() { return _paused; }
