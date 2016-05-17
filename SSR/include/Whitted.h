#ifndef WHITTED_H_
#define WHITTED_H_
#include "Tracer.h"

class Whitted : public Tracer{
public:
    virtual RGBColor trace_ray(Ray & ray, int depth);
    Whitted();
    Whitted(World * w_ptr);
};

#endif
