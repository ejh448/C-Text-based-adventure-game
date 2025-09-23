#include <iostream>
#include <string>
//#include <vector>
//for system clear
#include <cstdlib>
#include <chrono>
#include <thread>

#include "Game_Dialogue.h"

//can use this so you do not have to
//write std::string every time
//or all std
using namespace std;
using namespace std::chrono_literals;

void clearScreen()
{
    system("clear");
}

void Fight()
{
    Enemy enemy;
    int monster_type = (rand() % 3) + 1;
    cout << enemy.names[monster_type] << "\n";
    int fight_end = 0;
 
}


/*
    Using pointers as a way to keep track of player_x and player_y,
    without having to return anything and update.
*/
void options(string move, int *player_x, int *player_y, int rows, int cols, int (&map)[3][3])
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
        Fight();
    }
}


/*
    Using a struct allows to keep similar things together
    such as a player.
*/
struct Player {
    //setting base values
    string name;
    int xp = 0;
    int health = 100;
    int player_x = 0;
    int player_y = 0;
    int gold = 100;
};

struct Enemy {
    string names[3] = {
        "Goblin",
        "Ghoul",
        "Skeleton"
    };
    int health;
    int level;
    int gold;
};


struct Text_Colors {
    //text colors
    string red           = "\033[31m";
    string cyan          = "\033[36m";
    string default_color = "\033[0m";
};


int main()
{
    //instantiating text colors
    Text_Colors text_colors;

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
    const int rows = 3;
    const int cols = 3;
    int map[rows][cols] = {{0,0,0},
                           {0,1,0},
                           {0,2,0}};

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
        options(move, &player.player_x, &player.player_y, rows, cols, map);
        clearScreen();

    }


}