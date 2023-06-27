//
//  PointInTriangle.cpp
//  gamebase
//
//  Created by NGOCDIEP on 8/3/15.
//
//

#include "PointInTriangle.h"

USING_NS_CC;

float PointInTriangle::sign(cocos2d::Vec2 posA, cocos2d::Vec2 posB, cocos2d::Vec2 posC){
    return (posA.x - posC.x) * (posB.y - posC.y) - (posB.x - posC.x) * (posA.y - posC.y);
}

bool PointInTriangle::checkPoint(cocos2d::Vec2 pos, cocos2d::Vec2 posA, cocos2d::Vec2 posB, cocos2d::Vec2 posC){
    bool b1, b2, b3;
    
    b1 = sign(pos, posA, posB) <= 0.0f;
    b2 = sign(pos, posB, posC) <= 0.0f;
    b3 = sign(pos, posC, posA) <= 0.0f;
    
    return ((b1 == b2) && (b2 == b3));
}

Vec3 PointInTriangle::ptDuongThang(cocos2d::Vec2 point1, cocos2d::Vec2 point2){
    float a = 0;
    float b = 0;
    float c = 0;
    
    a = point2.y - point1.y;
    b = point1.x - point2.x;
    float tg = a;
    a = a/tg;
    b = b/tg;
    c = -(a * point2.x + b * point2.y);
    
    return Vec3(a,b,c);
}

float PointInTriangle::kcDiemVaDT(cocos2d::Vec2 point, cocos2d::Vec2 pointA, cocos2d::Vec2 pointB){
    float d = 0;
    
    Vec3 dt = PointInTriangle::ptDuongThang(pointA, pointB);
    
    d = fabsf(dt.x * point.x + dt.y * point.y + dt.z)/sqrtf(dt.x * dt.x + dt.y * dt.y);
    
    return d;
}
