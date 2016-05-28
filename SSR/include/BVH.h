#ifndef BVH_H_
#define BVH_H_
#include "GeometricObject.h"
#include "Ray.h"
#include "BVH_FLAT.h"
#include "BBox.h"
#include "Utility.h"

class GeometricObject;

class BVH{
public:
    // Bounding box for the node
    BBox bbox;

    // Binary tree structure
    BVH * left;
    BVH * right;
    BVH * parent;
    vector<GeometricObject *> objects;
    int index;
    int maxLeafNodeSize;

    BVH();
    BVH(int maxLeafNodeSize);
    void buildBVH(vector<GeometricObject *> objs, int AXIS);
    void flattenTree(vector<BVH_FLAT> & flat_arr, BVH * root ,int & counter);

};
#endif
