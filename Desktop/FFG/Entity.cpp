//
// Created by Jason Pacheco on 4/2/24.
//

#include "Entity.h"

Entity::Entity() {};

Entity::Entity(int hp, const std::string& name)
        : hp(hp), name(name) {}

void Entity::takeDamage(int damage) {
    hp = hp - damage;
}

int Entity::getHP() {
    return hp;
}

void Entity::setHP(int addHp) {
    this->hp = hp + addHp;
}

bool Entity::isDead(){
    if (hp <= 0) {
        return dead = true;
    } else {
        return dead = false;
    }
}

void Entity::resetHP() {
    hp = 100;
}

