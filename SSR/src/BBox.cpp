#include <iostream>
#include "BBox.h"

using std::cout;
using std::endl;

std::ostream& operator<< (std::ostream &out, BBox & bbox)
{
    out << "minX: " << bbox.minX << "~" << "maxX: " << bbox.maxX << endl << "minY: " << bbox.minY << "~" << "maxY: " << bbox.maxY << endl << "minZ: " << bbox.minZ << "~" << "maxZ: " << bbox.maxZ << endl;
    return out;
}

BBox::BBox(){
    minX = 0;
    minY = 0;
    minZ = 0;
    maxX = 0;
    maxY = 0;
    maxZ = 0;
}

BBox::BBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ){
    this->minX = minX;
    this->minY = minY;
    this->minZ = minZ;
    this->maxX = maxX;
    this->maxY = maxY;
    this->maxZ = maxZ;
}

/* BBox assignment operator*/
BBox & BBox::operator =(BBox & rhs){
    if(this != &rhs){
        minX = rhs.minX;
        maxX = rhs.maxX;
        minY = rhs.minY;
        maxY = rhs.maxY;
        minZ = rhs.minZ;
        maxZ = rhs.maxZ;
    }
    return *this;
}

bool BBox::intersectRay(Ray & ray){

    double ox = ray.o[0]; double oy = ray.o[1]; double oz = ray.o[2];
    double dx = ray.d[0]; double dy = ray.d[1]; double dz = ray.d[2];

    double tx_min, ty_min, tz_min;
    double tx_max, ty_max, tz_max;

    double a = 1.0 / dx;
    if (a >= 0) {
        tx_min = (minX - ox) * a;
        tx_max = (maxX - ox) * a;
    }
    else {
        tx_min = (maxX - ox) * a;
        tx_max = (minX - ox) * a;
    }

    double b = 1.0 / dy;
    if (b >= 0) {
        ty_min = (minY - oy) * b;
        ty_max = (maxY - oy) * b;
    }
    else {
        ty_min = (maxY - oy) * b;
        ty_max = (minY - oy) * b;
    }

    double c = 1.0 / dz;
    if (c >= 0) {
        tz_min = (minZ - oz) * c;
        tz_max = (maxZ - oz) * c;
    }
    else {
        tz_min = (maxZ - oz) * c;
        tz_max = (minZ - oz) * c;
    }

    double t0, t1;

    // find largest entering t value

    if (tx_min > ty_min)
        t0 = tx_min;
    else
        t0 = ty_min;

    if (tz_min > t0)
        t0 = tz_min;

    // find smallest exiting t value

    if (tx_max < ty_max)
        t1 = tx_max;
    else
        t1 = ty_max;

    if (tz_max < t1)
        t1 = tz_max;

    return (t0 < t1 && t1 > 0.0001);
}


bool BBox::intersectP(Ray & ray, Vec4 & invDir, uint32_t dirIsNeg[3]){
    float tmin, tmax, tymin, tymax, tzmin, tzmax;
    Vec4 bounds[2];
    bounds[0] = Vec4(minX, minY, minZ);
    bounds[1] = Vec4(maxX, maxY, maxZ);

    tmin = (bounds[dirIsNeg[0]].x() - ray.o.x()) * invDir.x();
    tmax = (bounds[1-dirIsNeg[0]].x() - ray.o.x()) * invDir.x();
    tymin = (bounds[dirIsNeg[1]].y() - ray.o.y()) * invDir.y();
    tymax = (bounds[1-dirIsNeg[1]].y() - ray.o.y()) * invDir.y();
    if ( (tmin > tymax) || (tymin > tmax) )
        return false;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;
        tzmin = (bounds[dirIsNeg[2]].z() - ray.o.z()) * invDir.z();
        tzmax = (bounds[1-dirIsNeg[2]].z() - ray.o.z()) * invDir.z();
    if ( (tmin > tzmax) || (tzmin > tmax) )
        return false;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;
    return ( (tmin < INFINITY) && (tmax > 0.f) );
}
