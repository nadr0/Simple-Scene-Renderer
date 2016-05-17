#include "Rectangle.h"
#include "MultiJitter.h"

Rectangle::Rectangle(){
    p0 = Vec4(0.0,0.0,0.0);
    a = Vec4(0.0,0.0,0.0);
    b = Vec4(0.0,0.0,0.0);;
    a_len_squared = 0.0;
    b_len_squared = 0.0;
    normal = Vec4(0.0,0.0,0.0);
    GeometricObject::normal = normal;
    area = 0.0;
    inv_area = 0.0;
    sampler_ptr = nullptr;
    kEpsilon = 0.001;
    compute_bbox();
    light = false;
}

Rectangle::Rectangle(Vec4 p0, Vec4 _a, Vec4 _b, Vec4 n){
    this->p0 = p0;
    this->a= _a;
    this->b = _b;
    this->normal = n;
    GeometricObject::normal = normal;
    a_len_squared = length_of_V_squared(a);
    b_len_squared = length_of_V_squared(b);
    area = length_of_V(a) * length_of_V(b);
    inv_area = 1.0/area;
    int samples = 512; // was 16...
    sampler_ptr = new MultiJitter(samples);
    kEpsilon = 0.001;
    compute_bbox();
    light = false;
}

void Rectangle::compute_bbox(){
    double delta = 0.0001;
    bbox.minX = fmin(p0[0], p0[0] + a[0] + b[0]) - delta;
    bbox.maxX = fmax(p0[0], p0[0] + a[0] + b[0]) + delta;
    bbox.minY = fmin(p0[1], p0[1] + a[1] + b[1]) - delta;
    bbox.maxY = fmax(p0[1], p0[1] + a[1] + b[1]) + delta;
    bbox.minZ = fmin(p0[2], p0[2] + a[2] + b[2]) - delta;
    bbox.maxZ = fmax(p0[2], p0[2] + a[2] + b[2]) + delta;
}

bool Rectangle::hit(Ray & ray, double &tmin, ShadeRec & sr){

    // Calculate t
    double t = dot((this->p0 - ray.o), normal)/ dot(ray.d, normal);

    if(t <= kEpsilon){
        return false;
    }
    Vec4 p = ray.o + t * ray.d;
    Vec4 d = p - p0;

    double ddota = dot(d,a);

    if (ddota < 0.0 || ddota > a_len_squared){
        return false;
    }

    double ddotb = dot(d,b);

    if(ddotb < 0.0 || ddotb > b_len_squared){
        return false;
    }

    sr.u = (p[0]-p0[0])/length_of_V(b);
    sr.v = (p[1]-p0[1])/length_of_V(a);

    tmin = t;
    sr.normal = normal;
    sr.local_hit_point = p;
    return true;

}
Vec4 Rectangle::get_normal(Vec4 p){
    return normal;
}
Vec4 Rectangle::sample(){
    Vec4 samplePoint = Vec4(0.0,0.0,0.0);
    samplePoint = sampler_ptr->sample_unit_square();
    return (p0 + (samplePoint[0] * a) + (samplePoint[1] * b));
}
float Rectangle::pdf(ShadeRec & sr){
    return inv_area;
}
bool Rectangle::shadow_hit(Ray & ray, float & tmin){
    // Calculate t
    double t = dot((this->p0 - ray.o), normal)/ dot(ray.d, normal);

    if(t <= kEpsilon){
        return false;
    }
    Vec4 p = ray.o + t * ray.d;
    Vec4 d = p - p0;

    double ddota = dot(d,a);

    if (ddota < 0.0 || ddota > a_len_squared){
        return false;
    }

    double ddotb = dot(d,b);

    if(ddotb < 0.0 || ddotb > b_len_squared){
        return false;
    }

    tmin = t;
    return true;
}
