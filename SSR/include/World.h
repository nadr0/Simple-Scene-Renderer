#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include "Viewplane.h"
#include "RGBColor.h"
#include "Tracer.h"
#include "ShadeRec.h"
#include "GeometricObject.h"
#include "Camera.h"
#include "Light.h"
#include "BVH.h"

class Viewplane;
class Tracer;
class ShadeRec;
class Camera;
class Light;
class GeometricObject;
class BVH;

using std::vector;

class World{
public:

    Viewplane vp;                /* Viewplane with image data*/
    Tracer * tracer_ptr;         /* Style of ray tracing */
    RGBColor background_color;   /* Background color for the image */

    BVH * BVH_root;

    World();
    void build(void);
    void draw_scene(void);
    ShadeRec hit_bare_bones_objects(Ray & ray);

    RGBColor fix_overflow(RGBColor & c);

    vector<GeometricObject *> objects;              /* Scene objects */
    void add_object(GeometricObject * object_ptr);  /* Add objecst to scene*/
    vector<Light *> lights;                          /* Lights */
    void add_light(Light * light_ptr);
    void setPixel(unsigned char * img, int x, int y, int width, int height, RGBColor & color);

    Camera * camera_ptr;


};
#endif
