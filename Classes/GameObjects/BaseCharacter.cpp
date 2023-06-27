//
//  BaseCharacter.cpp
//  gamebase
//
//  Created by Nguyễn Lê Lợi on 7/1/15.
//
//

#include "BaseCharacter.h"
#include "GameConfig.h"
#include "MainGameScene.h"
#include "AvatarConfig.h"
#include "BumBum.h"

BaseCharacter::BaseCharacter()
: dirSkill(dt_right)
, _glShaderProgram(nullptr)
, _defaultGLProgram(nullptr)
, _rate(1.0f)
{
    _boomKey = AnimationKey::BOOM_CHARACTER_KEY;
}
BaseCharacter::~BaseCharacter()
{
//    CC_SAFE_RELEASE(_glShaderProgram);
    
    
    _glShaderProgram = nullptr;
    _defaultGLProgram = nullptr;
}

bool BaseCharacter::init()
{
    if (!BaseBomb::init()) {
        return false;
    }
    
    BlendFunc blendFunc={GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA};
    this->setBlendFunc(blendFunc);
    
    
//    BlendFunc blendFunc={GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA};
//    this->setBlendFunc(blendFunc);
//    
    
//    this->setRate(2);
    return true;
}
void BaseCharacter::setShader()
{
    //create and set shader program
    {
        GLchar * fragSource = (GLchar*) String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename("Shaders/FrozenShader.fsh").c_str())->getCString();
        _glShaderProgram = CGLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource);
        
        //check gl error
//        _glShaderProgram->attachUniform("blue");
        _defaultGLProgram = this->getGLProgram();
        this->setGLProgram(_glShaderProgram);
        
        CHECK_GL_ERROR_DEBUG();
    }
    //check gl error
    CHECK_GL_ERROR_DEBUG();
}

void BaseCharacter::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if (_glShaderProgram)
    {
        _glShaderProgram->use();
        glUniform1f(glGetUniformLocation(_glShaderProgram->getProgram(), "blue"), _rate);
//        _glShaderProgram->passUnifoValue1f("blue", _rate);
#if CC_USE_CULLING
        // Don't do calculate the culling if the transform was not updated
        auto visitingCamera = Camera::getVisitingCamera();
        auto defaultCamera = Camera::getDefaultCamera();
        if (visitingCamera == defaultCamera) {
            _insideBounds = ((flags & FLAGS_TRANSFORM_DIRTY)|| visitingCamera->isViewProjectionUpdated()) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;
        }
        else
        {
            _insideBounds = renderer->checkVisibility(transform, _contentSize);
        }
        
        if(_insideBounds)
#endif
        {
            _trianglesCommand.init(_globalZOrder, _texture->getName(), getGLProgramState(), _blendFunc, _polyInfo.triangles, transform, flags);
            renderer->addCommand(&_trianglesCommand);
        }
    }
    else
        Sprite::draw(renderer, transform, flags);
    
}
void BaseCharacter::move(int dir, State state)
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
            vector = Vec2(0,TILE_SIZE);
            baseVector = Vec2(0,-1);
            _backDir = dt_bot;
            break;
        }
        case dt_left:
        {
            vector = Vec2(-TILE_SIZE,0);
            baseVector = Vec2(-1,0);
            _backDir = dt_right;
            break;
        }
        case dt_right:
        {
            vector = Vec2(TILE_SIZE,0);
            baseVector = Vec2(1,0);
            _backDir = dt_left;
            break;
        }
        case dt_bot:
        {
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

bool BaseCharacter::isFirable()
{
    Vec2 pos = Vec2::ZERO;
    Vec2 pos2 = Vec2::ZERO;
    switch (dirSkill)
    {
        case dt_top:
            pos = this->getFrontPosition() + Vec2(0,TILE_SIZE);
            pos2 = pos + Vec2(0,TILE_SIZE);
            break;
            
        case dt_bot:
            pos = this->getFrontPosition() + Vec2(0,-TILE_SIZE);
            pos2 = pos + Vec2(0,-TILE_SIZE);
            break;
            
        case dt_left:
            pos = this->getFrontPosition() + Vec2(-TILE_SIZE,0);
            pos2 = pos + Vec2(-TILE_SIZE,0);
            break;
            
        case dt_right:
            pos = this->getFrontPosition() + Vec2(TILE_SIZE,0);
            pos2 = pos + Vec2(TILE_SIZE,0);
            break;
    }
    
    
    Vec2 posMatrix = ConvertUtils::convertCDMaptoMatrix(pos, MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
    
    Vec2 posMatrix2 = ConvertUtils::convertCDMaptoMatrix(pos2, MainGameScene::getInstance()->getTileMap()->_tileSize, MainGameScene::getInstance()->getTileMap()->_tileMapSizeMatrix);
    
    auto tile = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(posMatrix);
    auto tile2 = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(posMatrix2);
    
    if ((tile == IDTILE::DEFAULT && tile2 == IDTILE::DEFAULT))
    {
        return true;
    }
    
    return false;
}

bool BaseCharacter::isMovable(int dir)
{
    Vec2 pos = this->getMatrixPos();
    switch (dir)
    {
        case dt_top:
            pos = pos + Vec2(0,-1);
            break;
            
        case dt_bot:
            pos = pos + Vec2(0,1);
            break;
            
        case dt_left:
            pos = pos + Vec2(-1,0);
            break;
            
        case dt_right:
            pos = pos + Vec2(1,0);
            break;
        case 0:
            return false;
        default:
            break;
    }
    
    auto tile = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(pos);
    
    if (tile == IDTILE::DEFAULT ||
        tile == IDTILE::BOMB_SPIKES)
    {
        return true;
    }
    
    if (_state == sMoving &&
        (tile == IDTILE::PLAYER ||
         tile == IDTILE::MARKED_PLAYER))
    {
        return true;
    }
    
    return false;
}

void BaseCharacter::flip(int dir)
{
    if (dirSkill != dir)
    {
        switch (dir)
        {
            case dt_left:
                _baseDir = 0;
                this->setFlippedX(true);
                this->setFlippedY(false);
                break;
            case dt_right:
                _baseDir = 0;
                this->setFlippedX(false);
                this->setFlippedY(false);
                break;
            case dt_bot:
                _baseDir = 1;
                this->setFlippedX(false);
                this->setFlippedY(true);
                break;
            case dt_top:
                _baseDir = 1;
                this->setFlippedX(false);
                this->setFlippedY(false);
                break;
            default:
                break;
        }
        dirSkill = dir;

        
        
        auto spriteFrame = this->getSpriteFrameByKey(_key.type, _key.id, _key.level, this->getAnimation()->getId(), this->getCurrentFrame(), this->getBaseDir());
        this->setSpriteFrame(spriteFrame);
    }
}

bool BaseCharacter::worldUpdate()
{
    if (!_actPool.empty())
    {
        if (_isCollisionOnMap)
        {
            auto frontPos = this->getFrontMatrixPosition();
            auto tile = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos);
            
            switch (tile)
            {
                case IDTILE::BOMB_SPIKES :
                    this->destroy();
                    break;
                case IDTILE::PLAYER :
                    this->destroy();
                    break;
                case IDTILE::MARKED_PLAYER :
                {
                    if ( _frontDir == dt_bot ||  _frontDir == dt_top)
                    {
                        auto tileRight = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos + Vec2(1,0));
                        auto tileLeft = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos + Vec2(-1,0));
                        if (tileRight == IDTILE::PLAYER || tileLeft == IDTILE::PLAYER)
                        {
                            this->destroy();
                            break;
                        }
                        else
                        {
                            MainGameScene::getInstance()->getTileMap()->setIdTile(frontPos, (int)IDTILE::CHARACTER);
                        }
                    }
                    if ( _frontDir == dt_left ||  _frontDir == dt_right)
                    {
                        auto tileTop = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos + Vec2(0,-1));
                        auto tileBot = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(frontPos + Vec2(0,1));
                        if (tileTop == IDTILE::PLAYER || tileBot == IDTILE::PLAYER)
                        {
                            this->destroy();
                            break;
                        }
                        else
                        {
                            MainGameScene::getInstance()->getTileMap()->setIdTile(frontPos, (int)IDTILE::CHARACTER);
                        }
                    }
                }
                    break;
                case IDTILE::DEFAULT :
                {
                    MainGameScene::getInstance()->getTileMap()->setIdTile(frontPos, (int)IDTILE::CHARACTER);
                }
                    break;
                default:
                    break;
            }
            _isCollisionOnMap = false;
        }
    }
    else
    {
        
    }
    
    return _isValid;
}

bool BaseCharacter::updateTile(Vec2 nextPos)
{
    auto tile = (IDTILE)MainGameScene::getInstance()->getTileMap()->getIdTile(nextPos);
    if (tile == IDTILE::DEFAULT)
    {
        MainGameScene::getInstance()->getTileMap()->setIdTile(nextPos, _idTile);
        return true;
    }
    else return false;
}


void BaseCharacter::onDestroyObject()
{
    BaseBomb::onDestroyObject();
#if (USE_SIMPLE_AUDIO_ENGINE)
    SIMPLE_AUDIO->playEffect(EFFECT_CART);
#else
    AUDIO::play2d(EFFECT_CART, false, GameSingleton::getInstance()->SOUND*0.01, nullptr);
#endif
}

bool BaseCharacter::destroy()
{
    MainGameScene::getInstance()->getPlayer()->getBonusScore().enemies++;
    int tg = this->getKey().id;
    switch (tg)
    {
        case (int)IDCHAR::HAMMER :
            MainGameScene::getInstance()->getPlayer()->_totalScore += (int)SCORE::HAMMER;
            break;
        case (int)IDCHAR::ROLLER :
            MainGameScene::getInstance()->getPlayer()->_totalScore += (int)SCORE::ROLLER;
            break;
        case (int)IDCHAR::SHIPPER :
            MainGameScene::getInstance()->getPlayer()->_totalScore += (int)SCORE::SHIPPER;
            break;
        case (int)IDCHAR::TANKER :
            MainGameScene::getInstance()->getPlayer()->_totalScore += (int)SCORE::TANKER;
            break;
        case (int)IDCHAR::TRACKER :
            MainGameScene::getInstance()->getPlayer()->_totalScore += (int)SCORE::TRACKER;
            break;
    }
    
    //update score
    MainGameScene::getInstance()->getPlayer()->updateScore();
    
    if (MainGameScene::getInstance()->getPlayer()->getData().enemies > 0)
    {
        MainGameScene::getInstance()->getPlayer()->getData().enemies--;
        MainGameScene::getInstance()->getMenuBar()->getLabelEnemies()->setString(StringUtils::format("%d",MainGameScene::getInstance()->getPlayer()->getData().enemies));
        
    }
    if (MainGameScene::getInstance()->getPlayer()->getData().enemies == 0 && MainGameScene::getInstance()->getPlayer()->getData().diamonds == 0)
    {
        MainGameScene::getInstance()->SHOW_NEXT_STAGE_DOOR = true;
    }
    
    
    return TiledObject::destroy();
}


int BaseCharacter::stateToAnimation(State state) const
{
    switch (state)
    {
        case sIdle:
            return 0;
        case sMoving:
            return 0;
        case sAttacking:
            return 0;
        default:
            return -1;
    }
}
