//
//  GameConfig.h
//  bomberman
//
//  Created by NGOCDIEP on 3/2/15.
//
//

#ifndef bomberman_GameConfig_h
#define bomberman_GameConfig_h

#include <VisibleRect.h>
#include <cocos-widget.h>
#include <cocos2d.h>
#include <Constants.h>
#include <StringUtil.h>
#include <LayerContainer.h>
#include "TransitionManager.h"
#include <ConvertUtils.h>
#include <CMoveBy.h>
#include <CSequence.h>
#include <CCallback.h>
#include <AnimationManager.h>
#include "DataManager.h"
#include "AppMacros.h"
#include "GameSingleton.h"
#include "Animator.h"
#include "TVWidget.h"




USING_NS_CC;
USING_NS_CC_WIDGET;





#define winSize Director::getInstance()->getWinSize()
#define GAME_FPS 30
#define DIRECTIONS 2

#define PI_NUMBER 3.141593f
#define EX 1
#define SIZE_ADD Vec2(50,50)
#define COUNT_TIME 360

static const int sl_level[5] = {10,10,10,10,12};

#define CONTROL_RECT Rect(0,0,winSize.width - 230, winSize.height - 150)


#define USE_SIMPLE_AUDIO_ENGINE true

#if (!USE_SIMPLE_AUDIO_ENGINE)
#include "AudioEngine.h"
#define AUDIO cocos2d::experimental::AudioEngine
#else
#include "SimpleAudioEngine.h"
#define SIMPLE_AUDIO CocosDenshion::SimpleAudioEngine::getInstance()
#endif

#endif

