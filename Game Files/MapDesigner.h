#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

enum TileType {
    EMPTY,
    WALL,
    ENEMY,
    DOOR,
};

class Map {
public:
    int rows;
    int cols;
    std::vector<std::vector<TileType>> tiles;

    // Constructor with random size
    Map(int minRows = 3, int maxRows = 20, int minCols = 3, int maxCols = 20) {
        srand(static_cast<unsigned int>(time(0))); // seed RNG
        rows = rand() % (maxRows - minRows + 1) + minRows;
        cols = rand() % (maxCols - minCols + 1) + minCols;
        tiles.resize(rows, std::vector<TileType>(cols, EMPTY));
        generateRandom();
    }

    // Generate random tiles with walls and 2 doors
    void generateRandom() {
        // Fill map with random inner tiles
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                if (y == 0 || y == rows - 1 || x == 0 || x == cols - 1) {
                    tiles[y][x] = WALL;
                } else {
                    int tile = rand() % 3; // 0=EMPTY,1=WALL,2=ENEMY
                    tiles[y][x] = static_cast<TileType>(tile);
                }
            }
        }

        // Collect possible outer wall positions for doors (excluding corners)
        std::vector<std::pair<int, int>> edges;
        for (int x = 1; x < cols - 1; x++) {
            edges.push_back({0, x});          // top
            edges.push_back({rows - 1, x});   // bottom
        }
        for (int y = 1; y < rows - 1; y++) {
            edges.push_back({y, 0});          // left
            edges.push_back({y, cols - 1});   // right
        }

        // Pick 2 unique random positions for doors
        int index1 = rand() % edges.size();
        int index2;
        do {
            index2 = rand() % edges.size();
        } while (index2 == index1);

        tiles[edges[index1].first][edges[index1].second] = DOOR;
        tiles[edges[index2].first][edges[index2].second] = DOOR;
    }

    // Print map to console
    void print() const {
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                switch (tiles[y][x]) {
                    case EMPTY: std::cout << "."; break;
                    case WALL:  std::cout << "#"; break;
                    case ENEMY: std::cout << "E"; break;
                    case DOOR:  std::cout << "D"; break;
                }
            }
            std::cout << "\n";
        }
    }
};

#endif // MAP_H
