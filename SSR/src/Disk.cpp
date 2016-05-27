#include "Disk.h"


Disk::Disk(){
    kEpsilon = 0.00001;
    center = Vec4(0.0,0.0,0.0);
    normal = Vec4(0.0,0.0,1.0);
    radius = 1.0;
    compute_bbox();
}

Disk::Disk(Vec4 c, Vec4 n, float r){
    center = c;
    normal = n;
    radius = r;
    kEpsilon = 0.00001;
    compute_bbox();
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
