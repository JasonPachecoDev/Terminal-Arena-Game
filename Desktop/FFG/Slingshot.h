//
// Created by Jason Pacheco on 3/29/24.
//

#ifndef FFG_SLINGSHOT_H
#define FFG_SLINGSHOT_H


#include "Weapon.h"
#include "Enemy.h"

class Slingshot : public Weapon {
private:
    int projectileX, projectileY;
    int projectileDX, projectileDY;
    Enemy* enemy;
public:
    Slingshot();
    int sling();
    void updateProjectile(int& projectileX, int& projectileY);
};


#endif //FFG_SLINGSHOT_H
