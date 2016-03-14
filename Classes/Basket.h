//
//  Basket.h
//  fruitmonkey
//
//  Created by Hari Krishna on 14/03/16.
//
//

#ifndef Basket_h
#define Basket_h

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class Basket : public Node
{
public:
	Basket();
	~Basket();
	
	static Basket* createBasket(bool empty = false);
    CREATE_FUNC(Basket);
    virtual bool init() override;
};

#endif /* Basket_h */
