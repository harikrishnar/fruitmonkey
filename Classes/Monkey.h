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
	IDLE = 0,
	LEFT_RUN,
	RIGHT_RUN,
	HIT,
	THROW
};

class Monkey : public Node
{
    
private:
    Sprite* _image;
public:
	Monkey();
	~Monkey();
	
	static Monkey* createMonkey();
	void playAnimation(AnimationType);
    
    virtual bool init();
    
    CREATE_FUNC(Monkey);
    
};

#endif /* Monkey_h */
