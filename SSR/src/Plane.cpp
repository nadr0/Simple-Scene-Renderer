#include "Plane.h"

Plane::Plane(){
    point = Vec4();
    normal = Vec4();
    kEpsilon = 0.00001;
    CENTER_POSITION = Vec4(0.0,0.0,0.0);
    bbox.minX = std::numeric_limits<float>::min();
    bbox.minY = std::numeric_limits<float>::min();
    bbox.minZ = std::numeric_limits<float>::min();
    bbox.maxX = std::numeric_limits<float>::max();
    bbox.maxY = std::numeric_limits<float>::max();
    bbox.maxZ = std::numeric_limits<float>::max();
    light = false;
}


Plane::Plane(Vec4 p, Vec4 n){
    point = p;
    normal = n;
    kEpsilon = 0.00001;
    CENTER_POSITION = point;
    bbox.minX = std::numeric_limits<float>::min();
    bbox.minY = std::numeric_limits<float>::min();
    bbox.minZ = std::numeric_limits<float>::min();
    bbox.maxX = std::numeric_limits<float>::max();
    bbox.maxY = std::numeric_limits<float>::max();
    bbox.maxZ = std::numeric_limits<float>::max();
    light = false;
}

bool Plane::hit(Ray & ray, double & tmin, ShadeRec & sr){
    double t = dot((point - ray.o), normal)/ dot(ray.d, normal);

    if(t > kEpsilon){
        tmin = t;
        sr.normal = normal;
        sr.local_hit_point = ray.o + (t * ray.d);
        return true;
    }else{
        return false;
    }
}

bool Plane::shadow_hit(Ray & ray, float & tmin){
    return false;
}
