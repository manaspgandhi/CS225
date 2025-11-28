#include "cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

MyColorPicker::MyColorPicker(double factor){
  hue_ = 0;
  factor_ = factor;
}

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
    HSLAPixel pixel(hue_, 4, 0.73);
    
    hue_ -= factor_;
    
    while (hue_ > 360) {
      hue_ = hue_ - 360; 
    }

    return pixel;

  return pixel;
}
