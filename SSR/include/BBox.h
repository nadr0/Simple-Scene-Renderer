#ifndef BBOX_H_
#define BBOX_H_
#include<ostream>
#include "Ray.h"

class  BBox{
public:
    float minX;
    float minY;
    float minZ;
    float maxX;
    float maxY;
    float maxZ;
    BBox();
    BBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
    friend std::ostream& operator<<(std::ostream &out, BBox & bbox);
    bool intersectRay(Ray & ray);
    bool intersectP(Ray & ray, Vec4 & invDir, uint32_t dirIsNeg[3]);
    BBox & operator=(BBox & rhs);

};
#endif
