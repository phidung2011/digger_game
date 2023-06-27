//
//  SceneManager.h
//  gamebase
//
//  Created by Phi Dzung on 8/10/15.
//
//

#ifndef __gamebase__SceneManager__
#define __gamebase__SceneManager__

#include "SceneDisplay.h"
class SceneManager
{
public:
    SceneManager();
    ~SceneManager();
    
    static SceneManager* getInstance();
    
    cocos2d::Map<int, SceneDisplay*>& getDictionary(){return _dictionary;};
    
    SceneDisplay* getRunningScene(){return _runningScene;};
    
    bool insertScene(const SCENE_ID sceneId, SceneDisplay* scene);
    
private:
    static SceneManager* _instance;
    cocos2d::Map<int, SceneDisplay*> _dictionary;
    
    SceneDisplay* _runningScene;
    
};

#endif /* defined(__gamebase__SceneManager__) */
