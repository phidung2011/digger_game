//
//  Player.h
//  rectdemo
//
//  Created by Nguyễn Lê Lợi on 6/2/15.
//
//

#ifndef __rectdemo__Player__
#define __rectdemo__Player__

#include "BaseCharacter.h"
#include "DataManager.h"
//#include "cocos-widget.h"
enum
{
    moveActTag = 10
};


class Player : public BaseCharacter
{
public:

    
    CREATE_FUNC(Player);
    bool isDead;
    bool isMovable(int dir) override;
    void executeControl(int dir);
    bool destroy() override;
    void onDestroyObject() override;
    
    void collectItem(DataObject* item);
    bool worldUpdate() override;
    
    bool updateTile(cocos2d::Vec2 nextPos) override;
    void move(int dir, State state) override;
    
    MapData& getData(){return _data;};
    
    CC_SYNTHESIZE(int, _timePlay, TimePlay);
    
//    bool isImmortal(){return _isImmortal;};
    void inputUpdate() override;
    void updateScore();
    MapData& getBonusScore(){return _bonusScore;};
    int _totalGrassDiamond;
    int _totalScore;
private:
    int stateToAnimation(State state) const override;
protected:
    Player();
    ~Player();
    MapData _data;
    bool init() override;
    MapData _bonusScore;
    
    bool _isImmortal;
    int _immortalTime;
    CC_SYNTHESIZE(DroppingObject*, _objectPushing, ObjectPushing);
};

#endif /* defined(__rectdemo__Player__) */


