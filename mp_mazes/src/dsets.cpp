/* Your code here! */
#include "dsets.h"
#include <vector>

void DisjointSets::addelements(int num) {
    for(int i = 1; i <= num; i++){
        disjointSet.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if (disjointSet[elem] < 0) {
        return elem;
    } 
    
    disjointSet[elem] = find(disjointSet[elem]);
    return disjointSet[elem];
    
}

void DisjointSets::setunion(int a, int b) {
    int rootIndexA = find(a);
    int rootIndexB = find(b);

    if (rootIndexA == rootIndexB) {
        return;
    }

    if (disjointSet[rootIndexA] <= disjointSet[rootIndexB]) {
        disjointSet[rootIndexA] += disjointSet[rootIndexB];
        disjointSet[rootIndexB] = rootIndexA;
    } 
    
    else {
        disjointSet[rootIndexB] += disjointSet[rootIndexA];
        disjointSet[rootIndexA] = rootIndexB;
    }
}

int DisjointSets::size(int elem) {
    return -disjointSet[find(elem)];
}
