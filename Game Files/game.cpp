#include <iostream>
#include <string>
//#include <vector>
//for system clear
#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>

#include "Game_Dialogue.h"
#include "Player.h"
#include "Enemy.h"
#include "Text_Colors.h"
#include "MapDesigner.h"
//can use this so you do not have to
//write std::string every time
//or all std
using namespace std;
using namespace std::chrono_literals;

void clearScreen()
{
    system("clear");
}

void animateDots(int count = 3, int delay = 500) {
    for (int i = 0; i < count; i++) {
        cout << ".";
        cout.flush();                // force output immediately
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
    cout << "\n";
}

void Fight(Player &p)
{
    Enemy enemy;
    TextColors text_colors; 
    int monster_type = (rand() % 3);
    int fight_end = 0;

    //could add leveling system and balance for fight here..

    cout << p.name << " you are FACE TO FACE with a " << text_colors.red << enemy.names[monster_type] << "\n";
    this_thread::sleep_for(3s);
    clearScreen();
    string move;
    while (!fight_end)
    {
        
       
        cout << text_colors.default_color << enemy.names[monster_type] << "s" << text_colors.red << " HEALTH: " << enemy.health << "\n";
        cout << "YOUR HEALTH: " << text_colors.cyan  << p.health << "\n" << text_colors.default_color;
        cout << "OPTIONS:\n* Attack\n* Heal\n* Run\nPlease enter your move: ";
        cin >> move;
        cout << "\n";
        
            if (move == "attack")
            {
                int attack = p.player_attack(rand());
                cout << "You Damaged the " << enemy.names[monster_type] << " " << text_colors.red << attack << text_colors.default_color << " points...\n";
                enemy.health -=  p.player_attack(rand());
                this_thread::sleep_for(1.5s);
                if (enemy.health > 0)
                {
                    cout << "The enemy is attacking";
                    animateDots();
                    int enemy_attack = enemy.enemy_attack(rand());
                    cout << "The " << enemy.names[monster_type] << " attacked!\nDoing " << text_colors.cyan << enemy_attack << text_colors.default_color << " damage!\n";
                    p.health -= enemy_attack;
                }
                else if (enemy.health <= 0)
                {
                    cout << "You have won the fight!!! \n";
                    int randomFactor = rand() % 99 + 1;
                    p.xp_gain(randomFactor, p.level);
                    cout << "HERE IS YOUR XP " << text_colors.cyan << p.xp << text_colors.default_color << "\n";
                    this_thread::sleep_for(5s);
                    fight_end = 1;
                }
                else if (p.health <= 0)
                {
                    cout << "UNFORTUNATELY YOU HAVE LOST THE FIGHT\n";
                    this_thread::sleep_for(5s);
                    fight_end = 1;
                }
                this_thread::sleep_for(3s);
            }
            else if (move == "heal")
            {
                p.player_heal();
            }
            else if (move == "run")
            {
                if (enemy.health > 45)
                {
                    cout << text_colors.red << "Sorry you cannot run..\n This enemy is TOO powerful...\n";
                    this_thread::sleep_for(3s);
                }
                else if (enemy.health < 45 && enemy.health > 0)
                {
                    cout << "YOU RAN SO FAR AWAY!\n";
                    this_thread::sleep_for(3s);
                    fight_end = 1;
                }
                else
                {
                    cout << "The enemy evaporated.... WEIRD!\n";
                    this_thread::sleep_for(3s);
                    fight_end = 1;
                }
            }
            else 
                cout << "move invalid...";
        
            clearScreen();
    }
 
}


/*
    Using pointers as a way to keep track of player_x and player_y,
    without having to return anything and update.
*/
void moves(string move, Player &p, int *player_x, int *player_y, int rows, int cols, int (&map)[3][3])
{
    int new_x = *player_x;
    int new_y = *player_y;

    if (move == "down" && *player_y + 1 < rows && map[*player_y + 1][*player_x] != 1)
        new_y += 1;
    else if (move == "up" && *player_y - 1 >= 0 && map[*player_y - 1][*player_x] != 1)
        new_y -= 1;
    else if (move == "right" && *player_x + 1 < cols && map[*player_y][*player_x + 1] != 1)
        new_x += 1;
    else if (move == "left" && *player_x - 1 >= 0 && map[*player_y][*player_x - 1] != 1)
        new_x -= 1;
    else
    {
        cout << "You have hit a wall\n";
        this_thread::sleep_for(1.2s);
        return;
    }

    *player_x = new_x;
    *player_y = new_y;

    if (map[*player_y][*player_x] == 2)
    {
        Fight(p);
    }
}






int main()
{
    //initializing random seeding
    srand(time(0));
    const int rows = 3;
    const int cols = 3;
    
    Map myMap(5,8);
    myMap.print_map();

    this_thread::sleep_for(20s);

    //instantiating text colors
    TextColors text_colors;

    //character info
    Player player;

    //create dialogue
    Game_Dialogue dialogue;

    //clears the screen to start
    clearScreen();
    cout << dialogue.ask_name_text; //displays text asking for name
    cin >> player.name; // takes user input for name
    clearScreen();

    cout << text_colors.red << player.name << text_colors.default_color << ", The name of a Fierce warrior!\n";
    this_thread::sleep_for(3s);
    clearScreen();
    cout << dialogue.game_start_text;
    this_thread::sleep_for(1s);
    clearScreen();

    //2d array for world



    int map[3][3] = {{}};
   

    //gameloop
    int end_value = 0;
    player.player_x = 0;
    player.player_y = 0;
    string move;

    while (!end_value)
    {
        cout << text_colors.red << "Player Location: \n";
        cout << "X:" << player.player_x << " Y:" << player.player_y << "\n";
        cout << text_colors.cyan << "Options: \n* up\n* down\n* left\n* right\n* map\n* inventory\n";
        
        
        //Takes in a move and then deciphers what to do with that move
        cout << text_colors. default_color << "Please enter your move: ";
        cin >> move;
        moves(move, player ,&player.player_x, &player.player_y, rows, cols, map);
        clearScreen();

    }

    return 0;

} 