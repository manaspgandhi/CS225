
#pragma once

#include "cs225/PNG.h"
#include "dsets.h"

#include <vector>
#include <iostream>
#include <queue>
#include <map>
// #include <cstdlib>
#include <algorithm>


using namespace cs225;
using namespace std;

/**
 * This class creates a SquareMaze object which represents a randomly-generated
 * square maze and its solution
 **/
class SquareMaze{
    public:
        SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        vector<int> solveMaze();
        PNG * drawMaze() const;
        PNG * drawMazeWithSolution();

    private:
        int width_;
        int height_;
        vector<bool> upWalls_;
        vector<bool> downWalls_;
        vector<bool> leftWalls_;
        vector<bool> rightWalls_;
};