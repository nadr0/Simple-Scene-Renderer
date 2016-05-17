#include <stdio.h>
#include <ctime>
#include <iostream>
#include "Ray.h"
#include "Vec4.h"
#include "World.h"
#include "Utility.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using std::cout;
using std::endl;

int main(){
    system("clear");

    // Create World
    World world;

    // Build Scene
    world.build();

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
