#include <stdio.h>
#include <vector>
#include <iostream>
#include "BVH.h"
#include "BVH_FLAT.h"
#include "BBox.h"
#include "GeometricObject.h"
#include "Utility.h"
using std::vector;
using std::endl;
using std::cout;

BVH::BVH(){
    bbox.minX = 0;
    bbox.minY = 0;
    bbox.minZ = 0;
    bbox.maxX = 0;
    bbox.maxY = 0;
    bbox.maxZ = 0;

    left = 0;
    right = 0;
    parent = 0;
    maxLeafNodeSize = 1;
}


BVH::BVH(int maxLNS){
    bbox.minX = 0;
    bbox.minY = 0;
    bbox.minZ = 0;
    bbox.maxX = 0;
    bbox.maxY = 0;
    bbox.maxZ = 0;

    left = 0;
    right = 0;
    parent = 0;
    maxLeafNodeSize = maxLNS;
}

void BVH::buildBVH(vector<GeometricObject *> objs, int AXIS){

    AXIS = AXIS % 3;
    int center;
    vector<GeometricObject *> tempObjs;

    // Base case.
    if(objs.size() <= 0){
        bbox.minX = 0;
        bbox.minY = 0;
        bbox.minZ = 0;
        bbox.maxX = 0;
        bbox.maxY = 0;
        bbox.maxZ = 0;
        left = 0;
        right = 0;
        parent = 0;
        return;
    }

    // If we want to store the objects in the leaf node now. maxLeafNodeSize will determine how many objects
    // will be in a leaf node. 1,2,3,5 ... etc..
    if(objs.size() <= maxLeafNodeSize){
        // Init first object to be max/min, then check all objects
        bbox.minX = objs[0]->bbox.minX;
        bbox.maxX = objs[0]->bbox.maxX;

        bbox.minY = objs[0]->bbox.minY;
        bbox.maxY = objs[0]->bbox.maxY;

        bbox.minZ = objs[0]->bbox.minZ;
        bbox.maxZ = objs[0]->bbox.maxZ;

        left = 0;
        right = 0;

        // Set the min/max values of the leaf node bounding box.
        for (int i = 0; i < objs.size(); i++) {

            if(objs[i]->bbox.minX < bbox.minX){
                bbox.minX = objs[i]->bbox.minX;
            }

            if(objs[i]->bbox.maxX > bbox.maxX){
                bbox.maxX = objs[i]->bbox.maxX;
            }

            if(objs[i]->bbox.minY < bbox.minY){
                bbox.minY = objs[i]->bbox.minY;
            }

            if(objs[i]->bbox.maxY > bbox.maxY){
                bbox.maxY = objs[i]->bbox.maxY;
            }

            if(objs[i]->bbox.minZ < bbox.minZ){
                bbox.minZ = objs[i]->bbox.minZ;
            }

            if(objs[i]->bbox.maxZ > bbox.maxZ){
                bbox.maxZ = objs[i]->bbox.maxZ;
            }


            if(parent != 0 && bbox.minX < parent->bbox.minX){
                parent->bbox.minX = bbox.minX;
            }

            if(parent != 0 && bbox.maxX > parent->bbox.maxX){
                parent->bbox.maxX = bbox.maxX;
            }

            if(parent != 0 && bbox.minY < parent->bbox.minY){
                parent->bbox.minY = bbox.minY;
            }

            if(parent != 0 && bbox.maxY > parent->bbox.maxY){
                parent->bbox.maxY = bbox.maxY;
            }

            if(parent != 0 && bbox.minZ < parent->bbox.minZ){
                parent->bbox.minZ  = bbox.minZ;
            }

            if(parent != 0 && bbox.maxZ > parent->bbox.maxZ){
                parent->bbox.maxZ = bbox.maxZ;
            }

            objects.push_back(objs[i]);

        }
        return;
    }

    center = (int)(objs.size()/2);

    for (int i = 0; i < objs.size(); i++) {
        tempObjs.push_back(objs[i]);
    }

    if(AXIS == 0){
        std::sort(tempObjs.begin(), tempObjs.end(), x_compare);
    }else if(AXIS == 1){
        std::sort(tempObjs.begin(), tempObjs.end(), y_compare);
    }else if(AXIS == 2){
        std::sort(tempObjs.begin(), tempObjs.end(), z_compare);
    }

    left = new BVH(maxLeafNodeSize);
    right = new BVH(maxLeafNodeSize);

    // set parent
    left->parent = this;
    right->parent = this;

    vector<GeometricObject *> left_array;
    vector<GeometricObject *> right_array;

    for (int i = 0; i < center; i++) {
        left_array.push_back(objs[i]);
    }

    for (int i = center; i < objs.size(); i++) {
        right_array.push_back(objs[i]);
    }

    left->buildBVH(left_array, AXIS+1);
    right->buildBVH(right_array, AXIS+1);

    if(parent != 0 && bbox.minX < parent->bbox.minX){
        parent->bbox.minX = bbox.minX;
    }

    if(parent != 0 && bbox.maxX > parent->bbox.maxX){
        parent->bbox.maxX = bbox.maxX;
    }

    if(parent != 0 && bbox.minY < parent->bbox.minY){
        parent->bbox.minY = bbox.minY;
    }

    if(parent != 0 && bbox.maxY > parent->bbox.maxY){
        parent->bbox.maxY = bbox.maxY;
    }

    if(parent != 0 && bbox.minZ < parent->bbox.minZ){
        parent->bbox.minZ  = bbox.minZ;
    }

    if(parent != 0 && bbox.maxZ > parent->bbox.maxZ){
        parent->bbox.maxZ = bbox.maxZ;
    }
}


// Assuming that the BVH tree only has 1 geometric object per BVH leaf node
void BVH::flattenTree(vector<BVH_FLAT> & flat_arr, BVH * root ,int & counter){

    BVH_FLAT bvh_flat;
    // offset of 0 is the base case
    bvh_flat.offset = 0;
    bvh_flat.bbox = root->bbox;
    // means it doesn't have an object
    bvh_flat.obj = nullptr;
    root->index = counter;
    counter++;
    flat_arr.push_back(bvh_flat);

    if(root->right == NULL && root->left == NULL){
        flat_arr[root->index].obj = root->objects[0];
    }

    if(root->left != NULL){
        flattenTree(flat_arr, root->left, counter);
    }

    if(root->right != NULL){
        flat_arr[root->index].offset = counter;// - root->index;
    }

    if(root->right != NULL){
        flattenTree(flat_arr, root->right, counter);
    }
}
