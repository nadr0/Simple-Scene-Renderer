#include <stdlib.h>
#include <iostream>
#include "Utility.h"
#include "RGBColor.h"
using std::cout;
using std::endl;


bool x_compare( GeometricObject* x,  GeometricObject* y) { return x->CENTER_POSITION[0] < y->CENTER_POSITION[0]; }
bool y_compare( GeometricObject* x,  GeometricObject* y) { return x->CENTER_POSITION[1] < y->CENTER_POSITION[1]; }
bool z_compare( GeometricObject* x,  GeometricObject* y) { return x->CENTER_POSITION[2] < y->CENTER_POSITION[2]; }


void hitBBox(Ray & ray, BVH * root, vector<GeometricObject *> & possible_hits){

    if(root->left == 0 && root->right == 0){
        for (int i = 0; i < root->objects.size();i++) {
            possible_hits.push_back(root->objects[i]);
        }
        return;
    }

    if(root->bbox.intersectRay(ray)){
            hitBBox(ray, root->left, possible_hits);
            hitBBox(ray, root->right, possible_hits);
    }


}

double length_of_V(Vec4 v){
    double x_2 = v[0]*v[0];
    double y_2 = v[1]*v[1];
    double z_2 = v[2]*v[2];

    return sqrt(x_2 + y_2 + z_2);
}
double length_of_V_squared(Vec4 v){
    return length_of_V(v)*length_of_V(v);
}

void bboxes(BVH * root){
    if(root == 0){
        return;
    }
    cout << "<-> "<< root->bbox << endl;
    if(root->parent != 0){
        cout << "---" << endl;
        cout << root->parent->bbox << endl;
        cout << "---" << endl;
    }
    bboxes(root->left);
    bboxes(root->right);
}
