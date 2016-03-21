//
//  GameEngine.h
//  fruitmonkey
//
//  Created by Hari Krishna on 20/03/16.
//
//

#ifndef GameEngine_h
#define GameEngine_h

#include <stdio.h>
#include "cocos2d.h"
#include "Game.h"
#include "Stone.h"
#include "HudLayer.h"

class GoodObject;

USING_NS_CC;

class GameEngine
{

protected:
    Game game;
    Sprite arrows;
    int combo;
    int nextBasket = 0;
    Sprite flashes;
    int wave_gems;
    int next_rockfall;
    int shakeOffset;
    int rocks_per_rockfall;
    int waveNum;
    Sprite foods;
    Player* player;
    Stone* rock;
    int f = 0;
    Sprite baskets;
    int timeLeft;
    int rockfall_wave_space;
public:
    Layer* rope;
    HudLayer* hud;
    Sprite* bg;
    static const int INIT_ROCKS_PER_ROCKFALL = 1;
    static const int GROUND = 400;
    static const int GO_DROPPED = 1;
    static const int DELTA_ROCKFALL_SPACE = 30;
    static const int COMBO_LENGTH = 5;
    static const int GEMS_PER_WAVE = 10;
    static const int GO_TIMEUP = 2;
    static const int INIT_ROCKFALL_SPACE = 300;
    static const int MIN_BASKET_SPAWN_INT = 50;
    static const int L_BOUND = 100;
    static const int GRAVITY = 2;
    static const int TIME_LIMIT = 3600;
    static const int R_BOUND = 550;
    static const int COMBO_BONUS = 1000;
    static const int ROCK_Y = 320;
public:
	GameEngine();
	~GameEngine();
    
    void die();
    void shake();
    void nextWave();
    void addFood(GoodObject*);
    void spawnBasket(Node*);
    void gotTimeBonus(int);
    void exitGame();
    void gameLoop(Event*);
    std::vector<Node*> getFoodTouching(Node*);
    void gemCollected();
    void gemSmashed(GoodObject*);
    bool hitBasket(Stone*);
    void gameover(int);
    void updateScore(int);
    void droppedRock();
    void rockfall();
    void gotCombo();
    std::vector<Node*> addArrow(GoodObject*);
    void spawnRocks();
    Game go(Ref*);
    void endCombo();
    void addCombo();
    
};

#endif /* GameEngine_h */
