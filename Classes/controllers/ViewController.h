//
//  ViewController.h
//  teenpatti
//
//  Created by Hari Krishna on 11/20/15.
//
//

#ifndef ViewController_h
#define ViewController_h

#include <stdio.h>
#include "cocos2d.h"
#include "cocosbuilder/CocosBuilder.h"
#include "ui/CocosGUI.h"
#include "JsonController.h"
//#include "SharpLabelTTF.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

#define CREATE_CCB_METHODS(ClassName) \
public: \
ClassName(); \
~ClassName(); \
CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ClassName, create); \
virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref *pTarget, const char* pSelectorName) override; \
virtual Control::Handler onResolveCCBCCControlSelector(Ref *pTarget, const char* pSelectorName) override; \
virtual bool onAssignCCBMemberVariable(Ref* pTarget, const char* pMemberVariableName, Node* pNode) override; \
virtual bool onAssignCCBCustomProperty(Ref* target, const char* pMemberVariableName, const cocos2d::Value& value) override;


#define CC_CREATE_LOADER_FOR_CCBI(loaderClassName, className)\
class loaderClassName : public LayerLoader {\
public:\
CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(loaderClassName, loader);\
protected:\
CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(className);\
};

class ViewController : public cocos2d::Layer,
public CCBMemberVariableAssigner,
public CCBSelectorResolver {
    CREATE_CCB_METHODS(ViewController);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;

//    subclass should have these two lines
//    inside class:
//    CREATE_CCB_METHODS(classname);

//    outside class:
//    CC_CREATE_LOADER_FOR_CCBI(classnameLoader, classname);
};

#endif /* ViewController_h */
