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

    void level_up() 
    {
        if (xp >= 10 * level)
        {
            xp -= 10 * level;
            level++;
            cout << "You have leveled up!" << level << "\n";
        }
    }

    void player_heal() 
    {
           if (potions > 0)
                {
                    health += 25;
                    potions -= 1;
                    if (health > 100)
                    {
                        health = 100;
                    }
                }
            else if (potions <= 0)
            {
                cout << "You are unfortunately out of POTIONS...\n";
                this_thread::sleep_for(3s);
            } 
    }

    int player_attack(int random_number)
    {
        return random_number % ((health / 2) - 1) + (level * .13);
    }

    void xp_gain(int random_factor, int enemy_level)
    {
        xp += level * (enemy_level * 0.10) * random_factor;
        level_up();
    }
};

#endif