#ifndef MESH_H_
#define MESH_H_

#include "World.h"
#include "Triangle.h"

class Triangle;

struct Vertex{
    float x;
    float y;
    float z;
};

struct Face{
    int i_0;
    int i_1;
    int i_2;
};

struct Normal{
    float x;
    float y;
    float z;
};

class Mesh{
public:
    vector<Vertex> vertices; // vertices for the mesh
    vector<Face> faces; //  faces for the mesh
    vector< vector<int> >  faceList; // stores the faces adjacent to a vertex
    vector<Vec4> perVertexNormals; // vertex normals
    vector<Triangle *> triangle_ptrs; // vertex normals
    World * wptr;
    Mesh();
    Mesh(World * wptr);

    Vec4 offset;
    float SCALE;
    RGBColor color;

    void readObject(char * fileName); //read the file to populate the vectors
    void trianglesToWorld();
    void calculateNormalList();
};
#endif
