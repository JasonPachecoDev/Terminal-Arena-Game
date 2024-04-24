//
// Created by Jason Pacheco on 4/12/24.
//

#ifndef FFG_RIFLE_H
#define FFG_RIFLE_H


#include "Weapon.h"
#include "Enemy.h"

class Rifle : public Weapon {
private:
    int projectileX, projectileY;
    int projectileDX, projectileDY;
    Enemy* enemy;
public:
    Rifle();
    int shoot();
    void updateProjectile(int& projectileX, int& projectileY);
};


#endif //FFG_RIFLE_H
