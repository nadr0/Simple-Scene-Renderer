#ifndef GEOMETRIC_OBJECT_H
#define GEOMETRIC_OBJECT_H

#include "Ray.h"
#include "ShadeRec.h"
#include "Material.h"
#include "Utility.h"
#include "BBox.h"

class ShadeRec;
class Material;

class GeometricObject{

public:
    BBox bbox;
    Vec4 normal;
    Material * material_ptr;
    Vec4 CENTER_POSITION;
    virtual bool hit(Ray & ray, double & tmin, ShadeRec & sr) = 0;
    virtual bool shadow_hit(Ray & ray, float & tmin) = 0;
    virtual Vec4 sample();
    virtual float pdf(ShadeRec & sr);
    virtual Vec4 get_normal(Vec4 p);
    bool light; 
};
#endif
