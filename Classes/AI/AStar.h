//
//  AStar.h
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 7/9/15.
//
//

#ifndef __gamebase__AStar__
#define __gamebase__AStar__

#include "cocos2d.h"

class CNode : public cocos2d::Ref
{
public:
    CNode();
    CNode(CNode* parent, cocos2d::Vec2 pos, int f, int g);
    ~CNode();
    static CNode* create(CNode* parent, cocos2d::Vec2 point);
    CNode* _parent;
    cocos2d::Vec2 _pos;
    int _h;
    int _f;
    int _g;
private:
    
};



class AStar
{
public:
    static float getManhattanDistance(cocos2d::Vec2 point, cocos2d::Vec2 goal)
    {
        return std::abs(point.x - goal.x) + std::abs(point.y - goal.y);
    };
    
    static float getDiagonalDistance(cocos2d::Vec2 point, cocos2d::Vec2 goal)
    {
        return MAX(std::abs(point.x - goal.x), std::abs(point.y - goal.y));
    };
    
    static float getEuclideDistance(cocos2d::Vec2 point, cocos2d::Vec2 goal)
    {
        return sqrt(pow(point.x - goal.x, 2) + pow(point.y - goal.y, 2));
    };

    
    static std::vector<cocos2d::Vec2> neighbours(cocos2d::Vec2 pos, int minX, int maxX, int minY, int maxY);
    
    static bool canWalkHere(int x, int y, int minX, int maxX, int minY, int maxY);
    
    
//    static void diagonalNeighbours(bool myN, bool myS, bool myE, bool myW, int N, int S, int E, int W, std::vector<cocos2d::Vec2> result);
    
    static cocos2d::Vector<CNode*> calculatePath(cocos2d::Vec2 startPos, cocos2d::Vec2 endPos, int range);
    
    static cocos2d::Vector<CNode*> reconstructPath(CNode* s,CNode* t)
    {
        cocos2d::Vector<CNode*> path;
        path.clear();
        CNode* tmp = t;
        while (tmp != NULL)
        {
            path.pushBack(tmp);
            tmp = tmp->_parent;
        }
        return path;
    };
    
    static bool isExist(cocos2d::Vector<CNode*> list, cocos2d::Vec2 pos);
    
private:
    
};


#endif /* defined(__gamebase__AStar__) */
