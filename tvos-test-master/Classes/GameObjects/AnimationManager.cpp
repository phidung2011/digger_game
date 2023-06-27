//
//  AnimationManager.cpp
//  gamebase
//
//  Created by Phi Dzung on 7/2/15.
//
//

#include "AnimationManager.h"
#include "AvatarConfig.h"
USING_NS_CC;

AnimationManager* AnimationManager::_instance = NULL;

AnimationManager* AnimationManager::getInstance()
{
    if (!_instance)
    {
        _instance = new AnimationManager();
    }
    return _instance;
}
AnimationManager::AnimationManager()
{
    this->loadAnimationDataFromFile(AnimationKey::PLAYER_KEY);
    this->loadAnimationDataFromFile(AnimationKey::HAMMER_KEY);
    this->loadAnimationDataFromFile(AnimationKey::SHIPPER_KEY);
    this->loadAnimationDataFromFile(AnimationKey::TANKER_KEY);
    this->loadAnimationDataFromFile(AnimationKey::TRACKER_KEY);
    this->loadAnimationDataFromFile(AnimationKey::ROLLER_KEY);
    
    this->loadAnimationDataFromFile(AnimationKey::BOMB_DROP_KEY);
    this->loadAnimationDataFromFile(AnimationKey::BOMB_FIRE_KEY);
    this->loadAnimationDataFromFile(AnimationKey::BOMB_SPIKE_KEY);
    this->loadAnimationDataFromFile(AnimationKey::BOMB_TIME_KEY);
    
    this->loadAnimationDataFromFile(AnimationKey::BOOM_BOMB_KEY);
    this->loadAnimationDataFromFile(AnimationKey::BOOM_CHARACTER_KEY);
    this->loadAnimationDataFromFile(AnimationKey::BOOM_MINE_KEY);
    this->loadAnimationDataFromFile(AnimationKey::BOOM_TIME_BOMB_KEY);
    
    this->loadAnimationDataFromFile(AnimationKey::DIAMOND1_KEY);
    this->loadAnimationDataFromFile(AnimationKey::DIAMOND2_KEY);
    this->loadAnimationDataFromFile(AnimationKey::DIAMOND3_KEY);
    
    this->loadAnimationDataFromFile(AnimationKey::STONE_KEY);
    this->loadAnimationDataFromFile(AnimationKey::BOX_GOLD_KEY);
    this->loadAnimationDataFromFile(AnimationKey::BOX_BOMB_DROP_KEY);
    this->loadAnimationDataFromFile(AnimationKey::BOX_BOMB_FIRE_KEY);
    this->loadAnimationDataFromFile(AnimationKey::BOX_BOMB_SPIKE_KEY);
    this->loadAnimationDataFromFile(AnimationKey::BOX_BOMB_TIME_KEY);
    this->loadAnimationDataFromFile(AnimationKey::GOLD_KEY);
    this->loadAnimationDataFromFile(AnimationKey::SNOW_FLAKE_KEY);
    this->loadAnimationDataFromFile(AnimationKey::FUEL_KEY);
    this->loadAnimationDataFromFile(AnimationKey::NEXT_STAGE_DOOR_KEY);
    this->loadAnimationDataFromFile(AnimationKey::HP_UP_KEY);
    
    this->loadAnimationDataFromFile(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 1));
    this->loadAnimationDataFromFile(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 2));
    this->loadAnimationDataFromFile(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 3));
    this->loadAnimationDataFromFile(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 4));
    this->loadAnimationDataFromFile(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 5));
    
    _animationData.at(AnimationKey::PLAYER_KEY).at(0)->setAnimSpeed(6);
    _animationData.at(AnimationKey::PLAYER_KEY).at(1)->setAnimSpeed(5);
    
    _animationData.at(AnimationKey::ROLLER_KEY).at(0)->setAnimSpeed(2);
    _animationData.at(AnimationKey::SHIPPER_KEY).at(0)->setAnimSpeed(1);
    _animationData.at(AnimationKey::TANKER_KEY).at(0)->setAnimSpeed(3);
    _animationData.at(AnimationKey::TRACKER_KEY).at(0)->setAnimSpeed(4);
    _animationData.at(AnimationKey::HAMMER_KEY).at(0)->setAnimSpeed(3);
    
    _animationData.at(AnimationKey::BOMB_DROP_KEY).at(0)->setAnimSpeed(5);
    _animationData.at(AnimationKey::BOMB_FIRE_KEY).at(0)->setAnimSpeed(5);
    _animationData.at(AnimationKey::BOMB_SPIKE_KEY).at(0)->setAnimSpeed(INT_MAX);
    _animationData.at(AnimationKey::BOMB_TIME_KEY).at(0)->setAnimSpeed(15);
    _animationData.at(AnimationKey::BOMB_TIME_KEY).at(0)->setRepeatTime(1);
    
    _animationData.at(AnimationKey::BOOM_BOMB_KEY).at(0)->setAnimSpeed(5);
    _animationData.at(AnimationKey::BOOM_BOMB_KEY).at(0)->setRepeatTime(1);
    
    _animationData.at(AnimationKey::BOOM_CHARACTER_KEY).at(0)->setAnimSpeed(5);
    _animationData.at(AnimationKey::BOOM_CHARACTER_KEY).at(0)->setRepeatTime(1);
    
    _animationData.at(AnimationKey::BOOM_MINE_KEY).at(0)->setAnimSpeed(5);
    _animationData.at(AnimationKey::BOOM_MINE_KEY).at(0)->setRepeatTime(1);
    
    _animationData.at(AnimationKey::BOOM_TIME_BOMB_KEY).at(0)->setAnimSpeed(5);
    _animationData.at(AnimationKey::BOOM_TIME_BOMB_KEY).at(0)->setRepeatTime(1);
    
    _animationData.at(AnimationKey::DIAMOND1_KEY).at(0)->setAnimSpeed(7);
    _animationData.at(AnimationKey::DIAMOND2_KEY).at(0)->setAnimSpeed(7);
    _animationData.at(AnimationKey::DIAMOND3_KEY).at(0)->setAnimSpeed(7);
    _animationData.at(AnimationKey::DIAMOND1_KEY).at(1)->setAnimSpeed(7);
    _animationData.at(AnimationKey::DIAMOND1_KEY).at(1)->setRepeatTime(1);
    _animationData.at(AnimationKey::DIAMOND2_KEY).at(1)->setAnimSpeed(7);
    _animationData.at(AnimationKey::DIAMOND2_KEY).at(1)->setRepeatTime(1);
    _animationData.at(AnimationKey::DIAMOND3_KEY).at(1)->setAnimSpeed(7);
    _animationData.at(AnimationKey::DIAMOND3_KEY).at(1)->setRepeatTime(1);
    
    _animationData.at(AnimationKey::STONE_KEY).at(0)->setAnimSpeed(INT_MAX);
    
    _animationData.at(AnimationKey::BOX_GOLD_KEY).at(0)->setAnimSpeed(7);
    _animationData.at(AnimationKey::BOX_GOLD_KEY).at(1)->setAnimSpeed(7);
    _animationData.at(AnimationKey::BOX_GOLD_KEY).at(1)->setRepeatTime(1);
    
    _animationData.at(AnimationKey::BOX_BOMB_DROP_KEY).at(0)->setAnimSpeed(INT_MAX);
    _animationData.at(AnimationKey::BOX_BOMB_DROP_KEY).at(1)->setAnimSpeed(7);
    _animationData.at(AnimationKey::BOX_BOMB_DROP_KEY).at(1)->setRepeatTime(1);
    
    
    _animationData.at(AnimationKey::BOX_BOMB_FIRE_KEY).at(0)->setAnimSpeed(INT_MAX);
    _animationData.at(AnimationKey::BOX_BOMB_FIRE_KEY).at(1)->setAnimSpeed(7);
    _animationData.at(AnimationKey::BOX_BOMB_FIRE_KEY).at(1)->setRepeatTime(1);
    
    
    _animationData.at(AnimationKey::BOX_BOMB_SPIKE_KEY).at(0)->setAnimSpeed(INT_MAX);
    _animationData.at(AnimationKey::BOX_BOMB_SPIKE_KEY).at(1)->setAnimSpeed(7);
    _animationData.at(AnimationKey::BOX_BOMB_SPIKE_KEY).at(1)->setRepeatTime(1);
    
    
    _animationData.at(AnimationKey::BOX_BOMB_TIME_KEY).at(0)->setAnimSpeed(INT_MAX);
    _animationData.at(AnimationKey::BOX_BOMB_TIME_KEY).at(1)->setAnimSpeed(7);
    _animationData.at(AnimationKey::BOX_BOMB_TIME_KEY).at(1)->setRepeatTime(1);
    
    _animationData.at(AnimationKey::HP_UP_KEY).at(0)->setAnimSpeed(7);
    
    
    _animationData.at(AnimationKey::GOLD_KEY).at(0)->setAnimSpeed(5);
    
    _animationData.at(AnimationKey::SNOW_FLAKE_KEY).at(0)->setAnimSpeed(3);
    
    
    _animationData.at(AnimationKey::FUEL_KEY).at(0)->setAnimSpeed(INT_MAX);
    _animationData.at(AnimationKey::FUEL_KEY).at(1)->setAnimSpeed(5);
    _animationData.at(AnimationKey::FUEL_KEY).at(1)->setRepeatTime(1);
    
    _animationData.at(AnimationKey::NEXT_STAGE_DOOR_KEY).at(0)->setAnimSpeed(4);
    _animationData.at(AnimationKey::NEXT_STAGE_DOOR_KEY).at(0)->setRepeatTime(1);
    _animationData.at(AnimationKey::NEXT_STAGE_DOOR_KEY).at(1)->setAnimSpeed(4);
    
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 1)).at(0)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 1)).at(0)->setRepeatTime(1);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 1)).at(1)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 1)).at(1)->setRepeatTime(1);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 1)).at(2)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 1)).at(2)->setRepeatTime(1);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 1)).at(3)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 1)).at(3)->setRepeatTime(1);
    
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 2)).at(0)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 2)).at(0)->setRepeatTime(1);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 2)).at(1)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 2)).at(1)->setRepeatTime(1);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 2)).at(2)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 2)).at(2)->setRepeatTime(1);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 2)).at(3)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 2)).at(3)->setRepeatTime(1);
    
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 3)).at(0)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 3)).at(0)->setRepeatTime(1);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 3)).at(1)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 3)).at(1)->setRepeatTime(1);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 3)).at(2)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 3)).at(2)->setRepeatTime(1);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 3)).at(3)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 3)).at(3)->setRepeatTime(1);
    
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 4)).at(0)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 4)).at(0)->setRepeatTime(1);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 4)).at(1)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 4)).at(1)->setRepeatTime(1);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 4)).at(2)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 4)).at(2)->setRepeatTime(1);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 4)).at(3)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 4)).at(3)->setRepeatTime(1);
    
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 5)).at(0)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 5)).at(0)->setRepeatTime(1);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 5)).at(1)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 5)).at(1)->setRepeatTime(1);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 5)).at(2)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 5)).at(2)->setRepeatTime(1);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 5)).at(3)->setAnimSpeed(2);
    _animationData.at(AnimationKey(ObjectKey::EFFECT_LAND_KEY, 5)).at(3)->setRepeatTime(1);
    
//    _animationData.at(AnimationKey::EFFECT_LAND1_TOP_KEY).at(1)->setAnimSpeed(2);
//    _animationData.at(AnimationKey::EFFECT_LAND1_TOP_KEY).at(1)->setRepeatTime(1);
//    _animationData.at(AnimationKey::EFFECT_LAND1_TOP_KEY).at(2)->setAnimSpeed(2);
//    _animationData.at(AnimationKey::EFFECT_LAND1_TOP_KEY).at(2)->setRepeatTime(1);
//    _animationData.at(AnimationKey::EFFECT_LAND1_TOP_KEY).at(3)->setAnimSpeed(2);
//    _animationData.at(AnimationKey::EFFECT_LAND1_TOP_KEY).at(3)->setRepeatTime(1);
}




void AnimationManager::loadAnimationDataFromFile(AnimationKey animationKey)
{
    std::string path = StringUtils::format("res/avatar/%s_%d_%d.plist",animationKey.type.c_str(), animationKey.id, animationKey.level);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(path);
    
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
    
    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);
    
    auto framesDict = dict.at("frames");
    auto item = framesDict.asValueMap();
    std::vector<int> array;
    
    std::vector<int> actionArr;
    std::vector<int> totalFrameArr;
    
    for (auto itr = item.cbegin(); itr != item.cend(); ++itr)
    {
        auto index = itr->first.find("/") + 1;
        auto idx = itr->first.find("/", index);
        auto a = itr->first.substr(index, idx - index);
        auto action = atoi(a.c_str());
        array.push_back(action);
        bool isExist = false;
        int count = 0;
        for (auto i = actionArr.cbegin(); i != actionArr.cend(); ++i)
        {
            if ((*i) == action)
            {
                isExist = true;
            }
            count++;
        }
        if (!isExist)
            actionArr.push_back(action);
    }
    
    std::sort(actionArr.begin(), actionArr.end());
    std::sort(array.begin(), array.end());
    
    int temp = 0;
    for (auto i = actionArr.cbegin(); i != actionArr.cend(); ++i) {
        int count = 0;
        for (auto itr = array.cbegin(); itr != array.cend(); ++itr)
        {
            if ((*itr) == actionArr.at(temp))
            {
                count++;
            }
        }
        if (animationKey.type == "CHAR")
        {
            if (animationKey.id == (int)IDCHAR::SHIPPER)
            {
                totalFrameArr.push_back(count);
            }
            else
                totalFrameArr.push_back(count/2);
        }
        else
            totalFrameArr.push_back(count);
        temp++;
    }
    
    cocos2d::Vector<CAnimation*> animations;
    
    for (auto i = 0; i < actionArr.size(); ++i)
    {
        auto state = CAnimation::create();
        state->setId(actionArr.at(i));
        state->setTotalFrame(totalFrameArr.at(i));
        animations.pushBack(state);
    }
    _animationData.insert(std::make_pair(animationKey, animations));
}

