#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "cs225/PNG.h"
#include "dsets.h"
#include "maze.h"
#include "mazereader.h"

using std::cout;
using std::endl;
using std::string;

using namespace cs225;
using namespace std;

void assert_maze_acyclic(SquareMaze & maze, int width, int height);
void assert_maze_connected(SquareMaze & maze, int width, int height);
void assert_maze_tree(SquareMaze & maze, int width, int height);
void copyMaze(const MazeReader & source, SquareMaze * dest);
void advancePosition(int * x, int * y, int dir);
PNG read_solution(const string & filename, int width, int height);
PNG read_unsolved(const string & filename, int width, int height);
#define READ_SOLUTION_PNG(func, width, height)  \
    read_solution(string("../tests/soln_") + func + string(".png"), width, height)
#define READ_UNSOLVED_PNG(func, width, height)  \
    read_unsolved(string("../tests/soln_") + func + string(".png"), width, height)
#define READ_SOLUTION_MAZE(func, width, height)  \
    MazeReader(READ_SOLUTION_PNG(func, width, height))
#define READ_UNSOLVED_MAZE(func, widht, height)  \
    MazeReader(READ_UNSOLVED_PNG(func, width, height))


TEST_CASE("My Test Case", "[weight=10][part2][timeout=30000]") {
    // Feel free to use this to put your own test cases.
    // Look at other test files for inspiration!
    PNG solnImage = READ_UNSOLVED_PNG("testDrawMazeLarge", 190, 190);
    MazeReader soln(solnImage);
    SquareMaze maze;
    copyMaze(soln, &maze);
    PNG * actualOutput = maze.drawMaze();
    actualOutput->writeToFile("testDrawMazeLarge" + string(".png"));
    REQUIRE(*actualOutput == solnImage);
    delete actualOutput;


    // string expected = "I put my own test cases here.";
    // string actual = "I DON'T HAVE ANY TEST CASES :'(";
    // REQUIRE(expected == actual);
}