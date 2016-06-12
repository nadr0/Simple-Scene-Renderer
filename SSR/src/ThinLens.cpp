#include "ThinLens.h"
#include "MultiJitter.h"


ThinLens::ThinLens(){
    lens_radius = 1.0;
    d = 350.0;
    f = 50;
    zoom = 1.0;
    exposure_time = 1.0;

    int num_samples = 128;
    sampler_ptr = new MultiJitter(num_samples);
    sampler_ptr->map_samples_to_disk();

}

void ThinLens::ray_direction(Vec4 & point, Vec4 & lens_point, Ray & ray){
    Vec4 p;
    p[0] = point.x() * f / d;
    p[1] = point.y() * f / d;
    Vec4 dir = (p.x() - lens_point.x()) * u + (p.y() - lens_point.y()) * v - f * w;
    dir = normalize(dir);
    ray.d = dir;
}

void ThinLens::render_scene(World & w){
    RGBColor pixel_color;
    Ray ray;
    Viewplane vp = w.vp;
    Vec4 sp;
    Vec4 pp;
    Vec4 dp;
    Vec4 lp;
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

                pp[0] = vp.s * (c - 0.5 * vp.hres + sp.x());
                pp[1] = vp.s * (r - 0.5 * vp.vres + sp.y());

                dp = sampler_ptr->sample_disk();
                lp = dp * lens_radius;

                // Set ray direction
                ray.o = eye + lp.x() * u + lp.y() * v;
                ray_direction(pp,lp,ray);

                pixel_color += w.tracer_ptr->trace_ray(ray,0);
            }

            pixel_color /= vp.num_samples;
            pixel_color *= exposure_time;
            w.setPixel(vp.image, c, r, vp.hres, vp.vres, pixel_color);
        }
    }

}
