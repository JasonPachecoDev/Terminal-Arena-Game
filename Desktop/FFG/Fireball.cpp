//
// Created by Jason Pacheco on 4/15/24.
//

#include "Fireball.h"

Fireball::Fireball() : Weapon("Fireball", 90){
damage = 30;
}

int Fireball::burn() {
    return damage;
}