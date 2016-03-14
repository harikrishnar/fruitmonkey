//
//  Monkey.cpp
//  fruitmonkey
//
//  Created by Hari Krishna on 13/03/16.
//
//

#include "Monkey.h"
#include "PhysicsShapeCache.h"

Monkey* Monkey::createMonkey() {
    Monkey* monkey = Monkey::create();
    monkey->init();
    
    return monkey;
}

bool Monkey::init() {
    _image = Sprite::createWithSpriteFrameName("run/monkey0002.png");
    auto monkeyBody = PhysicsShapeCache::getInstance()->createBodyWithName("monkey");
    _image->setPhysicsBody(monkeyBody);
    _image->setPosition(500, 80);
    monkeyBody->setRotationEnable(false);
    _image->setName("monkey");
    _image->setScale(2.5);
    this->addChild(_image);
    
    return true;
}

Monkey::Monkey() {
    
}

Monkey::~Monkey() {
    
}