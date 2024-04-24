//
// Created by Jason Pacheco on 3/29/24.
//

#include <iostream>
#include "Store.h"

Store::Store(){
}

void Store::displayWeapons() {
    for ( auto& weapon : weapons) {
        std::cout << weapon.getName() << std::endl;
    }
}

int Store::getBalance() {
    return balance;
}

void Store::subBalance(int cost) {
    balance = balance - cost;
}

void Store::addBalance(int money) {
    balance = balance + money;
}

void Store::resetBalance() {
    balance = 40;
}

void Store::setBalance(int balance) {
    this->balance = balance;
}