#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using namespace std;
/*
    Using a struct allows to keep similar things together
    such as a player.
*/
struct Player {
    //setting base values
    string name;
    int xp = 0;
    int level = 1;
    int health = 100;
    int player_x = 0;
    int player_y = 0;
    int gold = 100;
    int potions = 5;
};

#endif