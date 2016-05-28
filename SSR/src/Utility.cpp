#include <stdlib.h>
#include <stack>
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

void BVH_TRAVERSE(Ray & ray,vector<BVH_FLAT> & flat_arr,vector<GeometricObject *> & possible_hits){
    unsigned int nodeNum = 0;

    // Todo stack for further testing for intersections
    std::stack<unsigned int> todo;

    // Traverse the array
    while(true){

        // Current object
        BVH_FLAT curr_object = flat_arr[nodeNum];

        // Check if ray hits box
        if(curr_object.bbox.intersectRay(ray)){
            // Node has an object to test intersection with
            if(curr_object.obj != nullptr){

                possible_hits.push_back(curr_object.obj);

                if(todo.empty()){
                    break;
                }
                nodeNum = todo.top();
                todo.pop();
            }else{
                // No intersction test with the nodes objects

                // Put far BVH node on todo stack
                todo.push(curr_object.offset);
                // Advance to near node
                nodeNum = nodeNum + 1;
            }
        }else{
            if(todo.empty()){
                break;
            }
            nodeNum = todo.top();
            todo.pop();
        }
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
