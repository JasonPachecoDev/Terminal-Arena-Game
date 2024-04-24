//
// Created by Jason Pacheco on 3/29/24.
//

#ifndef FFG_STORE_H
#define FFG_STORE_H

#include "Weapon.h"
#include "Slingshot.h"
#include "Player.h"

#include <vector>


class Store {
private:
    int balance = 40;
    std::vector<Weapon> weapons;
    bool owned;
public:
    Store();

    void displayWeapons();

    int getBalance();
    void subBalance(int cost);
    void addBalance(int money);
    void resetBalance();
    void setBalance(int balance);
};


#endif //FFG_STORE_H
