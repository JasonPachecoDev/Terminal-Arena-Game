//
// Created by Jason Pacheco on 4/1/24.
//

#include "Arena.h"
#include "Rifle.h"
#include "Fireball.h"
#include "Cloth.h"
#include "Leather.h"
#include "Chain.h"
#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>


#define COLOR_PAIR_ENEMY 1
#define COLOR_PAIR_BRIGHT_WHITE 3
#define COLOR_PAIR_BRIGHT_GREEN 4

Arena::Arena() {
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    resizeterm(25, 100);
    setscrreg(0, LINES - 1);
    scrollok(stdscr, FALSE);
    store = Store();
    player = Player(10, "Jason");
    enemy = Enemy(20, 20, 25, 10, "Villain");
    boundX = 63, boundY = 20;
}

void Arena::startGame() {
    x = 8, y = 7;
    shotDirection = 0;
    over = false;
    hasToken = true;

    //Token 10 second function
    //std::chrono::steady_clock::time_point lastTokenTime = std::chrono::steady_clock::now();
    //std::chrono::steady_clock::time_point lastMoveTime;

    int ch;
    int input;

    while ((ch = getch()) != '5') {

        clear();


        start_color();
        init_pair(COLOR_PAIR_ENEMY, COLOR_RED, COLOR_BLACK);
        init_pair(COLOR_PAIR_BRIGHT_GREEN, COLOR_GREEN, COLOR_BLACK);

        mvprintw(0,0, "=======================================================================");
        mvprintw(1,0, "| Inventory [1] || Store [2] || Info [3] || Save Game [4] || Quit [5] |");
        mvprintw(2,0, "|---------------------------------------------------------------------|");

        for (int i = 3; i < 20; i++) {
            mvprintw(i,0, "|                                                                     |");
        }

        mvprintw(20,0, "|---------------------------------------------------------------------|");
        if (x == enemy.getX() && y == enemy.getY()) {
            int damage = enemy.getDamage();
            player.takeDamage(damage);
            //mvprintw(20, 10, "You took %d damage from the enemy!", damage);
        }
        mvprintw(21,0, "| Health || Player: %d || Enemy: %d", player.getHP(), enemy.getHP());
        mvprintw(21, 70, "|");
        mvprintw(22,0, "=======================================================================");

        enemy.calculateRandomDirection(x, y);

//Movement
        switch (ch) {
            case KEY_UP:
                if (y > 3 ) {
                    if (player.hasSpeedBoost()) {
                        y -= 2;
                    } else {
                        y--;
                    }
                }
                break;
            case KEY_DOWN:
                if (y < 20 - 1) {
                    if (player.hasSpeedBoost() && y < 20 - 2) {
                        y += 2;
                    } else {
                        y++;
                    }
                }
                break;
            case KEY_LEFT:
                shotDirection = 1;
                if (x > 1) {
                    if (player.hasSpeedBoost() && x > 2) {
                        x -= 2;
                    } else {
                        x--;
                    }
                }
                break;
            case KEY_RIGHT:
                shotDirection = 0;
                if (x < 68) {
                    if (player.hasSpeedBoost()) {
                        x += 2;
                    } else {
                        x++;
                    }
                }
                break;
            case 'w': {
                if (player.getEquippedWeapon() != nullptr) {
                    projectile();
                    break;
                } else {
                    break;
                }
            }
//Inventory
            case '1': {
                bool showInventory = true;
                while (showInventory) {

                    mvprintw(6, 14, "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
                    for (int i = 7; i < 15; i++) {
                        mvprintw(i, 14, "|                                       |");
                    }
                    mvprintw(15, 14, "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
                    mvprintw(7, 30, "Inventory      back [Z]");

                    int lineNo = 9;
                    for (int i = 0; i < player.getWeaponInventory().size(); i++) {
                        mvprintw(lineNo, 16, "[%c] %s", 'A' + i, player.getWeaponInventory()[i].getName().c_str());
                        lineNo++;
                    }
                    if (player.getEquippedWeapon() != nullptr) {
                        mvprintw(lineNo + 2, 16, "Equipped: %s", player.getEquippedWeapon()->getName().c_str());
                        refresh();
                    } else {
                        mvprintw(lineNo + 2, 16, "Equipped: None");
                    }
                    int ch = getch();
                    if (ch >= 'a' && ch <= 'z') {
                        int index = ch - 'a';

                        if (ch == 'z') {
                            for (int i = 6; i <= 15; i++) {
                                mvprintw(i, 14, "                                         ");
                            }
                            showInventory = false;
                            refresh();
                        } else if (ch >= 'a' && ch <= 'z') {
                            int index = ch - 'a';
                            if (index < player.getWeaponInventory().size()) {
                                player.equipWeapon(player.getWeaponInventory()[index]);
                                mvprintw(lineNo + 2, 16, "Equipped: %s", player.getWeaponInventory()[index].getName().c_str());
                                refresh();
                            }
                        }
                    }
                }
                break;
            }
//Store
            case '2': { //STORE
                bool showStore = true;
                while (showStore) {
                    mvprintw(6, 14, "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
                    for (int i = 7; i < 15; i++) {
                        mvprintw(i, 14, "|                                       |");
                    }
                    mvprintw(15, 14, "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
                    mvprintw(7, 32, "Store       back [Z]");

                    mvprintw(9, 16, "Weapons [A]");
                    mvprintw(10, 16, "Armor   [B]");
                    mvprintw(11, 16, "Perks   [C]");

                    mvprintw(14, 16, "Balance: $%d", store.getBalance());

                    int storeOp = getch();

                    if (storeOp == 'z') {
                        for (int i = 6; i <= 15; i++) {
                            mvprintw(i, 14, "                                         ");
                        }
                        showStore = false;
                        refresh();
                    }

                    switch (storeOp) {
                        case 'a': {
    //Weapons
                            bool showWeapons = true;

                            while (showWeapons) {
                                mvprintw(7, 31, "Weapons");
                                mvprintw(9, 16, "Slingshot     $40  [A]");
                                //Check if the weapons have already been purchased
                                for (const auto &weapon: player.getWeaponInventory()) {
                                    //If it has, it is not for sale
                                    if (weapon.getName() == "Slingshot") {
                                        mvprintw(9, 16, "Slingshot     ---Owned");
                                        break;
                                    }
                                }
                                mvprintw(10, 16, "Rifle         $60  [B]");
                                for (const auto &weapon: player.getWeaponInventory()) {
                                    if (weapon.getName() == "Rifle") {
                                        mvprintw(10, 16, "Rifle         ---Owned");
                                        break;
                                    }
                                }
                                mvprintw(11, 16, "Fireball      $90  [C]");
                                for (const auto &weapon: player.getWeaponInventory()) {
                                    if (weapon.getName() == "Fireball") {
                                        mvprintw(11, 16, "Fireball      ---Owned");
                                        break;
                                    }
                                }

                                char purchaseOp = getch();

                                switch (purchaseOp) {
                                    case 'a': {
                                        Slingshot slingshot;
                                        if (player.hasWeapon("Slingshot")) {
                                            break;
                                        } else if (store.getBalance() >= slingshot.getPrice()) {
                                            mvprintw(9, 16, "Slingshot  ---Owned");
                                            player.buyWeap(slingshot);
                                            store.subBalance(slingshot.getPrice());
                                            mvprintw(14, 16, "                                ");
                                            mvprintw(14, 16, "Balance: $%d", store.getBalance());
                                        } else {
                                            mvprintw(14, 31, "*Insufficient balance*");
                                        }
                                        break;
                                    }

                                    case 'b': {
                                        Rifle rifle;
                                        if (player.hasWeapon("Rifle")) {
                                            break;
                                        } else if (store.getBalance() >= rifle.getPrice()) {
                                            mvprintw(10, 16, "Rifle       ---Owned");
                                            player.buyWeap(rifle);
                                            store.subBalance(rifle.getPrice());
                                            refresh();
                                            mvprintw(14, 16, "                                ");
                                            mvprintw(14, 16, "Balance: $%d", store.getBalance());
                                        } else {
                                            mvprintw(14, 31, "*Insufficient balance*");
                                        }
                                        break;
                                    }
                                    case 'c': {
                                        Fireball fireball;
                                        if (player.hasWeapon("Fireball")) {
                                            break;
                                        } else if (store.getBalance() >= fireball.getPrice()) {
                                            mvprintw(11, 16, "| Fireball    ---Owned  ");
                                            player.buyWeap(fireball);
                                            store.subBalance(fireball.getPrice());
                                            refresh();
                                            mvprintw(14, 16, "                                ");
                                            mvprintw(14, 16, "Balance: $%d", store.getBalance());
                                        } else {
                                            mvprintw(14, 31, "*Insufficient funds*");
                                        }
                                        break;
                                    }
                                    case 'z': {
                                        showWeapons = false;
                                    }
                                }
                            }
                            storeOp = NULL;
                        }
                            break;

                        case 'b': {
                            bool showArmor = true;

                                while (showArmor) {
                                    mvprintw(7, 32, "Armor       back [Z]");

                                    if (!player.hasArmor("Cloth")) {
                                        mvprintw(9, 16, "                          ");
                                        mvprintw(9, 16, "Cloth      $15  [A]");
                                    } else {
                                        mvprintw(9, 16, "                          ");
                                        mvprintw(9, 16, "Cloth      ---Owned");
                                    }

                                    if (!player.hasArmor("Leather")) {
                                        mvprintw(10, 16, "                          ");
                                        mvprintw(10, 16, "Leather    $25  [B]");
                                    } else {
                                        mvprintw(10, 16, "                          ");
                                        mvprintw(10, 16, "Leather    ---Owned");
                                    }

                                    if (!player.hasArmor("Chain")) {
                                        mvprintw(11, 16, "                          ");
                                        mvprintw(11, 16, "Chain      $35  [C]");
                                    } else {
                                        mvprintw(11, 16, "                          ");
                                        mvprintw(11, 16, "Chain      ---Owned");
                                    }

                                    int purchaseOp = getch();


                                    switch (purchaseOp) {
                                        case 'a': {
                                            Cloth cloth;
                                            if (player.hasArmor("Cloth")) {
                                                break;
                                            } else if (store.getBalance() >= cloth.getPrice()) {
                                                mvprintw(9, 16, "                          ");
                                                mvprintw(9, 16, "Cloth      ---Owned");
                                                player.setHP(cloth.getHealth());
                                                player.buyArmor(cloth);
                                                store.subBalance(cloth.getPrice());
                                                mvprintw(21,20, "   ");
                                                mvprintw(21,20, "%d", player.getHP());
                                                mvprintw(14, 16, "                                ");
                                                mvprintw(14, 16, "Balance: $%d", store.getBalance());
                                                refresh();
                                            } else {
                                                mvprintw(14, 33, "*Insufficient funds*");
                                            }
                                            break;
                                        }
                                        case 'b': {
                                            Leather leather;
                                            if (player.hasArmor("Leather")) {
                                                break;
                                            } else if (store.getBalance() >= leather.getPrice()) {
                                                mvprintw(10, 16, "                          ");
                                                mvprintw(10, 16, "Leather    ---Owned");
                                                player.setHP(leather.getHealth());
                                                player.buyArmor(leather);
                                                store.subBalance(leather.getPrice());
                                                mvprintw(21,20, "   ");
                                                mvprintw(21,20, "%d", player.getHP());
                                                mvprintw(14, 16, "                                ");
                                                mvprintw(14, 16, "Balance: $%d", store.getBalance());
                                                refresh();
                                            } else {
                                                mvprintw(14, 33, "*Insufficient funds*");
                                            }
                                            break;
                                        }
                                        case 'c': {
                                            Chain chain;
                                            if (player.hasArmor("Chain")) {
                                                break;
                                            } else if (store.getBalance() >= chain.getPrice()) {
                                                mvprintw(11, 16, "                          ");
                                                mvprintw(11, 16, "Chain   ---Owned");
                                                player.setHP(chain.getHealth());
                                                player.buyArmor(chain);
                                                store.subBalance(chain.getPrice());
                                                mvprintw(21,20, "   ");
                                                mvprintw(21,20, "%d", player.getHP());
                                                mvprintw(14, 16, "                                ");
                                                mvprintw(14, 16, "Balance: $%d", store.getBalance());
                                                refresh();
                                            } else {
                                                mvprintw(14, 33, "*Insufficient funds*");
                                            }
                                            break;
                                        }
                                        case 'z': {
                                            showArmor = false;
                                            break;
                                        }
                                    }
                                }
                        }
                        break;
//Perks
                        case 'c': {
                            bool showPerks = true;

                            while (showPerks) {
                                mvprintw(7, 32, "Perks       back [Z]");

                                mvprintw(11, 16, "                          ");

                                if (!player.hasRangeBoost()) {
                                    mvprintw(9, 16, "                          ");
                                    mvprintw(9, 16, "Range      $10  [A]");
                                } else {
                                    mvprintw(9, 16, "                          ");
                                    mvprintw(9, 16, "Range      ---Owned");
                                }

                                if (!player.hasSpeedBoost()) {
                                    mvprintw(10, 16, "                          ");
                                    mvprintw(10, 16, "Speed      $25  [B]");
                                } else {
                                    mvprintw(10, 16, "                          ");
                                    mvprintw(10, 16, "Speed      ---Owned");
                                }


                                int input = getch();

                                switch (input) {
                                    case 'a': {
                                        mvprintw(9, 16, "Range      ---Owned");
                                        store.subBalance(10);
                                        player.addRangeBoost();
                                        mvprintw(14, 16, "                                ");
                                        mvprintw(14, 16, "Balance: $%d", store.getBalance());
                                        refresh();
                                        break;
                                    }
                                    case 'b': {
                                        mvprintw(10, 16, "Speed      ---Owned");
                                        store.subBalance(25);
                                        player.addSpeedBoost();
                                        mvprintw(14, 16, "                                ");
                                        mvprintw(14, 16, "Balance: $%d", store.getBalance());
                                        refresh();
                                        break;
                                    }
                                    case 'z': {
                                        showPerks = false;
                                        break;
                                    }
                                }

                            }
                        }
                        break;
                    }

                }

                break;
            }
            case '3': { //Info
                bool showInfo = true;

                while (showInfo) {
                    mvprintw(6, 14, "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
                    for (int i = 7; i < 15; i++) {
                        mvprintw(i, 14, "|                                       |");
                    }
                    mvprintw(15, 14, "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
                    mvprintw(7, 33, "Info       back [Z]");

                    mvprintw(9, 16, "Controls:");
                    mvprintw(10, 16, "Attack      [W]");
                    mvprintw(11, 16, "Move   [Arrows]");

                    mvprintw(13, 16, "Objective:");
                    mvprintw(14, 16, "Attack the enemy to accumulate money.");

                    //mvprintw(13, 65, "| Credits:");
                    //mvprintw(14, 65, "| Jason Pacheco");
                    char infoOp = getch();
                    if (infoOp == 'z') {
                        for (int i = 6; i <= 15; i++) {
                            mvprintw(i, 14, "                                         ");
                        }
                        showInfo = false;
                        refresh();
                    }

                }
                showInfo = NULL;

                break;
            }

            case '4': {

                bool saveLoadPlayer = true;

                while (saveLoadPlayer) {

                    mvprintw(6, 14, "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
                    for (int i = 7; i < 14; i++) {
                        mvprintw(i, 14, "|                                       |");
                    }
                    mvprintw(14, 14, "|");
                    mvprintw(14, 54, "|");
                    mvprintw(15, 14, "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
                    mvprintw(7, 24, "Save Game Player     back [Z]");

                    mvprintw(10, 16, "Save player   [S]");
                    //mvprintw(11, 16, "Load player   [L]");


                    char input = toupper(getch());

                    if (input == 'S') {

                        std::string fileName = "savedPlayer.txt";
                        std::string data = "Name: Player\nHP: " + std::to_string(player.getHP()) + "\n"
                                           + "Balance: " + std::to_string(store.getBalance()) + "\n"
                                           + "Weapons: ";

                        std::vector<Weapon> weapons = player.getWeaponInventory();
                        for (const Weapon &weapon: weapons) {
                            data += weapon.getName() + ", ";
                        }

                        std::ofstream outFile(fileName);


                        if (outFile.is_open()) {
                            outFile << data;
                            outFile.close();
                            mvhline(14, 16, ' ', 14);
                            mvprintw(14, 16, "*Successfully saved player*  ");
                            refresh();
                        } else {
                            mvprintw(14, 16, "*Failed to save player*");
                            refresh();
                        }
                    }/* else if (input == 'L') {
                        player.resetHP();
                        player.setHP(-100);

                        refresh();
                        std::string fileName = "savedPlayer.txt";
                        std::ifstream inFile(fileName);
                        if (inFile.is_open()) {
                            std::string line;
                            std::getline(inFile, line);

                            std::getline(inFile, line);
                            size_t colonPos = line.find(": ");
                            if (colonPos != std::string::npos) {
                                std::string hpStr = line.substr(colonPos + 2);
                                try {
                                    int hp = std::stoi(hpStr);
                                    player.setHP(hp);
                                } catch (const std::invalid_argument& e) {
                                    mvprintw(14, 16, "*Invalid HP value in file*");
                                    refresh();
                                }
                            } else {
                                mvprintw(14, 16, "*Invalid HP format in file*");
                                refresh();
                            }

                            std::getline(inFile, line);
                            colonPos = line.find(": ");
                            if (colonPos != std::string::npos) {
                                std::string balanceStr = line.substr(colonPos + 2);
                                try {
                                    int balance = std::stoi(balanceStr);
                                    store.setBalance(balance);
                                } catch (const std::invalid_argument& e) {
                                    mvprintw(14, 16, "*Invalid Balance value in file*");
                                    refresh();
                                }
                            } else {
                                mvprintw(14, 16, "*Invalid Balance format in file*");
                                refresh();
                            }

                            std::getline(inFile, line);
                            colonPos = line.find(": ");
                            if (colonPos != std::string::npos) {
                                std::string weaponsStr = line.substr(colonPos + 2);
                                std::istringstream iss(weaponsStr);
                                std::vector<Weapon> weapons;
                                std::string token;
                                while (std::getline(iss, token, ',')) {
                                    if (!token.empty()) {
                                        player.getWeaponInventory().emplace_back(token, 0);
                                    }
                                }
                            } else {
                                mvprintw(14, 16, "*Invalid Weapons format in file*");
                                refresh();
                            }

                            inFile.close();

                            mvprintw(21, 20, "  ");
                            mvprintw(21, 19, " %d ", player.getHP());

                            mvhline(14, 16, ' ', 14);
                            mvprintw(14, 16, "*Successfully loaded player* ");
                            refresh();
                        }
                    }*/ else if (input == 'Z') {

                        for (int i = 6; i <= 15; i++) {
                            mvprintw(i, 14, "                                         ");
                        }
                        saveLoadPlayer = false;
                        refresh();
                    }
                }
                input = NULL;

                break;
            }

            case '5': {
                over = true;
                break;
            }
        }
        attron(COLOR_PAIR(COLOR_PAIR_BRIGHT_GREEN));
        mvaddch(y, x, '*');
        attroff(COLOR_PAIR(COLOR_PAIR_BRIGHT_GREEN));

        enemy.movement(x, y);

        attron(COLOR_PAIR(COLOR_PAIR_ENEMY));
        mvaddch(enemy.getY(), enemy.getX(), 'X');
        attroff(COLOR_PAIR(COLOR_PAIR_ENEMY));

        if (player.isDead() == true) {
            clear();

            mvprintw(4, 14, "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
            for (int i = 5; i < 13; i++) {
                mvprintw(i, 14, "|                                       |");
            }
            mvprintw(13, 14, "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
            mvprintw(5, 26, "You were defeated.");

            mvprintw(8, 22, "=-=-=-=-=-=-=-=-=-=-=-=-=");
            mvprintw(9, 22,"|   Continue [return]   |");
            mvprintw(10, 22, "=-=-=-=-=-=-=-=-=-=-=-=-=");

            mvprintw(15, 14, "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
            mvprintw(16, 14, "|        Credits:   Jason Pacheco       |");
            mvprintw(17, 14, "|        Website:   jasonpache.co       |");
            mvprintw(18, 14, "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");

            int ch = getch();
            if (ch == '\n' || ch == '\r') {
                break;
            }

            over = true;
        } else if (enemy.isDead() == true) {
            clear();

            mvprintw(4, 14, "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
            for (int i = 5; i < 13; i++) {
                mvprintw(i, 14, "|                                       |");
            }
            mvprintw(13, 14, "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
            mvprintw(5, 23, "You defeated the enemy!");

            mvprintw(8, 22, "=-=-=-=-=-=-=-=-=-=-=-=-=");
            mvprintw(9, 22,"|   Continue [Return]   |");
            mvprintw(10, 22, "=-=-=-=-=-=-=-=-=-=-=-=-=");

            mvprintw(15, 14, "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
            mvprintw(16, 14, "|        Credits:   Jason Pacheco       |");
            mvprintw(17, 14, "|        Website:   jasonpache.co       |");
            mvprintw(18, 14, "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");

            int ch = getch();
            if (ch == '\n' || ch == '\r') {
                break;
            }

            over = false;
        }

        refresh();
    }

    endwin();
}

bool Arena::getState() {
    return over;
}

void Arena::projectile() {
    attron(COLOR_PAIR(COLOR_PAIR_BRIGHT_GREEN));
    mvaddch(y, x, '*');
    attroff(COLOR_PAIR(COLOR_PAIR_BRIGHT_GREEN));

    attron(COLOR_PAIR(COLOR_PAIR_ENEMY));
    mvaddch(enemy.getY(), enemy.getX(), 'X');
    attroff(COLOR_PAIR(COLOR_PAIR_ENEMY));

    int projPosX = x;
    int projPosY = y;
    int z = 0;

    if (shotDirection == 0) {
    projPosX = x + 1;
    }
    if (shotDirection == 1) {
    projPosX = x - 1;
    }

    int i;

    if (player.hasRangeBoost()) {
        i = 16;
    } else {
        i = 8;
    }

    while (z < i && projPosX != enemy.getX()) {
        usleep(100000);
        move(projPosY, projPosX);
        addch(' ');

        if(shotDirection == 0) {
            projPosX++;
        } else {
        projPosX--;
        }
        move(projPosY, projPosX);

        if (player.getEquippedWeapon()->getName() == "Slingshot") {
            addch('+');
        } else if (player.getEquippedWeapon()->getName() == "Rifle") {
            addch('-');
        } else if (player.getEquippedWeapon()->getName() == "Fireball") {
            addch('@');
        } else {
            addch('+');
        }
        refresh();

        if (projPosX == enemy.getX() && projPosY == enemy.getY()) {
            enemy.takeDamage(player.getEquippedWeapon()->getDamage());
            store.addBalance(15);
            //mvprintw(20, 10, "You dealt %d damage to the enemy!", player.getEquippedWeapon()->getDamage());
        }
        if (projPosX < 0 || projPosX > 64) {
            refresh();
            break;
        }

        z++;
        }
}

void Arena::tokens() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(0, boundX - 1);
    std::uniform_int_distribution<> distY(4, boundY - 1);

    tokenXCord = distX(gen);
    tokenYCord = distY(gen);

    mvprintw(tokenYCord, tokenXCord, "$");
}

void Arena::restartGame() {
    player.resetHP();
    player.removeSpeedBoost();
    player.removeRangeBoost();
    player.unEquipWeapon();
    enemy.resetHP();

    player.getWeaponInventory().clear();
    player.getWeaponInventory().shrink_to_fit();
    player.getArmorInventory().clear();
    player.getArmorInventory().shrink_to_fit();

    store.resetBalance();
}



