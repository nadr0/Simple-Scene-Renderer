#include <stdio.h>
#include <ctime>
#include <iostream>
#include "Ray.h"
#include "Vec4.h"
#include "World.h"
#include "Utility.h"
#include "Mesh.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using std::cout;
using std::endl;

int main(){
    system("clear");

    printf("%lu\n", sizeof(BVH_FLAT));
    // Create World
    World world;

    Mesh * COW = new Mesh(&world);
    char file_name[11] = "dragon.obj";
    COW->readObject(file_name);
    COW->SCALE = 5.0;
    // COW->SCALE = 2.0;
    // COW->SCALE = 1.0;
    // float minValue = -0.319838 * COW->SCALE; // COW
    // float minValue = -0.033310 * 75; // BUNNY
    // float minValue = -0.991233 * COW->SCALE;
    float minValue =  -0.705289 * COW->SCALE;
    COW->offset = Vec4(0.0,-minValue, 12.5);
    COW->color = RGBColor(1.0,1.0,1.0);
    COW->trianglesToWorld();
    COW->calculateNormalList();
    printf("%s Mesh Completed.\n", file_name);

    // Build Scene
    world.build();

    int GLOBAL_COUNT = 0;
    world.BVH_root->flattenTree(world.flat_BVH,world.BVH_root,GLOBAL_COUNT);


    // Timer
    std::clock_t start;
    double duration;
    start = std::clock();

    // Render Scene
    world.camera_ptr->render_scene(world);
    duration = (std::clock() - start)/(double) CLOCKS_PER_SEC;

    cout << " - - - - - - - - - - - - - - - - - - - "<< endl;
    cout << " - - RENDING TIME: " << duration << " seconds - - " << endl;
    cout << " - - - - - - - - - - - - - - - - - - - "<< endl;

    // Write image out
    world.draw_scene();
    printf(" - - Opening Image in Preview - - \n");

    system("open output.png");

    return 0;
}
