//
// Created by Jason Pacheco on 4/3/24.
//

#ifndef FFG_ENEMY_H
#define FFG_ENEMY_H


#include "Entity.h"

class Enemy : public Entity {
private:
    int x, y;
    int dx, dy;
    int damage;
public:
    Enemy();
    Enemy(int x, int y, int damage, int hp, const std::string& name);

    void movement(int playerX, int playerY);
    void calculateRandomDirection(int playerX, int playerY);

    int getX() const;
    int getY() const;

    int getDamage();
};


#endif //FFG_ENEMY_H
