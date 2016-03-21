//
//  Monkey.h
//  fruitmonkey
//
//  Created by Hari Krishna on 13/03/16.
//
//

#ifndef Monkey_h
#define Monkey_h

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

enum AnimationType
{
    NONE = 0,
	IDLE,
	LEFT_RUN,
	RIGHT_RUN,
	HIT,
	THROW
};

class Monkey : public Node
{
    
private:
    Sprite* _image;
    AnimationType currentState;
    Animation* runningAnimation;
    Vector<SpriteFrame*> getAnimation(std::string);
    float currentXValue;
    Point parallaxVelocity;
public:
	Monkey();
	~Monkey();
	
	static Monkey* createMonkey();
	void playAnimation(AnimationType);
    void walk(float);
    void update(float) override;
    
    virtual bool init() override;
    
    CREATE_FUNC(Monkey);
    
};

#endif /* Monkey_h */
