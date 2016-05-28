
#include <math.h>
#include <iostream>
#include <string>
#include "World.h"
#include "RGBColor.h"
#include "Utility.h"
#include "Sphere.h"
#include "MultiJitter.h"
#include "Sampler.h"
#include "Material.h"
#include "Matte.h"
#include "Phong.h"
#include "PathTrace.h"
#include "Plane.h"
#include "Triangle.h"
#include "Pinhole.h"
#include "BBox.h"
#include "Reflective.h"
#include "BVH.h"
#include "MultipleObjects.h"
#include "Emissive.h"
#include "DirectionalLight.h"
#include "Rectangle.h"
#include "Microfacet.h"
#include "AreaLight.h"
#include "AreaLighting.h"
#include "PointLight.h"
#include "GlossyReflector.h"
#include "Disk.h"
#include "AmbientOccluder.h"
#include "stb_image_write.h"

using std::cout;
using std::endl;

World::World()
    // :   background_color(0.0, 0.0, 0.0)
    :   background_color(0.75, 0.75, 0.75)
{
    vp = Viewplane(512,512); // hres,vres
}

/*  Set up the scene geometry
    Type of camera, tracer
*/
void World::build(void){
    // Sampler
    int numberOfSamples = 256;
    vp.sampler_ptr = new MultiJitter(numberOfSamples);
    vp.num_samples = vp.sampler_ptr->num_samples;

    // Camera
    camera_ptr = new Pinhole;
    camera_ptr->set_eye(0.0, 30.0, 70);
    camera_ptr->set_lookat(0.0,2.5,0.0);
    camera_ptr->set_view_distance(350);
    camera_ptr->compute_uvw();

    // Ray tracing method
    tracer_ptr = new MultipleObjects(this);     /* Determine tracer */
    // tracer_ptr = new AreaLighting(this);
    // tracer_ptr = new PathTrace(this);

    // Lighting
    // DirectionalLight * L1 = new DirectionalLight(Vec4(0.45,0.05,0.45), RGBColor(1.0,1.0,1.0),2.0);
    // PointLight * L1 =s new PointLight(Vec4(0.0,10,10.0),RGBColor(1.0,1.0,1.0),15.0);
    // add_light(L1);

    // height of the box.
    int HEIGHT = 25.0;

    Vec4 r1_p = Vec4(-6.25,25.0,6.25);
    Vec4 r1_a = Vec4(0.0,0.0,12.5);
    Vec4 r1_b = Vec4(12.5,0.0,0.0);
    Vec4 r1_n = Vec4(0.0,-1.0,0.0);

    // Emissive * emissive_ptr = new Emissive();
    // emissive_ptr->ls = 25.0;// 2.0

    // Rectangle * myRectangleTop = new Rectangle(r1_p,r1_a,r1_b,r1_n);
    // myRectangleTop->material_ptr = emissive_ptr;
    // add_object(myRectangleTop);
    //
    // Vec4 d1_c = Vec4(0.0,25.0,12.5);
    // Vec4 d1_n = Vec4(0.0,-1.0,0.0);
    // float d1_r = 2.5;
    // Disk * d1 = new Disk(d1_c, d1_n, d1_r);
    // d1->material_ptr = emissive_ptr;
    // add_object(d1);
    //
    // AreaLight * myAreaLight = new AreaLight();
    // myAreaLight->obj_ptr = d1;
    // myAreaLight->material_ptr = emissive_ptr;
    // add_light(myAreaLight);

    MultiJitter * sampler_ptr = new MultiJitter(256);
    AmbientOccluder * myLight = new AmbientOccluder();
    myLight->ls = 1.0;
    myLight->color = white;
    myLight->set_sampler(sampler_ptr);
    ambient_ptr = myLight;

    // Right Sphere.
    Vec4 s2_c = Vec4(7.5,3.5,18.0);
    Sphere * s2 = new Sphere(s2_c,3.5);
    s2->material_ptr = new Matte();
    s2->material_ptr->set_kd(1.0);
    s2->material_ptr->set_ka(0.25);
    s2->material_ptr->set_cd(RGBColor(1.0,1.0,1.0));
    // add_object(s2);

    // Left sphere.
    Vec4 s4_c = Vec4(-7.5,3.5,12.5);
    Sphere * s4 = new Sphere(s4_c,3.5);
    s4->material_ptr = new Matte();
    s4->material_ptr->set_kd(1.0);
    s4->material_ptr->set_ka(0.25);
    s4->material_ptr->set_cd(RGBColor(0.95,0.64,0.54));
    // add_object(s4);

    size_t numberOfSpheres = 5;
    float radius = 3.5;
    float offset = radius*3;
    float initial_x = (numberOfSpheres-1)*offset/2;
    float step = 1/(float)numberOfSpheres;
    for (size_t i = 0; i < numberOfSpheres; i++) {
        for (size_t j = 0; j < numberOfSpheres; j++) {
            Vec4 current_position = Vec4(-initial_x+(offset*j),radius,(offset * i));
            Sphere * current_sphere = new Sphere(current_position,radius);
            current_sphere->material_ptr = new Matte();
            current_sphere->material_ptr->set_kd(1.0);
            current_sphere->material_ptr->set_ka(0.90);
            current_sphere->material_ptr->set_cd(RGBColor((j*step)+step,(i*step)+step,0.2));
            add_object(current_sphere);
        }
    }


    // My cornell box

    // Floor.
    Vec4 floor_p = Vec4(-50.0,0.0,-50.0);
    Vec4 floor_a = Vec4(0.0,0.0,100.0);
    Vec4 floor_b = Vec4(100.0,0.0,0.0);
    Vec4 floor_n = Vec4(0.0,1.0,0.0);

    Rectangle * FLOOR = new Rectangle(floor_p,floor_a,floor_b,floor_n);
    FLOOR->material_ptr = new Matte();
    FLOOR->material_ptr->set_kd(1.0);
    FLOOR->material_ptr->set_ka(0.25);
    FLOOR->material_ptr->set_cd(RGBColor(0.80,0.80,0.80));
    add_object(FLOOR);

    // Left wall.
    Vec4 leftWall_p = Vec4(-12.5,0.0,0.0);
    Vec4 leftWall_a = Vec4(0.0,0.0,25.0);
    Vec4 leftWall_b = Vec4(0.0,HEIGHT,0.0);
    Vec4 leftWall_n = Vec4(1.0,0.0,0.0);

    Rectangle * LEFT_WALL = new Rectangle(leftWall_p,leftWall_a,leftWall_b,leftWall_n);
    LEFT_WALL->material_ptr = new Matte();
    LEFT_WALL->material_ptr->set_kd(1.0);
    LEFT_WALL->material_ptr->set_ka(0.0);
    LEFT_WALL->material_ptr->set_cd(RGBColor(1.0,0.2,0.2));
    // add_object(LEFT_WALL);

    // Right Wall.

    Vec4 rightWall_p = Vec4(12.5,0.0,0.0);
    Vec4 rightWall_a = Vec4(0.0,0.0,25.0);
    Vec4 rightWall_b = Vec4(0.0,HEIGHT,0.0);
    Vec4 rightWall_n = Vec4(-1.0,0.0,0.0);

    Rectangle * RIGHT_WALL = new Rectangle(rightWall_p,rightWall_a,rightWall_b,rightWall_n);
    RIGHT_WALL->material_ptr = new Matte();
    RIGHT_WALL->material_ptr->set_kd(1.0);
    RIGHT_WALL->material_ptr->set_ka(0.0);
    RIGHT_WALL->material_ptr->set_cd(RGBColor(0.2,1.0,0.2));
    // add_object(RIGHT_WALL);

    // Back Wall.

    Vec4 backWall_p = Vec4(-12.5,0.0,0.0);
    Vec4 backWall_a = Vec4(0.0,HEIGHT,0.0);
    Vec4 backWall_b = Vec4(25.0,0.0,0.0);
    Vec4 backWall_n = Vec4(0.0,0.0,1.0);

    Rectangle * BACK_WALL = new Rectangle(backWall_p,backWall_a,backWall_b,backWall_n);
    BACK_WALL->material_ptr = new Matte();
    BACK_WALL->material_ptr->set_kd(1.0);
    BACK_WALL->material_ptr->set_ka(0.0);
    BACK_WALL->material_ptr->set_cd(white);
    // add_object(BACK_WALL);

    // Ceiling.

    Vec4 ceiling_p = Vec4(-12.5,HEIGHT,0.0);
    Vec4 ceiling_a = Vec4(0.0,0.0,25.0);
    Vec4 ceiling_b = Vec4(25.0,0.0,0.0);
    Vec4 ceiling_n = Vec4(0.0,-1.0,0.0);

    Rectangle * CEILING = new Rectangle(ceiling_p,ceiling_a,ceiling_b,ceiling_n);
    CEILING->material_ptr = new Matte();
    CEILING->material_ptr->set_kd(1.0);
    CEILING->material_ptr->set_ka(0.0);
    CEILING->material_ptr->set_cd(white);
    // add_object(CEILING);


    BVH_root = new BVH(1);
    BVH_root->buildBVH(objects, 0);

    printf(" - - World Scene Complete - - \n");


}

/* Writes the image data to disk in a PNG */
void World::draw_scene(void){
    FILE * image_out = fopen("output.png","w+");

    int retVal = stbi_write_png("output.png", vp.hres, vp.vres, vp.IMAGE_RGB, vp.image, vp.hres * vp.IMAGE_RGB);

    if(retVal == 0){
        printf("stbi_write_png failed: Image failed to write to disk.\n");
    }

    printf(" - - Image Write To Disk Complete - - \n");

    // Close file pointer
    fclose(image_out);
}

void World::add_object(GeometricObject * object_ptr){
    objects.push_back(object_ptr);
}

void World::add_light(Light * light_ptr){
    lights.push_back(light_ptr);
}

ShadeRec World::hit_bare_bones_objects(Ray & ray){
    vector<GeometricObject *> tempObjs;
    hitBBox(ray, BVH_root, tempObjs);
    ShadeRec sr(this);
    double t;
    double tmin = std::numeric_limits<double>::max();
    size_t num_objects = tempObjs.size();
    Vec4 normal;
    Vec4 local_hit_point;
    sr.hit_an_object = false;

    for (int j = 0; j < num_objects; j++) {
       if(tempObjs[j]->hit(ray, t, sr) && (t < tmin)){
            sr.hit_an_object = true;
            tmin = t;
            sr.material_ptr = tempObjs[j]->material_ptr;
            sr.hit_point = ray.o + t * ray.d;
            normal = sr.normal;
            local_hit_point = sr.local_hit_point;
        }

    }

    if(sr.hit_an_object){
        sr.t = tmin;
        sr.normal = normal;
        sr.local_hit_point = local_hit_point;
    }
    return sr;
}

/*  Fixes out of gamut colors
    Finds the max RGB channel and divies the rest by that value
    to scale the color
*/
RGBColor World::fix_overflow(RGBColor & c){
    float maxValue = fmax(c.r,fmax(c.g,c.b));

    if(maxValue > 1.0){
        return (c/maxValue);
    }else{
        return c;
    }

}

/*  Writes a pixel value to the image data */
void World::setPixel(unsigned char * img, int x, int y, int width, int height, RGBColor & color){
    // Tone map
    color = fix_overflow(color);
    // Gamma correction
    color = color.gamma_correction(vp.inv_gamma);

    // Write pixel to the image, each channel
    *(img + ((height - y - 1)*3) * width + (x * 3)) = 255 * color.r;
    *(img + ((height - y - 1)*3) * width + (x * 3)+1) = 255 * color.g;
    *(img + ((height - y - 1)*3) * width + (x * 3)+2) = 255 * color.b;
}
