#include "grid.h"

#include <queue>
#include <set>

void Grid::createMatrix() {
    m.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        m[i].reserve(size);
    }

    std::random_device dev;
    std::mt19937 rng(dev());
    srand((unsigned) time(NULL));
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,3);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            m[i][j] = dist6(rng);
            std::cout << m[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void Grid::checkNeighbours(int k, int n) {
    int current = m[k][n];
    deleteNeighbors(k, n);
    m[k][n] = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << m[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void Grid::deleteNeighbors(int k, int n) {
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
                if (m[v.first + i][v.second + j] == m[k][n]) {

                    if (visited.find({v.first + i, v.second + j}) == visited.end()) {
                        q.push({v.first + i, v.second + j});
                    }
                    if (v.first + i == k && v.second + j == n) {
                        continue;
                    }
                    m[v.first + i][v.second + j] = 0;
                }
            }
        }
    }
}

int main() {
    Grid grid;
    grid.createMatrix();
    int a, b;
    std::cin >> a >> b;
    grid.checkNeighbours(a, b);
    return 0;
}
