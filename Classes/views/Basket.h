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
#include "GameEngine.h"

class Basket : public Node
{

protected:
    Sprite* contents;
    GameEngine* engine;
    int state = 1;
    int swing;
public:
    Layer* inner;
    static const int MAX_FOODS = 6;
    static const int INIT_BASE_SPEED = 2;
//    static int WAVE_DELTA = 1;
//    static const Array HIT_ANIMS = ["hit1", "hit2"];
//    static Array POSSIBLE_ITEMS = BAD_FOODS.concat(FOODS, FOODS, FOODS, FOODS, FOODS, FOODS, FOODS, BAD_FOODS, FOODS, FOODS, FOODS, BAD_FOODS, FOODS, FOODS, FOODS, BAD_FOODS, FOODS, FOODS, FOODS, BAD_FOODS, "bonusRock", "bonusRock", "timeBonus", "timeBonus");
//    static const Array BAD_FOODS = ["badBoulder1", "badBoulder2", "badBoulder3"];
//    static const Object SCORES = {gem1:100, gem2:200, gem3:300, gem4:500, badBoulder1:0, badBoulder2:0, badBoulder3:0, bonusRock:0, timeBonus:0};
//    static const int STATE_HIT = 2;
//    static int SPEED = 0;
//    static const int BOTTOM = 40;
//    static const int STATE_OK = 1;
//    static const Array FOODS = ["gem1", "gem2", "gem3", "gem4"];
//    static int BASE_SPEED = 2;
//    static var prng:PM_PRNG = new PM_PRNG();
//    static const int MAX_X = 700;

public:
	Basket();
	~Basket();

    Basket(GameEngine*);
    void die();
    bool update(int);
    bool hit();
    void endHit();
    void nextWave();
    void reset();
	
	static Basket* createBasket(bool empty = false);
    CREATE_FUNC(Basket);
    virtual bool init() override;
};

#endif /* Basket_h */
