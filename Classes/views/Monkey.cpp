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
    
    return monkey;
}

bool Monkey::init() {
    this->currentState = AnimationType::NONE;
    _image = nullptr;
    currentXValue = 0.5;
//    _image = Sprite::createWithSpriteFrameName("throw/monkey0001.png");
//    this->addChild(_image);
    auto monkeyBody = PhysicsShapeCache::getInstance()->createBodyWithName("monkey");
    this->setPhysicsBody(monkeyBody);
    auto screenSize = Director::getInstance()->getWinSize();
    this->setPosition(screenSize.width/2.0, 120);
    monkeyBody->setRotationEnable(false);
    monkeyBody->setDynamic(false);
    this->setName("monkey");
    this->playAnimation(AnimationType::IDLE);
    
    return true;
}


#define kFilteringFactor 0.1

void Monkey::walk(float val) {
//    CCLOG("hari value received is %f",val);
//    val = val+100;
//    if (fabs(val) < 0.2) {
//        return;
//    }
//    val = val*100;
//    val = val+100.0;
//    if (fabs(val - currentXValue) > 20) {
//        if (val > currentXValue) {
//            this->playAnimation(AnimationType::RIGHT_RUN);
//        } else {
//            this->playAnimation(AnimationType::LEFT_RUN);
//        }
//        currentXValue = val;
//    }
//
//    auto screenSize = Director::getInstance()->getWinSize();
//    this->stopActionByTag(99);
//    MoveTo* move = MoveTo::create(0.1, Point(screenSize.width*val/200.0, this->getPositionY()));
//    move->setTag(99);
//    this->runAction(move);
//    this->setPositionX(screenSize.width*val/200.0);
    
    currentXValue = (val * kFilteringFactor) + (currentXValue * (1.0 - kFilteringFactor));
    
    float accelX = val - currentXValue;
    
    float deceleration = 0.10f;
    float sensitivity = 70.0f;
    
    parallaxVelocity.x = parallaxVelocity.x * deceleration + accelX *sensitivity;
    if (parallaxVelocity.x < 0) {
        this->playAnimation(LEFT_RUN);
    } else {
        this->playAnimation(RIGHT_RUN);
    }
}

void Monkey::playAnimation(AnimationType type) {
    if (this->currentState == type) {
        return;
    }
    float flip = false;
    std::string name = "";
    switch (type) {
        case IDLE:
            name = "throw";
            break;
        case LEFT_RUN:
            name = "run";
            break;
        case RIGHT_RUN:
            flip = true;
            name = "run";
            break;
        case HIT:
            name = "fall";
            break;
        case THROW:
            name = "throw";
            break;
        default:
            break;
    }
    if ((this->currentState == LEFT_RUN && type == RIGHT_RUN) ||
        (this->currentState == RIGHT_RUN && type == LEFT_RUN)) {
            _image->setFlippedX(!_image->isFlippedX());
            this->currentState = type;
            return;
    }
    this->currentState = type;
    if (_image) {
        _image->stopAllActions();
        _image->removeFromParent();
        _image = nullptr;
    }
    
    auto frames = getAnimation(name);
    _image = Sprite::createWithSpriteFrame(frames.front());
    this->addChild(_image);
    
    auto animation = Animation::createWithSpriteFrames(frames, 1.0f/30);
    _image->runAction(RepeatForever::create(Animate::create(animation)));
    _image->setFlippedX(flip);
}

Vector<SpriteFrame*> Monkey::getAnimation(std::string prefix)
{
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    char str[100];
    std::string fullName = prefix + "/monkey%04d.png";
    sprintf(str, fullName.c_str(), 1);
    for(int i = 2; spritecache->getSpriteFrameByName(str); i++)
    {
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
        sprintf(str, fullName.c_str(), i);
    }
    return animFrames;
}

void Monkey::update(float dt) {
    Node::update(dt);
    
    this->setPositionX(this->getPositionX() + parallaxVelocity.x);
    
    CCLOG("value change hari %f", this->getPositionX());
    
//    var _loc_2:* = NaN;
//    var _loc_3:* = null;
//    var _loc_5:* = null;
//    var _loc_7:* = NaN;
//    if (frozen > 0)
//    {
//        var _loc_9:* = frozen - 1;
//        frozen = _loc_9;
//        rock.update(param1);
//        if (frozen == 0)
//        {
//            freezeAnim = false;
//            allowMove = true;
//            rock.alpha = 1;
//            rock.visible = true;
//            gotoAndStop("idle");
//        }
//        return;
//    }
//    _loc_2 = BUF_STD;
//    _loc_3 = "run";
//    if (allowMove)
//    {
//        _loc_7 = x;
//        x = x + (engine.mouseX - x) / _loc_2;
//        x = x < Engine.L_BOUND ? (Engine.L_BOUND) : (x > Engine.R_BOUND ? (Engine.R_BOUND) : (x));
//        if (Math.abs(x - _loc_7) > 0.1)
//        {
//            if (!freezeAnim)
//            {
//                gotoAndStop(_loc_3);
//            }
//            if (x - _loc_7 < 0)
//            {
//                scaleX = 1;
//            }
//            else
//            {
//                scaleX = -1;
//            }
//        }
//        else if (!freezeAnim)
//        {
//            gotoAndStop("idle");
//        }
//    }
}

Monkey::Monkey() {
    
}

Monkey::~Monkey() {
    
}