#include "GameScene.h"

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
    addChild(sprite);
}

bool GameScene::onTouchesBegan(Touch *touch, Event *event)
{
    auto touchLoc = touch->getLocation();
    
    static int i = 0;
    std::string sprites[] = { "banana.png", "apple.png", "coconut.png", "orange.png", "grape.png", "yam.png", "yam2.png", "stone.png"};
    
    spawnSprite(sprites[i], touchLoc);
    i = (i + 1) % (sizeof(sprites)/sizeof(sprites[0]));
    
    return false;
}

void GameScene::onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event){
    CCLOG("X: %f", acc->x);
    CCLOG("Y: %f", acc->y);
    CCLOG("Z: %f", acc->z);
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
    Device::setAccelerometerEnabled(true);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("background.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("items.plist");
    
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(GameScene::onAcceleration, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::createWithSpriteFrameName("background.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
//    sprite->runAction(RepeatForever::create(Sequence::create(MoveTo::create(2.5, Vec2(visibleSize.width/2.0+25,visibleSize.height/2)), MoveTo::create(2.5, Vec2(visibleSize.width/2.0-25,visibleSize.height/2)), NULL)));
    
    sprite = Sprite::createWithSpriteFrameName("foreground.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 5);
    
    shapeCache = PhysicsShapeCache::getInstance();
    float scaleFactor = 1.0;
    if (visibleSize.height <= 320) {
        scaleFactor = 4.0;
    } else if (visibleSize.height <= 640) {
        scaleFactor = 2.0;
    }
    shapeCache->addShapesWithFile("shapes.plist", scaleFactor);
    
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
    spawnSprite("banana.png", pos);
    
    auto leftLayer = Layer::create();
    leftLayer->setContentSize(Size(2, visibleSize.height));
    auto borderBody = PhysicsBody::createBox(leftLayer->getContentSize());
    borderBody->setDynamic(false);
    leftLayer->setPhysicsBody(borderBody);
    leftLayer->setPosition(-2, 0);
    this->addChild(leftLayer);
    
    auto rightLayer = Layer::create();
    rightLayer->setContentSize(Size(2, visibleSize.height));
    borderBody = PhysicsBody::createBox(rightLayer->getContentSize());
    borderBody->setDynamic(false);
    rightLayer->setPhysicsBody(borderBody);
    rightLayer->setPosition(visibleSize.width, 0);
    this->addChild(rightLayer);
    
    auto bottomLayer = Layer::create();
    bottomLayer->setContentSize(Size(visibleSize.width, 20));
    borderBody = PhysicsBody::createBox(bottomLayer->getContentSize());
    borderBody->setDynamic(false);
    bottomLayer->setPhysicsBody(borderBody);
    bottomLayer->setPosition(0, 0);
    this->addChild(bottomLayer);
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    return true;
}