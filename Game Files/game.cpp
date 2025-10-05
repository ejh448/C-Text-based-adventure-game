#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>

#include "Game_Dialogue.h"
#include "Player.h"
#include "Enemy.h"
#include "Text_Colors.h"
#include "MapDesigner.h"

/*
    can use this so you do not have to
    write std::string / std::chrono_litrerals 
    every time
*/
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

void Fight(Player &p, TextColors text_colors)
{
    Enemy enemy;
    int monster_type = (rand() % 3);
    bool fight_end = false;

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
                int attack = p.player_attack(rand()); // have an issue when player health is around 2, scales infinitely...
                cout << "You Damaged the " << enemy.names[monster_type] << " " << text_colors.red << attack << text_colors.default_color << " points...\n";
                enemy.health -=  attack;
                this_thread::sleep_for(1.5s);

                if (enemy.health <= 0)
                {
                    cout << "You have won the fight!!! \n";
                    int randomFactor = rand() % 99 + 1;
                    p.xp_gain(randomFactor, p.level);
                    cout << "\nHERE IS YOUR XP " << text_colors.cyan << p.xp << text_colors.default_color << "\n";
                    this_thread::sleep_for(3s);
                    fight_end = true;
                    clearScreen();
                    continue;
                }

                //if enemy does not run out of health keep attacking.
                cout << "The enemy is attacking";
                animateDots();
                int enemy_attack = enemy.enemy_attack(rand());
                cout << "The " << enemy.names[monster_type] << " attacked!\nDoing " << text_colors.cyan << enemy_attack << text_colors.default_color << " damage!\n";
                p.health -= enemy_attack;
                this_thread::sleep_for(1.5s);

                if (p.health <= 0)
                {
                    cout << "UNFORTUNATELY YOU HAVE LOST THE FIGHT\n";
                    this_thread::sleep_for(1.5s);
                    fight_end = true;
                }
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
                    this_thread::sleep_for(1.5s);
                }
                else if (enemy.health < 45 && enemy.health > 0)
                {
                    cout << "YOU RAN SO FAR AWAY!\n";
                    this_thread::sleep_for(1.5s);
                    fight_end = true;
                }
                else
                {
                    cout << "The enemy evaporated.... WEIRD!\n";
                    this_thread::sleep_for(1.5s);
                    fight_end = true;
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
void moves(string move, Player &p, int *player_x, int *player_y, int rows, int cols,  vector<vector<int>> &map, TextColors text_colors)
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
        //this is the case where the player hits a wall.. Dont need to do anything here currently
        return;
    }

    //This updates the players x and y to the new x and y values
    *player_x = new_x; 
    *player_y = new_y;

    //checks if spot on the map is an enemy, then calls fight()
    if (map[*player_y][*player_x] == 2)
    {
        Fight(p, text_colors);
    }
}






int main()
{
    //initializing random seeding
    srand(time(0));

    //initializing objects
    TextColors text_colors;
    Player player;
    Game_Dialogue dialogue;


    //clears the screen to start
    clearScreen();
    cout << dialogue.ask_name_text; //displays text asking for name
    cin >> player.name; // takes user input for name
    clearScreen();
    cout << text_colors.red << player.name << text_colors.default_color << ", The name of a Fierce warrior!\n";
    this_thread::sleep_for(1.5s);
    clearScreen();
    cout << dialogue.game_start_text;
    this_thread::sleep_for(1s);
    clearScreen();

    //constants & initializers for game loop
    const int MAP_ROWS = 5;
    const int MAP_COLS = 5;
    const int INITIAL_X = 1;
    const int INITIAL_Y = 1;
    
    string move;
    Map myMap(MAP_ROWS, MAP_COLS);
    
    player.player_x = INITIAL_X;
    player.player_y = INITIAL_Y;
    
    bool end_value = true;
    
    while (end_value)
    {
        cout << text_colors.red << "Player Location: \n";
        cout << "X:" << player.player_x << " Y:" << player.player_y << "\n";
        myMap.print_map(player.player_x, player.player_y);
        cout << text_colors.cyan << "Options: \n* up\n* down\n* left\n* right\n* map\n* inventory\n";
       
        cout << text_colors. default_color << "Please enter your move: ";
        cin >> move;
        moves(move, player, &player.player_x, &player.player_y, myMap.rows, myMap.cols, myMap.vec, text_colors);
        clearScreen();
    }

    return 0;

} 