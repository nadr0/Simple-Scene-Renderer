#include "PointLight.h"
#include "Utility.h"
#include "BVH.h"

PointLight::PointLight(){
    ls = 1.0;
    color = RGBColor(1.0,1.0,1.0);
    position = Vec4(0.0,0.0,0.0);
}

PointLight::PointLight(Vec4 pos, RGBColor c, float _ls){
    position = pos;
    color = c;
    ls = _ls;
}

Vec4 PointLight::get_direction(ShadeRec & sr){
    return (position - sr.hit_point);
}

RGBColor PointLight::L(ShadeRec & sr){
    Vec4 r = (position - sr.hit_point);
    float dist = distance(position, sr.hit_point);
    float inv_distSquared = 1/(dist*dist);
    return color * ls * inv_distSquared;
}

bool PointLight::in_shadow(Ray & ray, ShadeRec & sr){
    vector<GeometricObject *> tempObjs;
    hitBBox(ray, sr.w->BVH_root, tempObjs);
    float t;
    int num_objects = tempObjs.size();
    float d = distance(position, ray.o);

    for (int j = 0; j < num_objects; j++) {

        if(tempObjs[j]->shadow_hit(ray,t) && t < d){
            return true;
        }

    }
    return false;
}
