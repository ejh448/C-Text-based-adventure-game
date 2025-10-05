#ifndef ENEMY_H
#define ENEMY_H
#include <string>
using namespace std;

struct Enemy {
    string names[3] = {
        "Goblin",
        "Ghoul",
        "Skeleton"
    };
    int health = 100;
    int level = 1;
    int gold = 10;

    int enemy_attack(int random_number)
    {
        return random_number % ((health / 2) - 1) + (level * .13);
    }
};


#endif