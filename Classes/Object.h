//
//  Object.h
//  fruitmonkey
//
//  Created by Hari Krishna on 13/03/16.
//
//

#ifndef Object_h
#define Object_h

#include <stdio.h>
#include "cocos2d.h"

enum ObjectType
{
	GOOD = 0,
	BAD,
	NEUTRAL,
	TIME,
	BONUS,
	COIN,
    STATIC
};

class Object
{
public:
	Object();
	~Object();
	
protected:
	bool isStatic;
    bool usePhysics;

	virtual void create(ObjectType) = 0;
};

#endif /* Object_h */
