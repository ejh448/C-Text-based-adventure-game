#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
using namespace std;

class Map {
public:
    int rows;
    int cols;
    vector<vector<int>> vec;

    // Constructor
    Map(int r, int c) {
        rows = r;
        cols = c;

       for (int i = 0; i < rows; i++) {
            vector<int> row;
            for (int j = 0; j < cols; j++) {
                if (i == 0 || j == 0 || j == cols - 1 || i == rows - 1)
                {
                    row.push_back(1);
                }
                else
                {
                    row.push_back(0);
                }
            }
            vec.push_back(row);
        }



        // Randomly add enemies
        int num_enemies = rand() % ((rows-2)*(cols-2)/3) + 1;
        for (int n = 0; n < num_enemies; n++) {
            int x, y;
            do {
                x = rand() % (cols - 2) + 1; // avoid walls
                y = rand() % (rows - 2) + 1;
            } while (vec[y][x] != 0); // only place on empty cells

            vec[y][x] = 2; // enemy
        }

   
    }

    void print_map()
    {
             
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++) 
            {
                cout << vec[i][j] << " ";
            }
            cout << endl;
        }
    }

    //using overloading to print the players location when needed.
    void print_map(int player_x, int player_y) 
    {
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            if (i == player_y && j == player_x)
                cout << "P "; // Print player
            else
                cout << vec[i][j] << " ";
        }
        cout << endl;
    }
}
};

#endif
