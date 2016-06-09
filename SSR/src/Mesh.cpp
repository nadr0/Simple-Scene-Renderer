#include <iostream>
#include <stdio.h>
#include <vector>
#include "Mesh.h"
#include "Phong.h"
#include "Matte.h"
#include "RGBColor.h"
#include "Triangle.h"
#include "Reflective.h"
#include "Microfacet.h"

using std::cout;
using std::endl;

Mesh::Mesh(){
    this->wptr = nullptr;
    this->offset = Vec4(0.0,0.0,0.0);
    this->SCALE = 1;
    FILE_TYPE = -1;
}

Mesh::Mesh(World * wptr){
    this->wptr = wptr;
    this->offset = Vec4(0.0,0.0,0.0);
    this->SCALE = 1;
    FILE_TYPE = -1;
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

    Face currentFace;

    Vertex v0,v1,v2;
    Vec4 V0,V1,V2;
    Vec4 xaxis;
    Vec4 yaxis;
    Vec4 n;

    for(int i = 0; i < this->faces.size(); i++){
        currentFace = this->faces[i];

        v0 = this->vertices[currentFace.i_0];
        v1 = this->vertices[currentFace.i_1];
        v2 = this->vertices[currentFace.i_2];

        V0 = SCALE*Vec4(v0.x, v0.y, v0.z) + offset;
        V1 = SCALE*Vec4(v1.x, v1.y, v1.z) + offset;
        V2 = SCALE*Vec4(v2.x, v2.y, v2.z) + offset;

        xaxis = V1 - V0;
        yaxis = V2 - V0;

        n = cross(xaxis, yaxis);
        n = normalize(n);

        Triangle * myTriangle = new Triangle(V0, V1, V2,n);

        myTriangle->face[0] = currentFace.i_0;
        myTriangle->face[1] = currentFace.i_1;
        myTriangle->face[2] = currentFace.i_2;
        myTriangle->material_ptr = new Matte();
        myTriangle->material_ptr->set_kd(1.0);
        myTriangle->material_ptr->set_ka(0.50);
        myTriangle->material_ptr->set_cd(this->color);
        triangle_ptrs.push_back(myTriangle);
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

    int vertex_index = 0;
    int face_index = 0;

    /* Blank vertex for offsetting*/
    Vertex OFF_SET_VERTEX;
    vertices.push_back(OFF_SET_VERTEX);
    vertex_texture_coords.push_back(OFF_SET_VERTEX);
    vertex_normals.push_back(OFF_SET_VERTEX);

    /* Offset for the faceLast since the vertices start counting at 1*/
    vector<int> OFF_SET_FACELIST;
    faceList.push_back(OFF_SET_FACELIST);

    size_t something;
    while (1){
        char line[128];

        /* Read the first word of the line*/
        int res = fscanf(objFile, "%s", line);

        /* Stop at the end of the file*/
        if (res == EOF)
            break;


        if (strcmp(line, "v") == 0){
            // Vertex
            vector<int> vertex_faceList;
            faceList.push_back(vertex_faceList);

            vertex_index++;
            float x,y,z;
            fscanf(objFile,"%f %f %f\n", &x, &y, &z);


            Vertex current_vertex;
            // current_vertex.x = x;
            // current_vertex.y = y;
            // current_vertex.z = z;

            // for dragon
            current_vertex.x = x;
            current_vertex.y = z;
            current_vertex.z = -y;

            vertices.push_back(current_vertex);
        }
        else if(strcmp(line, "vt") == 0){
            // Vertex Texture Coodinates
            float u,v;
            fscanf(objFile,"%f %f\n", &u, &v);
            Vertex current_vertex_tex;
            current_vertex_tex.x = u;
            current_vertex_tex.y = v;
            current_vertex_tex.z = 0.0;

            vertex_texture_coords.push_back(current_vertex_tex);
        }
        else if(strcmp(line, "vn") == 0){
            // Vertex Normal
            float x,y,z;
            fscanf(objFile,"%f %f %f\n", &x, &y, &z);
            Vertex current_vertex_normal;
            current_vertex_normal.x = x;
            current_vertex_normal.y = y;
            current_vertex_normal.z = z;

            vertex_normals.push_back(current_vertex_normal);
        }
        else if (strcmp(line, "f") == 0){
            face_index++;

            int v0, v1, v2;
            int vn0, vn1, vn2;
            int vt0, vt1, vt2;
            int vars_set = -1;

            if(FILE_TYPE == 0 ){
                vars_set = fscanf(objFile,"%d %d %d\n",&v0,&v1,&v2);
            }else if(FILE_TYPE == 1){
                // Type : 1 = f 1// 2// 3//
                vars_set = fscanf(objFile,"%d// %d// %d//\n",&v0,&v1,&v2);
            }else if(FILE_TYPE == 2){
                // Type : 2 = f 1/1/ 2/2/ 3/3/
                vars_set = fscanf(objFile,"%d/%d/ %d/%d/ %d/%d/\n", &v0,&vt0,&v1,&vt1,&v2,&vt2);
            }else if(FILE_TYPE == 3){
                // Type : 3 = f 1//1 2//2 3//3
                vars_set = fscanf(objFile,"%d//%d %d//%d %d//%d\n", &v0,&vn0,&v1,&vn1,&v2,&vn2);
            }else if(FILE_TYPE == 3){
                // Type : 4 = f 1/1/1 2/2/2 3/3/3
                vars_set = fscanf(objFile,"%d/%d/%d %d/%d/%d %d/%d/%d\n", &v0,&vt0,&vn0,&v1,&vt1,&vn1,&v2,&vt2,&vn2);

            }

            faceList[v0].push_back(face_index);
            faceList[v1].push_back(face_index);
            faceList[v2].push_back(face_index);

            Face current_face;
            current_face.i_0 = v0;
            current_face.i_1 = v1;
            current_face.i_2 = v2;
            faces.push_back(current_face);
         }
    }
    printf("%s\n", "Finished Reading Object");
    fclose(objFile);
}


void Mesh::calculateNormalList(){

    /* Go through all vertices*/
    for(int i = 1; i < faceList.size(); i++){
        /* Normal for one vertex*/
        Vec4 sumNormal;
        sumNormal[0] = 0;
        sumNormal[1] = 0;
        sumNormal[2] = 0;

        /* Go through the adjacent faces to the vertex*/
        for(int j = 0; j < faceList[i].size(); j++){

            /* Get the face index*/
            int indexFace = faceList[i][j];
            /* Get the face*/
            Face currentFace = faces[indexFace];
            /* Get the vertices from the face indices*/
            Vertex v1  = vertices[currentFace.i_0];
            Vertex v2  = vertices[currentFace.i_1];
            Vertex v3  = vertices[currentFace.i_2];

            /* Compute the normal of the current face*/
            Vec4 A(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
            Vec4 B(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
            Vec4 aXb;

            /* Normal from each face*/
            aXb = cross(A,B);

            /* Add all the normals together*/
            sumNormal[0] += aXb[0];
            sumNormal[1] += aXb[1];
            sumNormal[2] += aXb[2];
        }

        /* The sum of the normalized vectors adjacent*/
        sumNormal = normalize(sumNormal);

        /* Store the vertex normal*/
        perVertexNormals.push_back(sumNormal);
    }

    for (int i = 0; i < triangle_ptrs.size(); i++) {

        Triangle * currentTriangle = triangle_ptrs[i];
        currentTriangle->n0 = perVertexNormals[currentTriangle->face[0]];
        currentTriangle->n1 = perVertexNormals[currentTriangle->face[1]];
        currentTriangle->n2 = perVertexNormals[currentTriangle->face[2]];

    }

    printf("%s\n", "Normals Calculated");
}

void Mesh::determineFileType(char * file_name){
    FILE * objFile;
    objFile = fopen(file_name, "r");
    if(objFile == NULL){
        perror("something happened");
    }
    char * line = (char *)calloc(0,128);
    // char * line;
    size_t something;

    int v0, v1, v2;
    int vn0, vn1, vn2;
    int vt0, vt1, vt2;

    while(1){

        int res = getline(&line,&something,objFile);

        if (res == -1){
            break;
        }

        // Type : 0 = f 1 2 3
        int vars_set = sscanf(line,"f %d %d %d\n",&v0,&v1,&v2);

        if(vars_set == 3){
            FILE_TYPE = 0;
            break;
        }

        // Type : 1 = f 1// 2// 3//
        vars_set = sscanf(line,"f %d// %d// %d//\n",&v0,&v1,&v2);
        if(vars_set == 3){
            FILE_TYPE = 1;
            break;
        }

        // Type : 2 = f 1/1/ 2/2/ 3/3/
        vars_set = sscanf(line,"f %d/%d/ %d/%d/ %d/%d/\n", &v0,&vt0,&v1,&vt1,&v2,&vt2);
        if(vars_set == 6){
            FILE_TYPE = 2;
            break;
        }

        // Type : 3 = f 1//1 2//2 3//3
        vars_set = sscanf(line,"f %d//%d %d//%d %d//%d\n", &v0,&vn0,&v1,&vn1,&v2,&vn2);
        if(vars_set == 6){
            FILE_TYPE = 3;
            break;
        }

        // Type : 4 = f 1/1/1 2/2/2 3/3/3
        vars_set = sscanf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d\n", &v0,&vt0,&vn0,&v1,&vt1,&vn1,&v2,&vt2,&vn2);
        if(vars_set == 9){
            FILE_TYPE = 4;
            break;
        }
    }
    free(line);
    fclose(objFile);
}
