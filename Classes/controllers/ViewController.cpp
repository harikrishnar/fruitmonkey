//
//  ViewController.cpp
//  teenpatti
//
//  Created by Hari Krishna on 11/20/15.
//
//

#include "ViewController.h"

ViewController::ViewController() {

}

ViewController::~ViewController() {

}

SEL_MenuHandler ViewController::onResolveCCBCCMenuItemSelector(Ref * pTarget, const char* pSelectorName) {

    //assign all menu item handlers to the respective methods here:

    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuTestClicked", ViewController::onMenuTestClicked);


    return NULL;
}

Control::Handler ViewController::onResolveCCBCCControlSelector(Ref * pTarget, const char* pSelectorName) {

    //assign all the control handlers to the respective methods here:
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onControlClicked", ViewController::onControlClicked);

    return NULL;
}

bool ViewController::onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode) {

    //assign all the instance variables to the respective variables of the class:

    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBurstSprite", Sprite *, this->mBurstSprite);

    return false;
}

bool ViewController::onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value) {
    return false;
}

bool ViewController::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    return Layer::onTouchBegan(touch, unused_event);
}

//Vec2 DooberButtons::dooberLocation = Vec2();
//bool DooberButtons::onTouchBegan(Touch *touch, Event *unused_event) {
//    if (touch) {
//        dooberLocation = touch->getLocation();
//    }
//    return Layer::onTouchBegan(touch, unused_event);
//}
//
//Vec2 DooberButtons::getDooberSpawnLocation() {
//    return dooberLocation;
//}