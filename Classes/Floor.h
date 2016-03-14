//
//  Floor.h
//  fruitmonkey
//
//  Created by Hari Krishna on 13/03/16.
//
//

#ifndef Floor_h
#define Floor_h

#include <stdio.h>
#include "Object.h"

class Floor : public Object
{
public:
	Floor();
	~Floor();
	
	virtual void create(ObjectType) override;
};

#endif /* Floor_h */
