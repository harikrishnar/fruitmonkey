//
//  GoodObject.h
//  fruitmonkey
//
//  Created by Hari Krishna on 13/03/16.
//
//

#ifndef GoodObject_h
#define GoodObject_h

#include <stdio.h>
#include "Object.h"

class GoodObject : public Object
{
public:
	GoodObject();
	~GoodObject();
	
	virtual void create(ObjectType) override;
};

#endif /* GoodObject_h */
