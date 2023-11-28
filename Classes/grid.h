#ifndef MATCH_GRID_H
#define MATCH_GRID_H

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <queue>
#include <set>
#include "cocos2d.h"

class Grid {
    public:
        Grid() {};
        ~Grid() {};
        void FirstInitGrid();
        void RewriteGrid();
        bool CheckNeighbours(int k, int n);
        bool DeleteNeighbors(int k, int n, bool check);
        std::vector<std::vector<int>> GetGrid();
    private:
        int size = 16;
        int matches = 0;
        std::vector<std::vector<int>> grid;
};

#endif // MATCH_GRID_H