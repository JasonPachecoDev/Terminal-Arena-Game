//
// Created by Jason Pacheco on 3/29/24.
//

#include "Slingshot.h"

Slingshot::Slingshot() : Weapon("Slingshot", 40){
    damage = 10;
}

int Slingshot::sling() {
    return damage;
}
