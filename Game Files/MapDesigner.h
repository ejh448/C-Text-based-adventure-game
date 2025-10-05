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

   
    }

    void print_map(){
             
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++) 
            {
                cout << vec[i][j] << " ";
            }
            cout << endl;
        }
    }
};

#endif // MAP_H
