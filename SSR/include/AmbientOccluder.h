#ifndef AMBIENTOCCLUDER_H_
#define AMBIENTOCCLUDER_H_

#include "Light.h"
#include "Sampler.h"

class AmbientOccluder : public Light{
public:

    AmbientOccluder();
    void set_sampler(Sampler * s_ptr);
    virtual Vec4 get_direction(ShadeRec & sr);
    virtual bool in_shadow(Ray & ray, ShadeRec & sr);
    virtual RGBColor L(ShadeRec & sr);

    Vec4 u,v,w;
    Sampler * sample_ptr;
    RGBColor min_amount;
    RGBColor color;
    float ls;

};


#endif
