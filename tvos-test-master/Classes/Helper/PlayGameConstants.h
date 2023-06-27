//
//  PlayGameConstants.h
//  digger
//
//  Created by Phi Dzung on 10/30/15.
//
//

#ifndef PlayGameConstants_h
#define PlayGameConstants_h

#include "cocos2d.h"

#define IOS() (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#define ACH_PLAY_10_TIMES "com.newwindsoftware.bean.achievvement"
#define ACH_PLAY_50_TIMES "com.newwindsoftware.bean.achievvement"
#define ACH_PLAY_100_TIMES "com.newwindsoftware.bean.achievvement"

#define LEAD_STAR_MODE !IOS() ? "CgkI08fi59IWEAIQAQ" : "com.bigi.digger1.leaderboard"

#endif /* PlayGameConstants_h */
