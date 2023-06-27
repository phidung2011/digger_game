//
//  CarShipper.cpp
//  gamebase
//
//  Created by NGOCDIEP on 7/3/15.
//
//

#include "CarShipper.h"
#include "GameConfig.h"
#include "MainGameScene.h"
#include "AvatarConfig.h"
USING_NS_CC;

CarShipper::CarShipper()
: _countLand(0)
, goAHead(false)
{
}

CarShipper::~CarShipper(){
}

bool CarShipper::init()
{
    if (!BaseCharacter::initWithKey(AnimationKey::SHIPPER_KEY) || !BaseCharacter::init())
    {
        return false;
    }
    _speed = 1.9;
    _idTile = (int)IDTILE::CHARACTER;
//    _rotation = 0;
    int rd = random(0,1);
    if (rd == 0)
    {
        _direction = true;
    }
    else
        _direction = false;
    
    this->setFlippedX(!_direction);
    _landDir = Node::INVALID_TAG;
     _frontDir = dirSkill;
    _count = 1;
    return true;
}

void CarShipper::initDir()
{
    auto pos = this->getMatrixPos();
    
    auto tileBot = MainGameScene::getInstance()->getTileMap()->getIdTile(pos + Vec2(0,1));
    auto tileRight = MainGameScene::getInstance()->getTileMap()->getIdTile(pos + Vec2(1,0));
    auto tileTop = MainGameScene::getInstance()->getTileMap()->getIdTile(pos + Vec2(0,-1));
    auto tileLeft = MainGameScene::getInstance()->getTileMap()->getIdTile(pos + Vec2(-1,0));
    
    if (_direction)
    {
        if ((IDTILE)tileBot != IDTILE::DEFAULT)
        {
            _landDir = dt_bot;
            dirSkill = dt_right;
            return;
        }
        if ((IDTILE)tileRight != IDTILE::DEFAULT)
        {
            _landDir = dt_right;
            dirSkill = dt_top;
            return;
        }
        if ((IDTILE)tileTop != IDTILE::DEFAULT)
        {
            _landDir = dt_top;
            dirSkill = dt_left;
            return;
        }
        if ((IDTILE)tileLeft != IDTILE::DEFAULT)
        {
            _landDir = dt_left;
            dirSkill = dt_bot;
            return;
        }
    }
    else
    {
        if ((IDTILE)tileBot != IDTILE::DEFAULT)
        {
            _landDir = dt_bot;
            dirSkill = dt_left;
            return;
        }
        if ((IDTILE)tileLeft != IDTILE::DEFAULT)
        {
            _landDir = dt_left;
            dirSkill = dt_top;
            return;
        }
        if ((IDTILE)tileTop != IDTILE::DEFAULT)
        {
            _landDir = dt_top;
            dirSkill = dt_right;
            return;
        }
        if ((IDTILE)tileRight != IDTILE::DEFAULT)
        {
            _landDir = dt_right;
            dirSkill = dt_bot;
            return;
        }
    }
    _landDir = dt_bot;
}

int CarShipper::getMove()
{
    if (_count < 4)
    {
        int rd = 0;
        if (_direction)
        {
            rd = ((dirSkill-1) + _count) % 4;
        }
        else
            rd = abs(((dirSkill-1) + (4 - _count)) % 4);
        
        
        if (isMovable(rd + 1))
        {
            return rd + 1;
        }
        else
        {
            _count++;
            return getMove();
        }
    }
    else
        return INVALID_TAG;
}

bool CarShipper::isHaveLand()
{
    int tile;
    auto pos = this->getMatrixPos();
    if (_direction)
    {
        switch (dirSkill)
        {
            case dt_top:
                tile = MainGameScene::getInstance()->getTileMap()->getIdTile(pos + Vec2(1,0));
                break;
            case dt_left:
                tile = MainGameScene::getInstance()->getTileMap()->getIdTile(pos + Vec2(0,-1));
                break;
            case dt_right:
                tile = MainGameScene::getInstance()->getTileMap()->getIdTile(pos + Vec2(0,1));
                break;
            case dt_bot:
                tile = MainGameScene::getInstance()->getTileMap()->getIdTile(pos + Vec2(-1,0));
                break;
        }
    }
    else
    {
        switch (dirSkill)
        {
            case dt_top:
                tile = MainGameScene::getInstance()->getTileMap()->getIdTile(pos + Vec2(-1,0));
                break;
            case dt_left:
                tile = MainGameScene::getInstance()->getTileMap()->getIdTile(pos + Vec2(0,1));
                break;
            case dt_right:
                tile = MainGameScene::getInstance()->getTileMap()->getIdTile(pos + Vec2(0,-1));
                break;
            case dt_bot:
                tile = MainGameScene::getInstance()->getTileMap()->getIdTile(pos + Vec2(1,0));
                break;
        }
    }
    return !(tile == (int)IDTILE::DEFAULT ||
            tile == (int)IDTILE::PLAYER ||
            tile == (int)IDTILE::MARKED_PLAYER ||
            tile == (int)IDTILE::BOMB_SPIKES);
}

void CarShipper::move(int dir, State state)
{
    Vec2 vector = Vec2::ZERO;
    Vec2 baseVector = Vec2::ZERO;
    _frontDir = dir;
    dirSkill = dir;
    int totalLoop = TILE_SIZE/_speed;
    this->setState(state);
    switch (dir)
    {
        case dt_top:
        {
            if (_direction)
            {
                _landDir = dt_right;
            }
            else
                _landDir = dt_left;
            vector = Vec2(0,TILE_SIZE);
            baseVector = Vec2(0,-1);
            _backDir = dt_bot;
            break;
        }
        case dt_left:
        {
            if (_direction)
            {
                _landDir = dt_top;
            }
            else
                _landDir = dt_bot;
            vector = Vec2(-TILE_SIZE,0);
            baseVector = Vec2(-1,0);
            _backDir = dt_right;
            break;
        }
        case dt_right:
        {
            if (_direction)
            {
                _landDir = dt_bot;
            }
            else
                _landDir = dt_top;
            vector = Vec2(TILE_SIZE,0);
            baseVector = Vec2(1,0);
            _backDir = dt_left;
            break;
        }
        case dt_bot:
        {
            if (_direction)
            {
                _landDir = dt_left;
            }
            else
                _landDir = dt_right;
            vector = Vec2(0,-TILE_SIZE);
            baseVector = Vec2(0,1);
            _backDir = dt_top;
            break;
        }
    }
    
    CMoveBy* move = CMoveBy::create(vector, totalLoop);
    Vec2 prevPos = this->getMatrixPos();
    MainGameScene::getInstance()->getTileMap()->setIdTile(prevPos, (int)IDTILE::MARKED_CHARACTER);
    
    auto call = CCallback::create([prevPos, this]()
                                  {
                                      if (MainGameScene::getInstance()->getTileMap()->getIdTile(prevPos) == (int)IDTILE::MARKED_CHARACTER)
                                      {
                                          MainGameScene::getInstance()->getTileMap()->setIdTile(prevPos,(int)IDTILE::DEFAULT);
                                      }
                                  });
    auto seq = CSequence::create(call, move, NULL);
    this->runAct(seq);
    _isCollisionOnMap = !this->updateTile(prevPos + baseVector);

}

void CarShipper::inputUpdate()
{
    //execute control
    if (_actPool.empty())
    {
        if (isHaveLand())
        {
            goAHead = false;
            if (isMovable(dirSkill))
            {
                this->move(dirSkill, sMoving);
                setRotate();
            }
            else
            {
                auto getMove = this->getMove();
                if (getMove != INVALID_TAG)
                {
                    this->move(getMove, sMoving);
                    setRotate();
                }
                _count = 1;
            }
        }
        else
        {
            if (!goAHead) {
                _countLand++;
                this->move(_landDir, sMoving);
                setRotate();
                if (_countLand > 10)
                {
                    goAHead = true;
                    _countLand = 0;
                }
            }
            else
            {
                if (isMovable(dirSkill))
                {
                    this->move(dirSkill, sMoving);
                    setRotate();
                }
                else
                {
                    int move = this->getMove();
                    if (move != INVALID_TAG)
                    {
                        this->move(move, sMoving);
                        setRotate();
                    }
                    _count = 1;
                }
            }

        }
    }
    
    
}

void CarShipper::setRotate()
{
    switch (_landDir)
    {
        case dt_bot:
            if (dirSkill == dt_right)
            {
                this->setRotation(0);
                
            }
            else if (dirSkill == dt_left)
            {
                this->setRotation(0);
            }
            break;
        case dt_right:
            if (dirSkill == dt_top)
            {
                this->setRotation(-90);
                
            }
            else if (dirSkill == dt_bot)
            {
                this->setRotation(-90);
            }
            break;
        case dt_top:
            if (dirSkill == dt_right)
            {
                this->setRotation(180);
                
            }
            else if (dirSkill == dt_left)
            {
                this->setRotation(180);
            }
            break;
        case dt_left:
            if (dirSkill == dt_top)
            {
                this->setRotation(90);
                
            }
            else if (dirSkill == dt_bot)
            {
                this->setRotation(90);
            }
            break;
            
        default:
            break;
    }
}

//int CarShipper::checkMove(){
//    Vec2 pos = ConvertUtils::convertCDMaptoMatrix(this->getPosition(), MainGameScene::getInstance()->getTileMap()->_tileSize,  MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
//    
//    int arr[3][3];
//    //Khoi tao arr
//    for(int i = 0; i< 3; i++)
//        for(int j = 0; j< 3; j++){
//            arr[i][j] = -30000;
//        }
//    //Tao gia tri cho arr
//    for(int i = 0; i< 3; i++){
//        for(int j = 0; j< 3; j++){
//            int ii = pos.x - 1 + i;
//            int jj = pos.y - 1 + j;
//            int tg = MainGameScene::getInstance()->getTileMap()->getIdTile(Vec2(ii,jj));
//            //            log("%d ",tg);
//            if(tg == (int)IDTILE::CHARACTER || tg == (int)IDTILE::MARKED_CHARACTER)
//            {
//                tg = -10;
//            }else if(tg != (int)IDTILE::DEFAULT && tg != (int)IDTILE::BOMB_SPIKES && tg != (int)IDTILE::PLAYER && tg != (int)IDTILE::MARKED_PLAYER)
//                tg = -25;
//            else
//                tg = 6;
//            arr[j][i] = tg;
//            //            log("  --  %d  %d  %d" ,ii, jj, arr[j][i]);
//        }
//    }
//    
//    int moveI = -300;
//    int moveJ = -300;
//    int dir = this-> _frontDir;
//    bool checkBack = false;
//    switch (dir) {
//        case dt_top:
//            moveI = 2;
//            moveJ = 1;
//            if(arr[0][1] == -10){
//                checkBack = true;
//                
//            }
//            break;
//        case dt_left:
//            moveI = 1;
//            moveJ = 2;
//            if(arr[1][0] == -10)
//                checkBack = true;
//            break;
//        case dt_right:
//            moveI = 1;
//            moveJ = 0;
//            if(arr[1][2] == -10)
//                checkBack = true;
//            break;
//        case dt_bot:
//            moveI = 0;
//            moveJ = 1;
//            if(arr[2][1] == -10)
//                checkBack = true;
//            break;
//    }
//    
//    //Thiet lap lai gia tri ở ô di chuyể trước đó của xe là 0;
//    if(moveI != -300 && moveJ != -300 && arr[moveI][moveJ] >= 0){
//        if(checkBack == true )
//            arr[moveI][moveJ] = 20;
//        else
//            arr[moveI][moveJ] = 0;
//    }
//    
//    int rota = (int)this->getRotation();
//    
//    switch (rota) {
//        case 0:{
//            if(arr[moveI + 1][moveJ] == -25)
//                arr[moveI + 1][moveJ] = -300;
//            if(arr[2][1] == -25){
//                arr[2][1] = -300;
//                arr[moveI + 1][moveJ] = -25;
//            }
//            break;
//        }
//        case 90:{
//            if(arr[moveI][moveJ - 1] == -25)
//                arr[moveI][moveJ - 1] = -300;
//            if(arr[1][0] == -25){
//                arr[1][0] = -300;
//                arr[moveI][moveJ - 1] = -25;
//            }
//            break;
//        }
//        case 180:{
//            if(arr[moveI - 1][moveJ] == -25)
//                arr[moveI - 1][moveJ] = -300;
//            if(arr[0][1] == -25){
//                arr[0][1] = -300;
//                arr[moveI - 1][moveJ] = -25;
//            }
//            break;
//        }
//        case 270:{
//            if(arr[moveI][moveJ + 1] == -25)
//                arr[moveI][moveJ + 1] = -300;
//            if(arr[1][2] == -25){
//                arr[1][2] = -300;
//                arr[moveI][moveJ + 1] = -25;
//            }
//            break;
//        }
//        default:
//            break;
//    }
//    
//    //Thiet lap lai gia tri ben canh　ô bám của xe ở bước đi trước
//    for(int i = 0; i< 3; i++)
//        for(int j = 0; j< 3; j++){
//            if(arr[i][j] == -300){
//                if(i - 1 >= 0 && arr[i - 1][j] >= 0)
//                    arr[i - 1][j] += 1;
//                if(i + 1 <= 2 && arr[i + 1][j] >= 0)
//                    arr[i + 1][j] += 1;
//                if(j - 1 >= 0 && arr[i][j - 1] >= 0)
//                    arr[i][j - 1] += 1;
//                if(j + 1 <= 2 && arr[i][j + 1] >= 0)
//                    arr[i][j + 1] += 1;
//                if(j + 1 <= 2 && arr[i][j + 1] >= 0)
//                    arr[i][j + 1] += 1;
//                if(j + 1 <= 2 && i + 1 <= 2 && arr[i + 1][j + 1] >= 0)
//                    arr[i + 1][j + 1] += 1;
//                if(j + 1 <= 2 && i - 1 >= 0 && arr[i - 1][j + 1] >= 0)
//                    arr[i - 1][j + 1] += 1;
//                if(j - 1 >= 0 && i - 1 >= 0 && arr[i - 1][j - 1] >= 0)
//                    arr[i - 1][j - 1] += 1;
//                if(j - 1 >= 0 && i + 1 <= 2 && arr[i + 1][j - 1] >= 0)
//                    arr[i + 1][j - 1] += 1;
//                
//            }
//        }
//    
//    if(arr[1][0] <= -25 ){
//        if(arr[0][1] >= 0)
//            arr[0][1]++;
//        if(arr[2][1] >= 0)
//            arr[2][1]++;
//    }
//    if(arr[1][2] <= -25 ){
//        if(arr[0][1] >= 0)
//            arr[0][1]++;
//        if(arr[2][1] >= 0)
//            arr[2][1]++;
//    }
//    if(arr[0][1] <= -25 ){
//        if(arr[1][0] >= 0)
//            arr[1][0]++;
//        if(arr[1][2] >= 0)
//            arr[1][2]++;
//    }
//    if(arr[2][1] <= -25 ){
//        if(arr[1][0] >= 0)
//            arr[1][0]++;
//        if(arr[1][2] >= 0)
//            arr[1][2]++;
//    }
//    
//    //Tim huong di tiep theo cho xe
//    int max = -30000;
//    int resultDir = 0;
//    for(int i = 0; i< 3; i++)
//        for(int j = 0; j< 3; j++){
//            if(arr[i][j] >= max){
//                if(i == 0 && j == 1 && arr[i][j]>= 0){
//                    max = arr[i][j];
//                    resultDir = dt_top;
//                }
//            }
//            if(arr[i][j] >= max){
//                if(i == 1 && j == 0 && arr[i][j]>= 0){
//                    max = arr[i][j];
//                    resultDir = dt_left;
//                }
//            }
//            if(arr[i][j] >= max){
//                if(i == 1 && j == 2 && arr[i][j]>= 0){
//                    max = arr[i][j];
//                    resultDir = dt_right;
//                }
//            }
//            if(arr[i][j] >= max){
//                if(i == 2 && j == 1 && arr[i][j]>= 0){
//                    max = arr[i][j];
//                    resultDir = dt_bot;
//                }
//            }
//        }
//    
//    if(resultDir == dt_top){
//        if(arr[1][0] == -10&& arr[1][2] == -10&& arr[0][0] != -25 && arr[0][2] != -25)
//            return 0;
//    }else if(resultDir == dt_bot){
//        if(arr[1][0] == -10&& arr[1][2] == -10&& arr[2][0] != -25 && arr[2][2] != -25)
//            return 0;
//    }else if(resultDir == dt_left){
//        if(arr[0][1] == -10&& arr[2][1] == -10&& arr[0][0] != -25 && arr[2][0] != -25)
//            return 0;
//    }else if(resultDir == dt_right){
//        if(arr[0][1] == -10&& arr[2][1] == -10&& arr[0][2] != -25 && arr[2][2] != -25)
//            return 0;
//    }
//    if(resultDir == dt_top || resultDir == dt_bot){
//        int tg1 = arr[0][0] + arr[1][0] + arr[2][0];
//        int tg2 = arr[0][2] + arr[1][2] + arr[2][2];
//        bool ck = false;
//        if(resultDir == dt_top){
//            int tg = arr[2][0] + arr[2][1] + arr[2][2];
//            if(tg == -25 * 3 && arr[1][0] <= -25 && arr[1][2] <= -25)
//                ck = true;
//        }
//        if(resultDir == dt_bot){
//            int tg = arr[0][0] + arr[0][1] + arr[0][2];
//            if(tg == -25 * 3 && arr[1][0] <= -25 && arr[1][2] <= -25)
//                ck = true;
//        }
//
//        if(tg1 < tg2){
//            if(ck == true){
//                _rotation = 270;
//            }else{
//                _rotation = 90;
//            }
//        }else{
//            if(ck == true){
//                _rotation = 90;
//            }else{
//                _rotation = 270;
//            }
//        }
//    }else if(resultDir == dt_left || resultDir == dt_right){
//        int tg1 = arr[0][0] + arr[0][1] + arr[0][2];
//        int tg2 = arr[2][0] + arr[2][1] + arr[2][2];
//        bool ck = false;
//        if(resultDir == dt_left){
//            int tg = arr[0][2] + arr[1][2] + arr[2][2];
//            if(tg == -25 * 3 && arr[0][1] <= -25 && arr[2][1] <= -25)
//                ck = true;
//        }
//        if(resultDir == dt_right){
//            int tg = arr[0][0] + arr[1][0] + arr[2][0];
//            if(tg == -25 * 3 && arr[0][1] <= -25 && arr[2][1] <= -25)
//                ck = true;
//        }
//
//        if(tg1 < tg2){
//            if(ck == true){
//                _rotation = 0;
//            }else{
//                _rotation = 180;
//            }
//        }else{
//            if(ck == true){
//                _rotation = 180;
//            }else{
//                _rotation = 0;
//            }
//        }
//    }
//    return resultDir;
//}
