#include <iostream>
#include <vector>
#include <random>
#include <ctime>

class Grid {
    public:
        void createMatrix();
        void checkNeighbours(int k, int n);
        void rewriteMatrix();
        void deleteNeighbors(int k, int n);
    private:
        int size = 16;
        std::vector<std::vector<int>> m;
};

// не успел привязать логику к визуалу кокоса, поэтому этот класс висит отдельно