cmake_minimum_required(VERSION 3.27)
project(FFG)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(FFG main.cpp Arena.cpp
        Store.cpp
        Store.h
        Weapon.cpp
        Weapon.h
        Slingshot.cpp
        Slingshot.h
        Arena.cpp
        Arena.h
        Entity.cpp
        Entity.h
        Player.cpp
        Player.h
        Enemy.cpp
        Enemy.h
        Rifle.cpp
        Rifle.h
        Fireball.cpp
        Fireball.h
        Armor.cpp
        Armor.h
        Cloth.cpp
        Cloth.h
        Leather.cpp
        Leather.h
        Chain.cpp
        Chain.h
)
target_link_libraries(FFG ${CURSES_LIBRARIES})
