//
// Created by Jason Pacheco on 4/1/24.
//

#ifndef FFG_ARENA_H
#define FFG_ARENA_H

#include "Store.h"
#include "Weapon.h"
#include "Player.h"
#include "Enemy.h"


class Arena {
private:
    Store store;
    Player player;
    Enemy enemy;

    int x,y;
    int boundX, boundY;
    int tokenXCord, tokenYCord;
    int shotDirection;
    bool over;
    bool hasToken;
public:
    Arena();
    void startGame();
    void restartGame();

    bool getState();
    void projectile();
    void tokens();
};


#endif //FFG_ARENA_H
