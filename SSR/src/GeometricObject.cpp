#include "GeometricObject.h"

Vec4 GeometricObject::sample(){
    return Vec4(0.0,0.0,0.0);
}

float GeometricObject::pdf(ShadeRec & sr){
    return 0.0;
}

Vec4 GeometricObject::get_normal(Vec4 p){
    return Vec4(0.0,0.0,0.0);
}
