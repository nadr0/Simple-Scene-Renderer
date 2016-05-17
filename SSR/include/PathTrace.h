#ifndef PATHTRACE_H_
#define PATHTRACE_H_

#include "Tracer.h"

class PathTrace : public Tracer{
public:
    virtual RGBColor trace_ray(Ray & ray, int depth);
    PathTrace();
    PathTrace(World * w_ptr);
};
#endif
