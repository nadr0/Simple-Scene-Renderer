#ifndef CAMERA_H_
#define CAMERA_H_

#include "World.h"
#include "Vec4.h"

class Camera{
public:

    Camera();
    virtual void render_scene(World & w) = 0;
    void set_eye(double x, double y, double z);
    void set_lookat(double x, double y, double z);
    void set_view_distance(double d);
    void compute_uvw();

    Vec4 eye;
    Vec4 lookat;
    Vec4 up;
    Vec4 u;
    Vec4 v;
    Vec4 w;
    float d;
    float zoom;
    float exposure_time;

};
#endif
