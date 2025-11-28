#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
    png_ = png;
    start_ = start;
    tolerance_ = tolerance;
    points_.push(start);
    
    for (unsigned i = 0; i < png_.width(); i++) {
        
        vector<bool> currVec;
        
        for (unsigned j = 0; j < png_.height(); j++) {
            currVec.push_back(false);
        }

        visitedPoints_.push_back(currVec);
    }
    
    visitedPoints_[start.x][start.y] = true;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  DFS* dfsStartPoint = new DFS(png_, start_, tolerance_);
  return ImageTraversal::Iterator(*dfsStartPoint, start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(true);
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  points_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point tail = points_.top();
  points_.pop();
  return tail;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return points_.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return points_.empty();
}

PNG * DFS::getPNG() {
    return &png_;
}

double DFS::getTolerance() {
    return tolerance_;
}

bool DFS::getVisitedPoint(unsigned x, unsigned y) {
    return visitedPoints_[x][y];
}

void DFS::setVisitedPoint(unsigned x, unsigned y) {
    visitedPoints_[x][y] = true;
}

unsigned int DFS::getWidth(){
  return png_.width();
}

void DFS::setWidth(unsigned int width){
  imageWidth_ = width;
}

unsigned int DFS::getHeight(){
  return png_.height();
}

void DFS::setHeight(unsigned int height){
  imageHeight_ = height;
}