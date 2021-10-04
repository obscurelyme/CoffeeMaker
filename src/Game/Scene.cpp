#include "Game/Scene.hpp"

#include "Game/Enemy.hpp"
#include "Game/Player.hpp"

int SceneManager::_currentSceneIndex = -1;
std::vector<Scene*> SceneManager::scenes = {};
Scene* SceneManager::_currentScene = nullptr;

void SceneManager::UpdateCurrentScene() { _currentScene->Update(); }

void SceneManager::RenderCurrentScene() { _currentScene->Render(); }

void SceneManager::AddScene(Scene* scene) { scenes.push_back(scene); }

void SceneManager::LoadScene() {
  // NOTE: Handle first scene case
  if (_currentSceneIndex == -1) {
    _currentScene = scenes[++_currentSceneIndex];
    _currentScene->Init();
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
}

void SceneManager::LoadScene(unsigned long index) {
  if (scenes.size() >= index && index >= 0) {
    _currentScene->Destroy();
    _currentSceneIndex = index;
    _currentScene = scenes[_currentSceneIndex];
    _currentScene->Init();
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
