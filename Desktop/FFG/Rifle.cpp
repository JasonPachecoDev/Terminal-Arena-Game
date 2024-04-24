//
// Created by Jason Pacheco on 4/12/24.
//

#include "Rifle.h"

Rifle::Rifle() : Weapon("Rifle", 60){
damage = 20;
}

int Rifle::shoot() {
    return damage;
}