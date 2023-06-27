//
//  ConvertUtils.cpp
//  bomberman
//
//  Created by NGOCDIEP on 2/26/15.
//
//

#include "ConvertUtils.h"
#include "AvatarConfig.h"
USING_NS_CC;

Vec2 ConvertUtils::convertCDDevicetoMap(Vec2 device, Vec2 mapPos){
    return device + Vec2(fabsf(mapPos.x), fabsf(mapPos.y));
}
Vec2 ConvertUtils::convertCDMaptoDevice(Vec2 vec2, Size sizeMap){
    float x = 0;
    float y = 0;
    Point winsize = Director::getInstance()->getWinSize();
    //nhan vat nam ve ben phai cua map. Nguoc lai se nam ve ben trai. Neu khong thi se nam o giua
    if(sizeMap.width - vec2.x < winsize.x * 0.5)
    {
        x = winsize.x - (sizeMap.width - vec2.x);
    }
    else if(vec2.x < winsize.x * 0.5)
    {
        x = vec2.x;
    }
    else
    {
        x = winsize.x * 0.5;
    }
    
    if(sizeMap.height - vec2.y < winsize.y * 0.5)
    {
        y = winsize.y - (sizeMap.height - vec2.y);
    }
    else if(vec2.y < winsize.y * 0.5)
    {
        y = vec2.y;
    }
    else
    {
        y = winsize.y * 0.5;
    }
    return Vec2(x,y);
}
Vec2 ConvertUtils::convertCDMaptoMatrix(cocos2d::Vec2 vec2, cocos2d::Vec2 sizeTile, cocos2d::Size sizeMapMatrix)
{
    int x = vec2.x / sizeTile.x;
    int y = sizeMapMatrix.height - vec2.y / sizeTile.y;
    return Vec2(x,y);
}

Vec2 ConvertUtils::convertCDMatrixtoMap(cocos2d::Vec2 vec2, cocos2d::Vec2 sizeTile, cocos2d::Size sizeMapMatrix)
{
    float x = vec2.x * sizeTile.x;
    float y = (sizeMapMatrix.height - vec2.y) * sizeTile.y;
    return Vec2(x,y) + Vec2(TILE_SIZE*0.5f,-TILE_SIZE*0.5f);
}

cocos2d::Vec2 ConvertUtils::convertMapToDevice(cocos2d::Vec2 pos, cocos2d::Vec2 mapPos)
{
    return (pos + mapPos);
}




