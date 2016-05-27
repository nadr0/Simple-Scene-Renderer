#include "Disk.h"


Disk::Disk(){
    kEpsilon = 0.00001;
    center = Vec4(0.0,0.0,0.0);
    normal = Vec4(0.0,0.0,1.0);
    radius = 1.0;
    area = PI;
    inv_area = 1/PI;
    compute_bbox();
    int samples = 64; // was 16...512
    sampler_ptr = new MultiJitter(samples);
    sampler_ptr->map_samples_to_disk();
}

Disk::Disk(Vec4 c, Vec4 n, float r){
    center = c;
    normal = n;
    radius = r;
    area = PI * r * r;
    inv_area = 1/(PI * r * r);
    kEpsilon = 0.00001;
    compute_bbox();
    int samples = 64; // was 16...512
    sampler_ptr = new MultiJitter(samples);
    sampler_ptr->map_samples_to_disk();
}

Vec4 Disk::get_normal(Vec4 p){
    return normal;
}
Vec4 Disk::sample(){
    Vec4 samplePoint = Vec4(0.0,0.0,0.0);
    samplePoint = sampler_ptr->sample_disk();
    return center + (samplePoint*radius);
}
float Disk::pdf(ShadeRec & sr){
    return inv_area;
}

bool Disk::hit(Ray & ray, double & tmin, ShadeRec & sr){
    double t = dot((center - ray.o), normal)/ dot(ray.d, normal);

    if(t > kEpsilon){
        tmin = t;
        sr.normal = normal;
        sr.local_hit_point = ray.o + (t * ray.d);
        Vec4 v = sr.local_hit_point - center;
        if(dot(v,v) < radius * radius){
            return true;
        }
    }
    return false;
}

bool Disk::shadow_hit(Ray & ray, float & tmin){
    double t = dot((center - ray.o), normal)/ dot(ray.d, normal);

    if(t > kEpsilon){
        tmin = t;
        Vec4 p = ray.o + (t * ray.d);
        Vec4 v = p - center;
        if(dot(v,v) < radius * radius){
            return true;
        }
    }
    return false;
}

void Disk::compute_bbox(){
    bbox.minX = -radius + center.x();
    bbox.maxX = radius + center.x();
    bbox.minY = -radius + center.y();
    bbox.maxY = radius + center.y();
    bbox.minZ = -radius + center.z();
    bbox.maxZ = radius + center.z();
}
