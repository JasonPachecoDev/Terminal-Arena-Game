//
// Created by Jason Pacheco on 4/16/24.
//

#ifndef FFG_ARMOR_H
#define FFG_ARMOR_H

#include <string>


class Armor {
protected:
    int health;
    std::string name;
    int price;
public:
    Armor(int health, std::string name, int price);

    std::string getName() const;
    int getHealth();
    int getPrice();

    int apply();
};


#endif //FFG_ARMOR_H
