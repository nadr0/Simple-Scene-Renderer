#include "DirectionalLight.h"
#include "Utility.h"
#include "BVH.h"

DirectionalLight::DirectionalLight(){
    ls = 1.0;
    color = RGBColor(1.0,1.0,1.0);
    direction = Vec4(0.45,0.45,0.45);
}

DirectionalLight::DirectionalLight(Vec4 dir, RGBColor c, float _ls){
    direction = dir;
    color = c;
    ls = _ls;
}

Vec4 DirectionalLight::get_direction(ShadeRec & sr){
    return direction;
}

RGBColor DirectionalLight::L(ShadeRec & sr){
    return color * ls;
}

bool DirectionalLight::in_shadow(Ray & ray, ShadeRec & sr){
    vector<GeometricObject *> tempObjs;
    hitBBox(ray, sr.w->BVH_root, tempObjs);
    float t;
    int num_objects = tempObjs.size();
    float MAX_POSITION = std::numeric_limits<float>::max();
    Vec4 maxVecPosition = Vec4(MAX_POSITION, MAX_POSITION, MAX_POSITION);
    float d = distance(maxVecPosition, ray.o);

    for (int j = 0; j < num_objects; j++) {

        if(tempObjs[j]->shadow_hit(ray,t) && t < d){
            return true;
        }

    }
    return false;
}
