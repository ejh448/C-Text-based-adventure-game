#include <iostream>
#include <string>
//for system clear
#include <cstdlib>
#include <chrono>
#include <thread>


//can use this so you do not have to
//write std::string every time
//or all std
using namespace std;
using namespace std::chrono_literals;

void clearScreen()
{
    system("clear");
}

/*
    Using pointers as a way to keep track of player_x and player_y,
    without having to return anything and update.
*/
void options(string move, int *player_x, int *player_y, int rows, int cols,  int (&map)[3][3])
{
        if (move == "down" && *player_y + 1 < rows && map[*player_x][*player_y + 1] != 1)
        {
            (*player_y) += 1;
        }
        else if (move == "up" && *player_y - 1 >= 0 && map[*player_x][*player_y - 1] != 1 )
        {
            (*player_y) -= 1;
        }
        else if (move == "right" && *player_x + 1 < cols && map[*player_x + 1][*player_y] != 1)
        {
            (*player_x) += 1;
        }
        else if (move == "left" && *player_x - 1 >= 0 && map[*player_x - 1][*player_y] != 1)
        {
            (*player_x) -= 1;
        }
        else
        {
            cout << "You have hit a wall\n";
            this_thread::sleep_for(1.2s);
        }
}

int main()
{
    //text colors
    string red = "\033[31m";
    string default_color = "\033[0m";

    //character info
    string name;
    int health = 100;   
    cout << "Hello...\nWelcome to the game...\nWhat is your name?...\n";

    cin >> name;
    
    cout << red << name << default_color << ", That is a nice name!\n";
    this_thread::sleep_for(3s);
    clearScreen();

    cout << red; 
    cout << "Get ready for the game!\n";
    //2d array for world
    const int rows = 3;
    const int cols = 3;
    int map[rows][cols] = {{0,0,0},
                           {0,1,0},
                           {0,0,0}};

    //gameloop
    int end_value = 0;
    int player_x = 0;
    int player_y = 0;
    string move;

    while (!end_value)
    {
        cout << "X:" << player_x << " Y: " << player_y << "\n";
        //Takes in a move and then deciphers what to do with that move
        cin >> move;
        options(move, &player_x, &player_y, rows, cols, map);
        clearScreen();

    }


}