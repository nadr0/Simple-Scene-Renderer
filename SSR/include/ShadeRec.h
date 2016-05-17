#ifndef SHADREC_H_
#define SHADREC_H_

#include "Vec4.h"
#include "RGBColor.h"
#include "Ray.h"
#include "World.h"
#include "Material.h"

class World;

class ShadeRec{
public:
    ShadeRec(World * wr);
    ShadeRec(ShadeRec const &sr);

    bool hit_an_object;
    Vec4 local_hit_point;           /* untransformed point in world space */
    Vec4 normal;
    RGBColor color;
    Material * material_ptr;
    World * w;
    // Material * material_ptr;
    Ray ray;
    Vec4 hit_point;                 /* world coordinate of intersection*/
    double t;                       /* Ray parameter */
    int depth;                      /* Recursive depth */
    float u;                        /* Tex coord */
    float v;                        /* Tex coord */
};
#endif
