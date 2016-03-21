//
//  Basket.cpp
//  fruitmonkey
//
//  Created by Hari Krishna on 14/03/16.
//
//

#include "Basket.h"
#include "PhysicsShapeCache.h"


Basket::Basket() {
    
}

Basket::~Basket() {
    
}

Basket* Basket::createBasket(bool empty) {
    Basket* newBasket = Basket::create();
    newBasket->init();

    return newBasket;
}


bool Basket::init() {
    std::string name = "basket.png";
    auto basketContainer = Sprite::createWithSpriteFrameName(name);
    PhysicsShapeCache::getInstance()->setBodyOnSprite(name, basketContainer);
    basketContainer->setPosition(Vec2(500,500));
    this->addChild(basketContainer);
    basketContainer->setScale(2.0);
    
    name = "basket_top.png";
    auto basketHolder = Sprite::createWithSpriteFrameName(name);
    PhysicsShapeCache::getInstance()->setBodyOnSprite(name, basketHolder);
    basketHolder->setPosition(Vec2(500,500));
    this->addChild(basketHolder);
    basketHolder->setScale(2.0);
    
    PhysicsJointPin* joint = PhysicsJointPin::construct(basketHolder->getPhysicsBody(), basketContainer->getPhysicsBody(), basketContainer->getContentSize());
    Director::getInstance()->getRunningScene()->getPhysicsWorld()->addJoint(joint);
    
    return true;
}