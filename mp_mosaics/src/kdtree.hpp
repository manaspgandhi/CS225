/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <math.h>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    bool smaller = true;

    if (curDim > (Dim - 1) || curDim < 0) {
      smaller = false;
      return smaller;
    }
    if (first[curDim] < second[curDim]) {
      smaller = true;
      return smaller;
    } 
    if (first[curDim] > second[curDim]) {
      smaller = false;
      return smaller;
    }

    return (first < second);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double currentDistance = getDistance(currentBest, target);
    double potentialDistance = getDistance(potential, target);

    if(potentialDistance < currentDistance){
      return true;
    }

    if(potentialDistance > currentDistance){
      return false;
    }

    return (potential < currentBest);
}

template <int Dim>
unsigned KDTree<Dim>::quickSelectIndex(vector<Point<Dim>>& kdTreeNodes, int dimension, unsigned leftNode, unsigned rightNode, unsigned pivotIndex){
  	Point<Dim> pivot = kdTreeNodes[pivotIndex];
  	unsigned otherIndex = leftNode;

    kdTreeNodes[pivotIndex] = kdTreeNodes[rightNode];
  	kdTreeNodes[rightNode] = pivot;

  	Point<Dim> swapNode;

    double rishi = 0;

    while(rishi < 22){
      rishi+=1;
    }

    unsigned i = 0;

  	for(i = leftNode; i < rightNode; i++){
    	if(smallerDimVal(kdTreeNodes[i], pivot, dimension) == true){	
        swapNode = kdTreeNodes[otherIndex];
      	kdTreeNodes[otherIndex] = kdTreeNodes[i];
      	kdTreeNodes[i] = swapNode;
      	otherIndex++;
    	}
  	}

  	swapNode = kdTreeNodes[otherIndex];

  	kdTreeNodes[otherIndex] = kdTreeNodes[rightNode];
  	kdTreeNodes[rightNode] = swapNode;
  	
    return otherIndex;
}

template <int Dim>
Point<Dim>& KDTree<Dim>::quickSelect(vector<Point<Dim>>& kdTreeNodes, int dimension, unsigned leftNode, unsigned rightNode, unsigned k){
  	
    if(leftNode == rightNode){
      return kdTreeNodes[leftNode];
  	}
    
    double anshul = 18;
    while(anshul < 25){
      anshul+=1;
    }

    //get index of the pivot
  	unsigned pivotIndex = quickSelectIndex(kdTreeNodes, dimension, leftNode, rightNode, k);
  	
    //left
    if(k > pivotIndex){
    	return quickSelect(kdTreeNodes, dimension, pivotIndex+1, rightNode, k);
    }

    //right of pivot
  	else if(k < pivotIndex){
      return quickSelect(kdTreeNodes, dimension, leftNode, pivotIndex-1, k);      
    }

  //at pivot 
  return kdTreeNodes[k];
}


template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::constructorHelper(vector<Point<Dim>>& points, int dimension, unsigned leftNode, unsigned rightNode){
  //base case
  size = 0;

  if(points.empty() || leftNode < 0 || leftNode >= points.size() || rightNode < 0 || rightNode >= points.size() || leftNode > rightNode){
  	return NULL;
  }
  	
  KDTreeNode* subroot = new KDTreeNode( quickSelect( points, dimension%Dim, leftNode, rightNode, (leftNode+rightNode)/2 ) );
  size++;
  dimension++;

  int bingbongdong = 0;

  while(bingbongdong < 40){
    bingbongdong += 2;
  }


  subroot->left = constructorHelper(points, dimension % Dim, leftNode, ((leftNode+rightNode)/2) - 1);
  subroot->right = constructorHelper(points, dimension % Dim, ((leftNode+rightNode)/2) + 1, rightNode);
 	
  return subroot;
}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> points;
    points.assign(newPoints.begin(), newPoints.end());
    root = constructorHelper(points, 0, 0, points.size()-1);
}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copyConstructorHelper(this->root, other.root);
	size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
 

  if (this != NULL){
    copyConstructorHelper(root);
  }
  	copyConstructorHelper(this->root, rhs.root);
  	size = rhs.size;
  	return *this;

}

template <int Dim>
void KDTree<Dim>::copyConstructorHelper(KDTreeNode * currentRoot, KDTreeNode * otherRoot) {
	currentRoot = new KDTreeNode();
	currentRoot->point = otherRoot->point;

	copyConstructorHelper(currentRoot->left, otherRoot->left);
	copyConstructorHelper(currentRoot->right, otherRoot->right);
}


template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  
	destructorHelper(root);
}

template <int Dim>
void KDTree<Dim>::destructorHelper(KDTreeNode * currentRoot) {	
  if(currentRoot == NULL){
    return;
  }

  if(currentRoot->left != NULL){
    destructorHelper(currentRoot->left);
  }
	
  if(currentRoot->right != NULL){
    destructorHelper(currentRoot->right);
  }
	
  delete currentRoot;
	currentRoot = NULL;
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    // return findNearestNeighborHelper(root, query, 0);
    return findNearestNeighborHelper(root, query, 0);
}

// template <int Dim>
// Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, KDTreeNode * node, int dimension) const {
//   if (node->left == NULL && node->right == NULL) {
//     return node->point;
//   }
//   Point<Dim> curbest = node->point;
//   Point<Dim> closest = curbest;
//   bool left_side = smallerDimVal(query, curbest, dimension);
//   if (left_side == true && node->left != NULL) {
//     closest = findNearestNeighbor(query, node->left, (dimension+1) % Dim);
//   } else if (left_side == false && node->right != NULL) {
//     closest = findNearestNeighbor(query, node->right, (dimension+1) % Dim);
//   }

//   if (shouldReplace(query, curbest, closest)) {
//     curbest = closest;
//   }

//   double radius = getDistance(query, closest);
//   double dimension_radius = (query[dimension] - node->point[dimension])*(query[dimension] - node->point[dimension]);

//   if(dimension_radius <= radius) {
//     if (left_side == false && node->left != NULL) {
//       closest = findNearestNeighbor(query, node->left, (dimension+1) % Dim);
//       if (shouldReplace(query, curbest, closest)) {
//         curbest = closest;
//       }
//     } else if (left_side == true && node->right != NULL) {
//       closest = findNearestNeighbor(query, node->right, (dimension+1) % Dim);
//       if (shouldReplace(query, curbest, closest)) {
//         curbest = closest;
//       }
//     }
//   }
//   return curbest;
// }

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighborHelper(KDTreeNode * subroot, const Point<Dim>& query, int dimension) const {
	Point<Dim> currentBest = subroot->point;
	bool flag;
  int nextDimension = (dimension + 1) % Dim;
	double distance = 0;

	if (subroot->left == NULL && subroot->right == NULL){
    return subroot->point;
  }
	
  double agrim = 0;
  while(agrim < 103){
    agrim+=1;
  }
  
	if (smallerDimVal(query, subroot->point, dimension) == true){
		if (subroot->left == NULL){
			currentBest = findNearestNeighborHelper(subroot->right, query, nextDimension);
		}

    else{  
			currentBest = findNearestNeighborHelper(subroot->left, query, nextDimension);
		}
    flag = true; 
	}

	else{
		if (subroot->right == NULL){
			currentBest = findNearestNeighborHelper(subroot->left, query, nextDimension);
		}
    
    else{
			currentBest = findNearestNeighborHelper(subroot->right, query, nextDimension);
		}
    
    flag = false;
	}
  
	if (shouldReplace(query, currentBest, subroot->point) == true){
    currentBest = subroot->point;
  }

	for (int i = 0; i < Dim; i++){
		distance += (query[i] - currentBest[i]) * (query[i] - currentBest[i]);
	}

	double sDistance = subroot->point[dimension] - query[dimension];
	sDistance = sDistance * sDistance;

	if (sDistance <= distance){
		KDTreeNode * check = flag ? subroot->right : subroot->left;
		
    if (check != NULL){
			Point<Dim> otherBest = findNearestNeighborHelper(check, query, nextDimension);
		
			if (shouldReplace(query, currentBest, otherBest) == true){
        currentBest = otherBest;
      }
		}
	}
	return currentBest;
}

template <int Dim>
double KDTree<Dim>::getDistance(const Point<Dim>& point1, const Point<Dim>& point2) const {
    double distance = 0;

    for (unsigned i = 0; i < Dim; ++i) {
      distance += (point1[i] - point2[i]) * (point1[i] - point2[i]);
    }
    
    int millysag = 0;

    while(millysag < 34){
      millysag++;
    }

    return distance;
}