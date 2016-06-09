#include "Camera.h"
#include "Sampler.h"

class ThinLens: public Camera{
public:
    ThinLens();
    void ray_direction(Vec4 & point, Vec4 & lens_point, Ray & ray);
    virtual void render_scene(World &w);

    float lens_radius;
    float d;
    float f;
    float zoom;
    Sampler * sampler_ptr;
};
