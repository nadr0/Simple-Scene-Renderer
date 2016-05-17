#include <iostream>
#include "Camera.h"
#include "Pinhole.h"
#include "Viewplane.h"

using std::cout;
using std::endl;

Pinhole::Pinhole(){
    exposure_time = 1.0;
    zoom = 1.0;
}

void Pinhole::render_scene(World & w){
    RGBColor pixel_color;
    Ray ray;
    Viewplane vp = w.vp;
    Vec4 vp_point;
    Vec4 sp;
    vp.s /= zoom;

    float x;
    float y;

    ray.o = eye;
    for(int r = 0; r < vp.vres; r++){
        for(int c = 0; c < vp.hres; c++){
            pixel_color = RGBColor(0.0,0.0,0.0);

            for (int j = 0; j < vp.num_samples; j++) {
                sp = vp.sampler_ptr->sample_unit_square();

                ray.o[3] = 1.0;
                ray.d[3] = 0;

                vp_point[0] = vp.s * (c - 0.5 * vp.hres + sp.x());
                vp_point[1] = vp.s * (r - 0.5 * vp.vres + sp.y());

                // Set ray direction
                ray_direction(vp_point,ray.d);

                pixel_color += w.tracer_ptr->trace_ray(ray,0);
            }

            pixel_color /= vp.num_samples;
            pixel_color *= exposure_time;
            w.setPixel(vp.image, c, r, vp.hres, vp.vres, pixel_color);
        }
    }
}


void Pinhole::ray_direction(Vec4 & p, Vec4 & ray){
    ray = p[0] * u + p[1] * v - d * w;
}
