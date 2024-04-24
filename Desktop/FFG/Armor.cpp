//
// Created by Jason Pacheco on 4/16/24.
//

#include "Armor.h"

Armor::Armor(int health, std::string name, int price) : health(health), name(name), price(price) {

}

std::string Armor::getName() const{
    return name;
}

int Armor::getHealth() {
    return health;
}

int Armor::getPrice() {
    return price;
}

int Armor::apply() {
    return health;
}