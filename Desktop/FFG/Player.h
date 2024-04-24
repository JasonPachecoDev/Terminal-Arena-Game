//
// Created by Jason Pacheco on 4/2/24.
//

#ifndef FFG_PLAYER_H
#define FFG_PLAYER_H

#include <vector>
#include <iostream>
#include "Armor.h"
#include "Weapon.h"
#include "Entity.h"
#include "Slingshot.h"


class Player : public Entity {
private:
    std::vector<Weapon> weaponInventory;
    std::vector<Armor> armorInventory;
    int x, y;
    int currentIndex;
    Weapon* equippedWeapon;
    Armor* equippedArmor;
    Slingshot slingshot;
    bool speedBoost;
    bool rangeBoost;
public:
    Player();
    Player(int hp, const std::string& name);


    void switchItem(int index);

    void buyWeap(Weapon& weapon);
    void buyArmor(Armor& armor);

    void equipWeapon(Weapon& weapon);
    void equipArmor(Armor& armor);

    void unEquipWeapon();

    Weapon* getEquippedWeapon();
    Armor* getEquippedArmor();

    bool hasWeapon(const std::string& itemName);
    bool hasArmor(const std::string& itemName);

    std::vector<Weapon>& getWeaponInventory();
    std::vector<Armor>& getArmorInventory();

    bool hasSpeedBoost();
    bool hasRangeBoost();

    void addSpeedBoost();
    void addRangeBoost();
    void removeSpeedBoost();
    void removeRangeBoost();

};


#endif //FFG_PLAYER_H
