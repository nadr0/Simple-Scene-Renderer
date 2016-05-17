#include "Light.h"


Light::Light(){}

Vec4 Light::get_direction(ShadeRec & sr){
    return Vec4();
}

RGBColor Light::L(ShadeRec & sr){
    return RGBColor(0.0,0.0,0.0);
}

bool Light::in_shadow(Ray & ray, ShadeRec & sr){
    return false;
}

float Light::G(ShadeRec & sr){
    return 0.0;
}
float Light::pdf(ShadeRec & sr){
    return 0.0;
}
