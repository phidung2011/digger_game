//
//  SceneManager.cpp
//  gamebase
//
//  Created by Phi Dzung on 8/10/15.
//
//
#include "SceneManager.h"


SceneManager* SceneManager::_instance = NULL;

SceneManager* SceneManager::getInstance()
{
    if (!_instance)
    {
        _instance = new SceneManager();
    }
    return _instance;
}
SceneManager::SceneManager()
{
    
}

SceneManager::~SceneManager()
{
    
}

bool SceneManager::insertScene(const SCENE_ID sceneId, SceneDisplay *scene)
{
    if (!_dictionary.at(sceneId))
    {
        _dictionary.insert(sceneId, scene);
        return true;
    }
    return false;
}

