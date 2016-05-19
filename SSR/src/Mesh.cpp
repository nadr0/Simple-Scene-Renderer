#include <stdio.h>
#include <vector>
#include "Mesh.h"
#include "Phong.h"
#include "Matte.h"
#include "RGBColor.h"
#include "Triangle.h"
#include "Reflective.h"

Mesh::Mesh(){
    this->wptr = nullptr;
    this->offset = Vec4(0.0,0.0,0.0);
    this->SCALE = 1;
}

Mesh::Mesh(World * wptr){
    this->wptr = wptr;
    this->offset = Vec4(0.0,0.0,0.0);
    this->SCALE = 1;
}
/*
 Name: trianglesToWorld
 ---------------------
 Purpose: Goes through the Mesh's populated data to create all the 3D triangles and put them into the world's scene
 ---------------------
 Parameters: NONE
 ---------------------
 Return value: NONE
 */
void Mesh::trianglesToWorld(){

    for(int i = 0; i < this->faces.size(); i++){
        Face currentFace = this->faces[i];

        Vertex v0 = this->vertices[currentFace.i_0];
        Vertex v1 = this->vertices[currentFace.i_1];
        Vertex v2 = this->vertices[currentFace.i_2];

        Vec4 V0 = SCALE*Vec4(v0.x, v0.y, v0.z) + offset;
        Vec4 V1 = SCALE*Vec4(v1.x, v1.y, v1.z) + offset;
        Vec4 V2 = SCALE*Vec4(v2.x, v2.y, v2.z) + offset;

        Vec4 xaxis = V1 - V0;
        Vec4 yaxis = V2 - V0;

        Vec4 n = cross(xaxis, yaxis);
        n = normalize(n);

        Triangle * myTriangle = new Triangle(V0, V1, V2,n);
        myTriangle->material_ptr = new Reflective();
        myTriangle->material_ptr->set_kd(0.0);
        myTriangle->material_ptr->set_ka(0.0);
        myTriangle->material_ptr->set_cd(RGBColor(0.0,0.0,0.0));
        myTriangle->material_ptr->set_ks(0.0);
        // myTriangle->material_ptr = new Matte();
        // myTriangle->material_ptr->set_kd(1.0);
        // myTriangle->material_ptr->set_ka(0.0);
        // myTriangle->material_ptr->set_cd(this->color);

        this->wptr->add_object(myTriangle);
    }
}
/*
 Name: readObject
 ---------------------
 Purpose: Opens a .obj and parses the faces and vertices to populate the Mesh's data structures to render later.
 ---------------------
 Parameters: c++ magic
 ---------------------
 Return value: c++ magic
 */
void Mesh::readObject(char * file_name){
    FILE * objFile;
    objFile = fopen(file_name, "r");

    float minVALUE = std::numeric_limits<float>::max();

    int vertices = 0;
    int faces = 0;

    /* Blank vertex for offsetting*/
    Vertex Off_Set_Vertex;

    Off_Set_Vertex.x = 0;
    Off_Set_Vertex.y = 0;
    Off_Set_Vertex.z = 0;

    /* Offset of the vertex array because verts start at 1*/
    this->vertices.push_back(Off_Set_Vertex);

    /* Offset for the faceLast since the vertices start counting at 1*/
    vector<int> list_Off_Set;
    faceList.push_back(list_Off_Set);

    /* Offset for the perVertexNormals since them vertices start counting at 1*/
    Normal normal_Off_Set;
    perVertexNormals.push_back(normal_Off_Set);


    while (1){

        char lineHeader[128];
        /* Read the first word of the line*/
        int res = fscanf(objFile, "%s", lineHeader);

        /* Stop at the end of the file*/
        if (res == EOF)
            break;

        /* Read in the vertices*/
        if (strcmp(lineHeader, "v") == 0){
            /* Add a facelist for every vertex read in*/
            vector<int> list;
            faceList.push_back(list);

            /* Count verts*/
            vertices++;

            /* Read and create vertex*/
            float x,y,z;
            fscanf(objFile, "%f %f %f\n", &x, &y, &z);
            Vertex  vert;
            vert.x = x; vert.y = y; vert.z = z;

            if(y < minVALUE){
                minVALUE = y;;
            }

            /* Store vertex*/
            this->vertices.push_back(vert);
        }

        /* Read in the faces*/
        if (strcmp(lineHeader, "f") == 0){
            faces++;
            /* Read face*/
            int x, y, z;
            fscanf(objFile, "%i %i %i\n", &x, &y, &z);

            /*
             -----------------------------------------
             THIS IS FOR PER VERTEX NORMAL CALCUATIONS
             -----------------------------------------
             Index the vertex with what line of face it is connected to
             _faces[0]  = f 1 2 3 = _verts[1]..2..3
             */
            faceList[x].push_back(faces);
            faceList[y].push_back(faces);
            faceList[z].push_back(faces);

            /* Create face*/
            Face f;
            f.i_0 = x; f.i_1 = y; f.i_2 = z;
            /* Store face*/
            this->faces.push_back(f);
        }

    }
    // printf("%f\n", minVALUE);
    fclose(objFile);
}