#include <iostream>
#include <string>
//for system clear
#include <cstdlib>
#include <chrono>
#include <thread>


//can use thios so you do not have to
//write std::string every time
//or all std
using namespace std;
using namespace std::chrono_literals;

void clearScreen()
{
    system("clear");
}

/*
void isValid(int[][] map, player_start_x, player_start_y)
{

}
*/


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
        cin >> move;
        if (move == "down" && player_x + 1 <= rows && map[player_x + 1][player_y] != 1)
        {
            player_x += 1;
        }
        else if (move == "right" && player_y + 1 <= cols)
        {
            player_y += 1;
        }
        else if (move == "up" && player_x - 1 >= 0)
        {
            player_x -= 1;
        }
        else if (move == "left" && player_y - 1 >= 0)
        {
            player_y -= 1;
        }
        else
        {
            cout << "You have hit a wall\n";
            this_thread::sleep_for(1.2s);
        }
        clearScreen();

    }


}