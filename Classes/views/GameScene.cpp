//
//  GameScene.cpp
//  fruitmonkey
//
//  Created by Hari Krishna on 13/03/16.
//
//

#include "GameScene.h"
#include "Monkey.h"
#include "Basket.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, -640));
//    scene->getPhysicsWorld()->setDebugDrawMask(0xffff);
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
    srand (time (NULL));

    // return the scene
    return scene;
}

void GameScene::spawnSprite(const std::string &name, Vec2 pos)
{
    auto sprite = Sprite::createWithSpriteFrameName(name);
    shapeCache->setBodyOnSprite(name, sprite);
    sprite->setPosition(pos);
    itemsLayer->addChild(sprite);
}

bool GameScene::onTouchesBegan(Touch *touch, Event *event)
{
    static int x = 1;
    if (x == 0) {
        auto basket = Basket::createBasket(true);
        itemsLayer->addChild(basket);
        x++;
        return false;
    }
    auto touchLoc = touch->getLocation();
    
    static int i = 0;
    std::string sprites[] = { "banana.png", "apple.png", "coconut.png", "orange.png", "grape.png", "yam.png", "yam2.png", "stone.png"};
    
    spawnSprite(sprites[i], touchLoc);
    i = (i + 1) % (sizeof(sprites)/sizeof(sprites[0]));
    
    return false;
}

void GameScene::onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event){
//    CCLOG("X: %f", acc->x);
//    CCLOG("Y: %f", acc->y);
//    CCLOG("Z: %f", acc->z);
    this->playerMonkey->walk(acc->x);
}

bool GameScene::onContactBegin(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA && nodeB)
    {
        if (nodeA->getName() == "monkey")
        {
            nodeB->removeFromParentAndCleanup(true);
        }
        else if (nodeB->getName() == "monkey")
        {
            nodeA->removeFromParentAndCleanup(true);
        }
    }
    //bodies can collide
    return true;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    shapeCache = PhysicsShapeCache::getInstance();
    float scaleFactor = 1.0;
    if (visibleSize.height <= 320) {
        scaleFactor = 4.0;
    } else if (visibleSize.height <= 640) {
        scaleFactor = 2.0;
    }
    shapeCache->addShapesWithFile("shapes.plist", scaleFactor);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("background.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("items.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("monkey.plist");
    
    this->initListeners();
    
    this->initLayers();

    // add "HelloWorld" splash screen"
    auto backgroundSprite = Sprite::createWithSpriteFrameName("background.png");

    // position the sprite on the center of the screen
    backgroundSprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));

    // add the sprite as a child to this layer
    groundLayer->addChild(backgroundSprite, 0);
    auto foregroundSprite = Sprite::createWithSpriteFrameName("foreground.png");
    
    // position the sprite on the center of the screen
    foregroundSprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    
    // add the sprite as a child to this layer
    groundLayer->addChild(foregroundSprite, 5);
    
    auto pos = Vec2(Director::getInstance()->getWinSize()) / 2 + Director::getInstance()->getVisibleOrigin();
    
    // Add ground sprite and drop a banana
//    auto border = Sprite::createWithSpriteFrameName("border.png");
//    PhysicsBody *body = PhysicsShapeCache::getInstance()->createBodyWithName("border");
//    if (body)
//    {
//        border->setPhysicsBody(body);
//        body->setDynamic(false);
//    }
//    border->setPosition(0,0);
//    this->addChild(border);
    
    this->createBoundary();
    
    playerMonkey = Monkey::createMonkey();
    monkeyLayer->addChild(playerMonkey);
    
//    auto basket = Basket::createBasket(true);
//    itemsLayer->addChild(basket);
    
    return true;
}

void GameScene::initLayers() {
    groundLayer = Layer::create();
    this->addChild(groundLayer, 0);
    
    scrollingLayer = Layer::create();
    this->addChild(scrollingLayer, 10);
    
    itemsLayer = Layer::create();
    this->addChild(itemsLayer, 20);

    monkeyLayer = Layer::create();
    this->addChild(monkeyLayer, 21);
    
    hudLayer = Layer::create();
    this->addChild(hudLayer, 30);
}

void GameScene::initListeners() {
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(GameScene::onAcceleration, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin,
                                                    this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener,
                                                             this);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

}

Layer* GameScene::createPhysicsObject(cocos2d::Size size) {
    auto layer = Layer::create();
    layer->setContentSize(size);
    auto borderBody = PhysicsBody::createBox(layer->getContentSize());
    borderBody->setDynamic(false);
    layer->setPhysicsBody(borderBody);
    groundLayer->addChild(layer);
    
    return layer;
}

void GameScene::createBoundary() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto leftLayer = createPhysicsObject(Size(2, visibleSize.height));
    leftLayer->setPosition(-2, 0);
    
    auto rightLayer = createPhysicsObject(Size(2, visibleSize.height));
    rightLayer->setPosition(visibleSize.width, 0);
    
    auto bottomLayer = createPhysicsObject(Size(visibleSize.width, 10));
    bottomLayer->setPosition(0, 30);
    bottomLayer->getPhysicsBody()->setContactTestBitmask(0xfffffffd);
    bottomLayer->setName("bottom");
}