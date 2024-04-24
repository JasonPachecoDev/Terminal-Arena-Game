//
// Created by Jason Pacheco on 4/2/24.
//

#ifndef FFG_ENTITY_H
#define FFG_ENTITY_H


#include <string>

class Entity {
private:
    int hp;
    std::string name;
    bool dead;
public:
    Entity();
    Entity(int hp, const std::string& name);

    int getHP();
    void setHP(int addHp);
    void resetHP();
    void takeDamage(int damage);
    bool isDead();
};


#endif //FFG_ENTITY_H
