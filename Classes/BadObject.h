//
//  BadObject.h
//  fruitmonkey
//
//  Created by Hari Krishna on 13/03/16.
//
//

#ifndef BadObject_h
#define BadObject_h

#include <stdio.h>
#include "Object.h"

class BadObject : public Object
{
public:
	BadObject();
	~BadObject();
	
	virtual void create(ObjectType) override;
};

#endif /* BadObject_h */
