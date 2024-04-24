#include <iostream>
#include <ncurses.h>
#include "Arena.h"
#include "Slingshot.h"
#include "Store.h"
#include <ncurses.h>

#define COLOR_PAIR_BRIGHT_RED_BG 1

int main() {
    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);

    Arena arena;

    int boundX = 63, boundY = 20;
    int maxRows, maxCols;
    bool validWindowSize = false;
    getmaxyx(stdscr, maxRows, maxCols);

    while (true) {

        if (maxRows <= boundY && maxCols <= boundX) {

            start_color();
            init_color(COLOR_RED, 1000, 0, 0);
            init_pair(COLOR_PAIR_BRIGHT_RED_BG, COLOR_WHITE, COLOR_RED);
            bkgd(COLOR_PAIR(COLOR_PAIR_BRIGHT_RED_BG));
            mvprintw(10, 34, "RESIZE THE WINDOW");

            refresh();
        }

        clear();

        mvprintw(0,0, "=======================================================================");
        mvprintw(1,0, "|    ___         _                  ___ _      _   _   _              |\n"
                      "|   | __|_ _ _ _| |_ __ _ ____  _  | __(_)__ _| |_| |_(_)_ _  __ _    |\n"
                      "|   | _/ _` | ' \\  _/ _` (_-< || | | _|| / _` | ' \\  _| | ' \\/ _` |   |\n"
                      "|   |_|\\__,_|_||_\\__\\__,_/__/\\_, | |_| |_\\__, |_||_\\__|_|_||_\\__, |   |\n"
                      "|    / __|__ _ _ __  ___     |__/        |___/               |___/    |\n"
                      "|   | (_ / _` | '  \\/ -_)                                             |\n"
                      "|    \\___\\__,_|_|_|_\\___|                                             |\n"
                      "|                                                                     |\n"
                      "|                                                                     |\n"
                      "|                                                                     |\n"
                      "|                                                                     |\n"
                      "|                                                                     |\n"
                      "|                                                                     |\n"
                      "|        ================                    =================        |\n"
                      "|        | New Game [N] |                    | Load Game [L] |        |\n"
                      "|        ================                    =================        |\n"
                      "|                                                                     |\n"
                      "|                                                                     |\n"
                      "|                                                                     |\n"
                      "|                                                                     |\n"
                      "|                                                                     |\n");
        mvprintw(22,0, "=======================================================================");
        refresh();

        char input = toupper(wgetch(stdscr));
        bool cont = arena.getState();

        if (input == 'N') {

            arena.restartGame();
            arena.startGame();
            refresh();

            if (!cont) {
                input = NULL;
            }
        } else if (input == 'L') {

            arena.startGame();
            refresh();

            if (!cont) {
                input = NULL;
            }
        }


    }


    //arena.startGame();
    endwin();
    return 0;
}
