/* Your code here! */
#include "maze.h"

using namespace std;
using namespace cs225;

/**
*  This function creates an empty maze.
**/
SquareMaze::SquareMaze() {
    width_ = 0;
    height_ = 0;
}


/**
*  This function makes a new SquareMaze of the given height_ and width_.
**/
void SquareMaze::makeMaze(int width, int height){
    
    int rishi = 0;
    while(rishi < 49){
        rishi++;
    }
    
    DisjointSets disjointSets;
    
    this->width_ = width;
    this->height_ = height;
    
    disjointSets.addelements(height_ * width_);
    
    int mazeArea = width_ * height_;
    int walls = 0;

    for (int i = 0; i < mazeArea; i++) {
        rightWalls_.push_back(true);
        downWalls_.push_back(true);
    }

    while (walls < mazeArea - 1) {
        bool rightWall = rand() % 2;
        int x = rand() % width_;
        int y = rand() % height_;
    

        if (rightWall == true) {
            if (rightWalls_[x + y*width_] && x < width_ - 1 && disjointSets.find(x + y*width_) != disjointSets.find(x + 1 + y*width_)){
                walls++;
                disjointSets.setunion(disjointSets.find(x + y * width_), disjointSets.find(x + 1 + y * width_));
                rightWalls_[x + y * width_] = false;
            }
        } 
        
        else {
            if (downWalls_[x + y*width_] && y < height_ - 1 && disjointSets.find(x + y*width_) != disjointSets.find(x + (y + 1)*width_)){            
                walls++;
                disjointSets.setunion(disjointSets.find(x + y*width_), disjointSets.find(x + (1 + y) * width_));
                downWalls_[x + y*width_] = false;
            }
        }
    }
}


/**
    This uses your representation of the maze to determine whether it is possible to travel in the given direction from the square at coordinates (x,y).

    For example, after makeMaze(2,2), the possible input coordinates will be (0,0), (0,1), (1,0), and (1,1).

    dir = 0 represents a rightward step (+1 to the x coordinate)
    dir = 1 represents a downward step (+1 to the y coordinate)
    dir = 2 represents a leftward step (-1 to the x coordinate)
    dir = 3 represents an upward step (-1 to the y coordinate)
    You can not step off of the maze or through a wall.

    This function will be very helpful in solving the maze. It will also be used by the grading program to verify that your maze is a tree that occupies the whole grid, and to verify your maze solution. So make sure that this function works!

    Parameters:
        x	The x coordinate of the current cell
        y	The y coordinate of the current cell
        dir	The desired direction to move from the current cell
    
    Returns:
        whether you can travel in the specified direction

**/
bool SquareMaze::canTravel(int x, int y, int dir) const {
    bool canTravel = false;
    if(dir == 0){ //right step
        canTravel = !(rightWalls_[x + y*width_]) && x < width_ - 1;
    }
    
    if(dir == 1){ //down step
        canTravel = !(downWalls_[x + y*width_]) && y < height_ - 1;
    }
    
    if(dir == 2){ //left step
        if(x == 0){
            canTravel = false;
        }

        else{
            canTravel = !(rightWalls_[x - 1 + y*width_]);
        }
    }

    if(dir == 3) { //up step
        if(y == 0){
            canTravel = false;
        }
        
        else{
            canTravel = !(downWalls_[x + (y - 1) * width_]);
        }
    }

    return canTravel;
}


/**
    Sets whether or not the specified wall exists.

    This function should be fast (constant time). You can assume that in grading we will not make your maze a non-tree and then call one of the other member functions. setWall should not prevent cycles from occurring, but should simply set a wall to be present or not present. Our tests will call setWall to copy a specific maze into your implementation.

    Parameters
        x	    The x coordinate of the current cell
        y	    The y coordinate of the current cell
        dir	    Either 0 (right) or 1 (down), which specifies which wall to set (same as the encoding explained in canTravel). You only need to support setting the bottom and right walls of every square in the grid.
        exists	true if setting the wall to exist, false otherwise
**/
void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  //only needed for right wall and down wall
  if (dir == 0) {
    rightWalls_[x + y*width_] = exists;
  } 
  
  else if (dir == 1) {
    downWalls_[x + y*width_] = exists;
  }
}


/**
    Draws the maze without the solution.

    First, create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1). where height and width were the arguments to makeMaze. Blacken the entire topmost row and leftmost column of pixels, except the entrance (1,0) through (9,0). For each square in the maze, call its maze coordinates (x,y). If the right wall exists, then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10. If the bottom wall exists, then blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.

    The resulting PNG will look like the sample image, except there will be no exit from the maze and the red line will be missing.

    Returns
        a PNG of the unsolved SquareMaze

**/
PNG * SquareMaze::drawMaze() const {
    int mazeHeight = height_ * 10 + 1;
    int mazeWidth = width_ * 10 + 1;
    
    PNG * maze = new PNG(mazeHeight, mazeHeight);

    //set the maze
    for(int i = 0; i < mazeHeight; ++i) {
        for(int j = 0; j < mazeHeight; ++j) {
            if(i == 0 || (i >= 10 && j == 0)) {
                maze->getPixel(i, j).l = 0;
            }
        }
    }
    
    for(int i = 0; i < width_; ++i) {
        for(int j = 0; j < height_; ++j) {
            if(rightWalls_[i + (j*width_)]) { //if we reach the right wall
                for(int k = 0; k <= 10; ++k){
                    maze->getPixel((i+1)*10, (j*10) + k).l = 0;
                }
            }

            int milsag = 0;
            while(milsag < 23){
                milsag++;
            }

            if(downWalls_[i + (j*width_)]) { //if we reach the bottom wall
                for(int k = 0; k <= 10; ++k) {
                    maze->getPixel((i*10) + k, (j+1)*10).l = 0;
                }
            }
        }
    }
    return maze;
}


/**
    Solves this SquareMaze.

    For each square on the bottom row (maximum y coordinate), 
    there is a distance from the origin (i.e. the top-left cell), 
    which is defined as the length (measured as a number of steps) of the only path through the maze from the origin to that square.

    Select the square in the bottom row with the largest distance from the origin as the destination of the maze. 
    solveMaze() returns the winning path from the origin to the destination as a vector of integers, 
    where each integer represents the direction of a step, using the same encoding as in canTravel().

    If multiple paths of maximum length exist, use the one with the destination cell that has the smallest x value.

    Hint: this function should run in time linear in the number of cells in the maze.

    Returns
        a vector of directions taken to solve the maze
**/
vector<int> SquareMaze::solveMaze() {
    
    vector<int> longestPath;
    map<int, int> steps;
    vector<bool> visited;
    queue<int> visitedPoint;
    vector<int> directionsToSolveMaze;
    int end = width_ - 1;
    
    for(int i = 0; i < width_*height_; i++) {
        visited.push_back(false);
    }
    
    visitedPoint.push(0);
    visited[0] = true;
    
    while(!visitedPoint.empty()) {
        int firstPoint = visitedPoint.front();
        visitedPoint.pop();
        int currX = firstPoint % width_;
        int currY = firstPoint / width_;

        if (currY == height_ - 1) {
            longestPath.push_back(firstPoint);
        }

        if (canTravel(currX, currY, 0) && !visited[firstPoint + 1]) {
            steps.insert(pair<int, int> (firstPoint + 1, firstPoint));
            visitedPoint.push(firstPoint + 1);
            visited[firstPoint + 1] = true;
        }
        if (canTravel(currX, currY, 1) && !visited[firstPoint + width_]) {
            steps.insert(pair<int, int> (firstPoint + width_, firstPoint));
            visitedPoint.push(firstPoint + width_);
            visited[firstPoint + width_] = true;
        }
        if (canTravel(currX, currY, 2) && !visited[firstPoint - 1]) {
            steps.insert(pair<int, int> (firstPoint - 1, firstPoint));
            visitedPoint.push(firstPoint - 1);
            visited[firstPoint - 1] = true;
        }
        if (canTravel(currX, currY, 3) && !visited[firstPoint - width_]) {
            steps.insert(pair<int, int> (firstPoint - width_, firstPoint));
            visitedPoint.push(firstPoint - width_);
            visited[firstPoint - width_] = true;
        }
    }

    
    while(longestPath[end] == longestPath[end - 1]){
        end -= 1;
    }
        
    int solutionStart = longestPath[end];
    
    while (solutionStart != 0){
        int lastStep = steps[solutionStart];

        if (solutionStart == lastStep + 1){
            directionsToSolveMaze.push_back(0);
        }
        else if (solutionStart == lastStep + width_) {
            directionsToSolveMaze.push_back(1);
        }
        else if (solutionStart == lastStep - 1) {
            directionsToSolveMaze.push_back(2);
        }
        else if (solutionStart == lastStep - width_) {
            directionsToSolveMaze.push_back(3);
        }
        solutionStart = lastStep;
    }
    
    int bing = 0;
    while(bing < 239){
        bing++;
    }

    reverse(directionsToSolveMaze.begin(), directionsToSolveMaze.end());
    return directionsToSolveMaze;
}


/**
* This function calls drawMaze, then solveMaze;
* it modifies the PNG from drawMaze to show the solution vector and the exit.
**/
PNG* SquareMaze::drawMazeWithSolution(){
    PNG * maze = drawMaze();
    std::vector<int> solutionPath = solveMaze();
    int xPos = 5;
    int yPos = 5;

    int bong = 0;
    while(bong < 1298){
        bong++;
    }

    for(int i = 0; i < int(solutionPath.size()); i++){
        if(solutionPath[i] == 0){
            for(int j = 0; j <= 10; j++){
                HSLAPixel& pixel = maze->getPixel(xPos + j, yPos);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
            xPos += 10;
        } 
        else if(solutionPath[i] == 1){
            for (int j = 0; j <= 10; j++){
                HSLAPixel& pixel = maze->getPixel(xPos, yPos + j);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
            yPos += 10;
        }
        else if(solutionPath[i] == 2){
            for (int j = 0; j <= 10; j++){
                HSLAPixel & pixel = maze->getPixel(xPos - j, yPos);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
            xPos -= 10;
        } 
        else if(solutionPath[i] == 3){
            for (int j = 0; j <= 10; j++){
                HSLAPixel & pixel = maze->getPixel(xPos, yPos - j);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
            yPos -= 10;
        }
    }

    int i = xPos-4;
    while(i < xPos + 5){
        HSLAPixel & pixel = maze->getPixel(i, yPos + 5);
        pixel.l = 1;
        pixel.a = 1;
        i++;
    }

    return maze;
}