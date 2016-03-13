#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
#include "PhysicsShapeCache.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
    void spawnSprite(const std::string &name, cocos2d::Vec2 pos);
    bool onTouchesBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
private:
    Layer* itemsLayer;
    Layer* monkeyLayer;
    Layer* scrollingLayer;
    Layer* groundLayer;
    Layer* hudLayer;
    void onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event);
    bool onContactBegin(PhysicsContact& contact);
    PhysicsShapeCache *shapeCache;
};

#endif // __HELLOWORLD_SCENE_H__
