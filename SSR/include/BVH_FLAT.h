#ifndef BVHFLAT_H_
#define BVHFLAT_H_

#include "BBox.h"
#include "GeometricObject.h"

class GeometricObject;

struct BVH_FLAT{
    BBox bbox;
    // GeometricObject * obj;
    uint32_t obj;
    uint32_t offset;
};
#endif
