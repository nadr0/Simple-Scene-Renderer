#ifndef BVHFLAT_H_
#define BVHFLAT_H_

#include "BBox.h"
#include "GeometricObject.h"

class GeometricObject;

struct BVH_FLAT{
    BBox bbox;
    unsigned int offset;
    GeometricObject * obj;
};

#endif
