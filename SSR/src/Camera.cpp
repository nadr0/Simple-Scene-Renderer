#include "Camera.h"
#include "Vec4.h"

Camera::Camera(){}

void Camera::set_eye(double x, double y, double z){
    eye[0] = x;
    eye[1] = y;
    eye[2] = z;
}

void Camera::set_lookat(double x, double y, double z){
    lookat[0] = x;
    lookat[1] = y;
    lookat[2] = z;
}

void Camera::set_view_distance(double _d){
    d = _d;
}

void Camera::compute_uvw(){
    up = Vec4(0,1,0);

    w = eye - lookat;
    w = normalize(w);
    u = cross(up,w);
    u = normalize(u);
    v = cross(w,u);

}
