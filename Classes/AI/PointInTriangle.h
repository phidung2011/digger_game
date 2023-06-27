//
//  PointInTriangle.h
//  gamebase
//
//  Created by NGOCDIEP on 8/3/15.
//
//

#ifndef __gamebase__PointInTriangle__
#define __gamebase__PointInTriangle__

#include <stdio.h>
#include "cocos2d.h"

class PointInTriangle{
public:
    
    static bool checkPoint(cocos2d::Vec2 pos, cocos2d::Vec2 posA, cocos2d::Vec2 posB, cocos2d::Vec2 posC);
    static float sign(cocos2d::Vec2 posA, cocos2d::Vec2 posB, cocos2d::Vec2 posC);
    
    
    //ax + by + c = 0; Vec3(a,b,c)
    static cocos2d::Vec3 ptDuongThang(cocos2d::Vec2 point1 , cocos2d::Vec2 point2);
    
    //Khoang cach tu 1 diem toi 1 duong thang
    static float kcDiemVaDT(cocos2d::Vec2 point, cocos2d::Vec2 pointA, cocos2d::Vec2 pointB);
};

#endif /* defined(__gamebase__PointInTriangle__) */
