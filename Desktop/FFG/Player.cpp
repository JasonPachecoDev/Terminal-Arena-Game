//
// Created by Jason Pacheco on 4/2/24.
//

#include "Player.h"

Player::Player() {}

Player::Player(int hp, const std::string& name) : Entity(hp, name), slingshot(), equippedWeapon(nullptr){
    if (!weaponInventory.empty()) {
        equippedWeapon = &weaponInventory[0];
    }
}

std::vector<Weapon>& Player::getWeaponInventory() {
    return weaponInventory;
}

std::vector<Armor>& Player::getArmorInventory() {
    return armorInventory;
}

void Player::buyWeap(Weapon &weapon) {
    weaponInventory.push_back(weapon);
}

void Player::buyArmor(Armor &armor) {
    armorInventory.push_back(armor);
}


void Player::switchItem(int index) {
    if (index >= 0 && index < weaponInventory.size()) {
        currentIndex = index;
    }
}

void Player::equipWeapon(Weapon& weapon) {
    equippedWeapon = &weapon;
}

void Player::equipArmor(Armor &armor) {
    equippedArmor = &armor;
}

void Player::unEquipWeapon() {
    equippedWeapon = nullptr;
}

Weapon* Player::getEquippedWeapon() {
    return equippedWeapon;
}

bool Player::hasWeapon(const std::string &itemName) {
    for (const auto& item : weaponInventory) {
        if (item.getName() == itemName) {
            return true;
        }
    }
    return false;
}

bool Player::hasArmor(const std::string &itemName) {
    for (const auto& item : armorInventory) {
        if (item.getName() == itemName) {
            return true;
        }
    }
    return false;
}

bool Player::hasRangeBoost() {
    return rangeBoost;
}

bool Player::hasSpeedBoost() {
    return speedBoost;
}

void Player::addRangeBoost() {
    rangeBoost = true;
}

void Player::addSpeedBoost() {
    speedBoost = true;
}

void Player::removeRangeBoost() {
    rangeBoost = false;
}

void Player::removeSpeedBoost() {
    speedBoost = false;
}

