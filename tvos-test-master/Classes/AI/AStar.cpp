//
//  AStar.cpp
//  gamebase
//
//  Created by Phi Dzung on 7/9/15.
//
//

#include "AStar.h"
#include <MainGameScene.h>
#include <GameConfig.h>
#include "AvatarConfig.h"
CNode::CNode()
{
    
}
CNode::CNode(CNode* parent, cocos2d::Vec2 pos, int f, int g)
{
    _parent = parent;
    _pos = pos;
    _f = f;
    _g = g;
}

CNode::~CNode()
{
    
}

CNode* CNode::create(CNode* parent, cocos2d::Vec2 point)
{
    auto newNode = new CNode(parent, point, 0, 0);
    newNode->autorelease();
    return newNode;
}

//static int world[8][8] =
//{
//    {0,0,1,0,0,0,0,0},
//    {1,0,1,0,1,0,0,0},
//    {0,0,0,0,1,0,0,0},
//    {0,0,0,1,0,0,0,0},
//    {0,0,0,1,0,0,0,0},
//    {0,0,0,1,0,0,0,0},
//    {0,0,0,1,0,0,0,0},
//    {0,0,0,1,0,0,0,0},
//};


std::vector<cocos2d::Vec2> AStar::neighbours(cocos2d::Vec2 pos, int minX, int maxX, int minY, int maxY)
{
    auto N = pos.y - 1;
    auto S = pos.y + 1;
    auto E = pos.x + 1;
    auto W = pos.x - 1;
    bool myN = (N > -1 && canWalkHere(pos.x, N, minX, maxX, minY, maxY));
    bool myS = (S < MainGameScene::getInstance()->getTileMap()->_tileMapSize.height && canWalkHere(pos.x, S, minX, maxX, minY, maxY));
    bool myE = (E < MainGameScene::getInstance()->getTileMap()->_tileMapSize.width && canWalkHere(E, pos.y, minX, maxX, minY, maxY));
    bool myW = (W > -1 && canWalkHere(W, pos.y, minX, maxX, minY, maxY));
    std::vector<cocos2d::Vec2> result;
    if(myN)
        result.push_back(Vec2(pos.x,N));
    if(myE)
        result.push_back(Vec2(E,pos.y));
    if(myS)
        result.push_back(Vec2(pos.x,S));
    if(myW)
        result.push_back(Vec2(W,pos.y));
    
//    diagonalNeighbours(myN, myS, myE, myW, N, S, E, W, result);
    
    return result;
}

//void AStar::diagonalNeighbours(bool myN, bool myS, bool myE, bool myW, int N, int S, int E, int W, std::vector<Vec2> result)
//{
//    if(myN)
//    {
//        if(myE && canWalkHere(E, N))
//            result.push_back(Vec2(E, N));
//        if(myW && canWalkHere(W, N))
//            result.push_back(Vec2(W, N));
//    }
//    if(myS)
//    {
//        if(myE && canWalkHere(E, S))
//            result.push_back(Vec2(E, S));
//        if(myW && canWalkHere(W, S))
//            result.push_back(Vec2(W, S));
//    }
//}

bool AStar::canWalkHere(int x, int y, int minX, int maxX, int minY, int maxY)
{
    if (x < minX || x > maxX || y < minY || y > maxY)
    {
        return false;
    }
    auto tile = MainGameScene::getInstance()->getTileMap()->getIdTile(Vec2(x,y));
    return (tile == (int)IDTILE::DEFAULT ||
            tile == (int)IDTILE::PLAYER ||
            tile == (int)IDTILE::CHARACTER ||
            tile == (int)IDTILE::MARKED_CHARACTER ||
            tile == (int)IDTILE::MARKED_PLAYER);
}


cocos2d::Vector<CNode*> AStar::calculatePath(cocos2d::Vec2 startPos, cocos2d::Vec2 endPos, int range)
{
    int minX = startPos.x - range;
    int maxX = startPos.x + range;
    int minY = startPos.y - range;
    int maxY = startPos.y + range;
    
    auto start = CNode::create(NULL, startPos);
    
    cocos2d::Vector<CNode*> Open;
    cocos2d::Vector<CNode*> Closed;
    
    start->_g = 0;
    start->_h = getEuclideDistance(start->_pos, endPos);
    start->_f = start->_h + start->_g;
    
    Open.pushBack(start);
    
    cocos2d::Vector<CNode*> result;
    result.clear();
    
    while(Open.size() != 0)
    {
        CNode* current = Open.at(0);
        for (auto& node: Open)
        {
            if (node->_f < current->_f)
            {
                current = node;
            }
        }
        
        if (isExist(Closed, current->_pos)){ //neu ton tai thi continued
            Open.eraseObject(current);
            continue;//if node in close will do nothing
        }

        if (current->_pos == endPos)
        {
            Open.clear();
            Closed.clear();
            return reconstructPath(start, current);
        }
        else
        {
            Open.eraseObject(current);
            Closed.pushBack(current);
            
            for (auto& pos : neighbours(current->_pos, minX, maxX, minY, maxY))
            {
                if (isExist(Closed, pos)) //neu ton tai thi continued
                    continue;//if node in close will do nothing
                
                auto node = CNode::create(NULL, pos);
                auto tmp_current_g = current->_g + getEuclideDistance(current->_pos, pos);
                if (Open.getIndex(node) == CC_INVALID_INDEX || tmp_current_g < node->_g)
                {
                    node->_parent = current;
                    node->_g = tmp_current_g;
                    node->_h = getEuclideDistance(pos, endPos);
                    node->_f = node->_g + node->_h;
                    if (Open.getIndex(node) == CC_INVALID_INDEX)
                        Open.pushBack(node);
                }
            }
            
        }
        
    }
    return result;
}

bool AStar::isExist(cocos2d::Vector<CNode *> list, cocos2d::Vec2 pos)
{
    for (auto& node : list)
    {
        if (node->_pos == pos)
        {
            return true;
        }
    }
    return false;
}
