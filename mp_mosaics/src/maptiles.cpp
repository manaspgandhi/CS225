/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    MosaicCanvas * mosaicCanvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    map<Point<3>, TileImage*> mosaicImageMap;

    vector<Point<3>> points;

    for (auto i = theTiles.begin(); i != theTiles.end(); i++) {
        Point<3> AvColPoint = convertToXYZ(i->getAverageColor());
        
        mosaicImageMap[AvColPoint] = &(*i);
        points.push_back(AvColPoint);
    } 
    
    KDTree<3> kdtree(points);
    for (int i = 0; i < mosaicCanvas->getRows(); ++i) {
        for (int j = 0; j < mosaicCanvas->getColumns(); ++j) {
            Point<3> regionColor = convertToXYZ(theSource.getRegionColor(i, j));
            Point<3> closestColor = kdtree.findNearestNeighbor(regionColor);
            
            mosaicCanvas->setTile(i, j, mosaicImageMap[closestColor]);
        }
    }
    
    return mosaicCanvas;
}

