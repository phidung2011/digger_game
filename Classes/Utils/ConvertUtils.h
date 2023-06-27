//
//  ConvertUtils.h
//  bomberman
//
//  Created by NGOCDIEP on 2/26/15.
//
//

#ifndef __bomberman__ConvertUtils__
#define __bomberman__ConvertUtils__



const int MIN_PLAYERS = 1;
const int MAX_PLAYERS = 1;

#include "cocos2d.h"
class ConvertUtils{
public:
    static cocos2d::Vec2 convertCDDevicetoMap(cocos2d::Vec2 device, cocos2d::Vec2 mapPos);//chuyen toa do device -> toa do map
    static cocos2d::Vec2 convertCDMaptoDevice(cocos2d::Vec2 vec2, cocos2d::Size sizeMap);//chuyen toa do map -> toa do device
    static cocos2d::Vec2 convertCDMaptoMatrix(cocos2d::Vec2 vec2, cocos2d::Vec2 sizeTile, cocos2d::Size sizeMapMatrix);//chuyen toa do map -> toa do matrix
    static cocos2d::Vec2 convertCDMatrixtoDevice(cocos2d::Vec2 vec2);
    static cocos2d::Vec2 convertCDMatrixtoMap(cocos2d::Vec2 vec2,cocos2d::Vec2 sizeTile, cocos2d::Size sizeMapMatrix);
    static cocos2d::Vec2 convertMapToDevice(cocos2d::Vec2 pos, cocos2d::Vec2 mapPos);
};
#endif /* defined(__bomberman__ConvertUtils__) */
