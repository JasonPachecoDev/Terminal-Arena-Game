//
// Created by Jason Pacheco on 4/3/24.
//

#include <cstdlib>
#include "Enemy.h"


Enemy::Enemy() {}

Enemy::Enemy(int x, int y, int damage, int hp, const std::string& name) : Entity(hp, name) {
this->x = x;
this->y = y;
this->damage = damage;
}

void Enemy::movement(int playerX, int playerY) {
    int minX = 0, maxX = 63, minY = 2, maxY = 19;

    x += dx;
    y += dy;

    if (x < minX) x = minX;
    else if (x > maxX) x = maxX;

    if (y < minY) y = minY;
    else if (y > maxY) y = maxY;
}

void Enemy::calculateRandomDirection(int playerX, int playerY) {
    int diffX = playerX - x;
    int diffY = playerY - y;

    if (std::rand() % 2 == 0) {
        if (diffX > 0)
            dx = 1;
        else if (diffX < 0)
            dx = -1;
        else
            dx = 0;

        if (diffY > 0)
            dy = 1;
        else if (diffY < 0)
            dy = -1;
        else
            dy = 0;
    } else {
        dx = std::rand() % 3 - 1;
        dy = std::rand() % 3 - 1;
    }

}

int Enemy::getX() const {
    return x;
}

int Enemy::getY() const {
    return y;
}

int Enemy::getDamage() {
    return damage;
}