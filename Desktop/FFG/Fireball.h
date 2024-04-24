//
// Created by Jason Pacheco on 4/15/24.
//

#ifndef FFG_FIREBALL_H
#define FFG_FIREBALL_H

#include "Weapon.h"
#include "Enemy.h"

class Fireball : public Weapon{
private:
    int projectileX, projectileY;
    int projectileDX, projectileDY;
    Enemy* enemy;
public:
    Fireball();
    int burn();
    void updateProjectile(int& projectileX, int& projectileY);
};


#endif //FFG_FIREBALL_H
