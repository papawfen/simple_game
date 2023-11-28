#include "Grid.h"

USING_NS_CC;

void Grid::FirstInitGrid() {
    if (!grid.empty()) grid.clear();
    grid.resize(size, std::vector<int>(size));
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 3);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            grid[i][j] = dist6(rng);
        }
    }
}

bool Grid::CheckNeighbours(int k, int n) {
    if (DeleteNeighbors(k, n, true)) {
        DeleteNeighbors(k, n, false);
        grid[k][n] = 0;
        RewriteGrid();
        return true;
    }
    return false;
}

bool Grid::DeleteNeighbors(int k, int n, bool check) {
    std::queue<std::pair<int, int>> q;
    q.push({k, n});
    std::set<std::pair<int, int>> visited;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        visited.insert(v);
        for (int i = -1; i <= 1; ++i) {
            if (v.first + i < 0 || v.first + i == size) {
                continue;
            }
            for (int j = -1; j <= 1; ++j) {
                if (v.second + j < 0 || v.second + j == size || std::abs(i) + std::abs(j) == 2) {
                    continue;
                }
                if (grid[v.first + i][v.second + j] == grid[k][n]) {
                    if (visited.find({v.first + i, v.second + j}) == visited.end()) {
                        q.push({v.first + i, v.second + j});
                    }
                    if (v.first + i == k && v.second + j == n) {
                        continue;
                    }
                    if (!check) {
                        grid[v.first + i][v.second + j] = 0;
                    } else {
                        ++matches;
                    }
                }
            }
        }
        if (matches >= 3) {
            matches = 0;
            return true;
        }
    }
    matches = 0;
    return false;
}

void Grid::RewriteGrid() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - 1; ++j) {
            for (int k = 0; k < size - j - 1; ++k) {
                if (grid[k + 1][i] == 0) {
                    std::swap(grid[k][i], grid[k + 1][i]);
                }
            }
        }
    }
}

std::vector<std::vector<int>> Grid::GetGrid() { return grid; }

