//
// Created by Jason Pacheco on 3/29/24.
//

#include "Weapon.h"

Weapon::Weapon(std::string name, int price) : name(name), price(price) {

}

std::string Weapon::getName() const{
    return name;
}

int Weapon::getDamage() {
    return damage;
}

int Weapon::getPrice() {
    return price;
}