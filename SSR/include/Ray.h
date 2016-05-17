#ifndef RAY_H_
#define RAY_H_

#include "Vec4.h"

class Ray{
public:
    Vec4 o;                             /* Origin point */
    Vec4 d;                             /* Direction of Ray */

    Ray();
    Ray(Vec4 & origin, Vec4 & direction);
    Ray & operator= (Ray & rhs);        /* Assignment Operator */
};
#endif
