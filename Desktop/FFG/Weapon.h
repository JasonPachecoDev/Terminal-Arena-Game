//
// Created by Jason Pacheco on 3/29/24.
//

#ifndef FFG_WEAPON_H
#define FFG_WEAPON_H


#include <string>

class Weapon {
protected:
    int damage;
    std::string name;
    int price;
public:
    Weapon(std::string name, int price);

    std::string getName() const;
    int getDamage();
    int getPrice();
};


#endif //FFG_WEAPON_H
