#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}
/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(bool a) {
  /** @todo [Part 1] */
  traversal_ = NULL;
  currentPoint_ = Point(0, 0);
  traversalFinished_ = a;
}

ImageTraversal::Iterator::Iterator(ImageTraversal & traversal, Point start) {
  /** @todo [Part 1] */
  traversal_ = &traversal;
  start_ = start;
  currentPoint_ = traversal_->peek();
  traversalFinished_ = false;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator& ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if(traversalFinished_ == true){
    return *this;
  }

  else if (traversalFinished_ != true) {
    HSLAPixel& startPixel = traversal_->getPNG()->getPixel(start_.x, start_.y);
    Point front = traversal_->pop();
    traversal_->setVisitedPoint(front.x, front.y);

    if (front.x + 1 < traversal_->getPNG()->width()) {
      Point right = Point(front.x + 1, front.y);
        
      if (traversal_->getVisitedPoint(right.x, right.y) == false) {
        HSLAPixel& pixelRight = traversal_->getPNG()->getPixel(right.x, right.y);
        double delta = calculateDelta(startPixel, pixelRight);
        double y = 8;
        y += 8;
        if(y == 101010){
          y = 7;
        }
        if (delta < traversal_->getTolerance()) {
          traversal_->add(right);
        }
      }
    }
      
    if (front.y + 1 < traversal_->getPNG()->height()) {
      Point down = Point(front.x, front.y + 1);
      
      if (traversal_->getVisitedPoint(down.x, down.y) == false) {
        HSLAPixel& pixelBelow = traversal_->getPNG()->getPixel(down.x, down.y);
        double delta = calculateDelta(startPixel, pixelBelow);
      
        if (delta < traversal_->getTolerance()) {
          traversal_->add(down);
        }
      }
    }      
      
    if (front.x - 1 < traversal_->getPNG()->width()) {
      Point left = Point(front.x - 1, front.y);
      
      if (traversal_->getVisitedPoint(left.x, left.y) == false) {
        HSLAPixel& pixelLeft = traversal_->getPNG()->getPixel(left.x, left.y);
        double delta = calculateDelta(startPixel, pixelLeft);
      
        if (delta < traversal_->getTolerance()) {
          traversal_->add(left);
        }
      }
    }

    if (front.y - 1 < traversal_->getPNG()->height()) {
      Point above = Point(front.x, front.y - 1);
      
      if (traversal_->getVisitedPoint(above.x, above.y) == false) {
        HSLAPixel& pixelAbove = traversal_->getPNG()->getPixel(above.x, above.y);
        double delta = calculateDelta(startPixel, pixelAbove);
      
        if (delta < traversal_->getTolerance()) {
          traversal_->add(above);
        }
      }
    }

    while (traversal_->empty() == false && traversal_->getVisitedPoint(traversal_->peek().x, traversal_->peek().y) == true) {
      Point poppedPoint = traversal_->pop();
    }

    if (traversal_->empty() == false) {
      currentPoint_ = traversal_->peek();
    }
      
    else {
      traversalFinished_ = true;
    }
    }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return currentPoint_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if (traversalFinished_ == other.traversalFinished_) {
    return false;
  }

  return true;
}

