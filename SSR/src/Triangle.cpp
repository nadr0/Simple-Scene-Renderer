#include <iostream>
#include "Triangle.h"
#include "Mesh.h"

using std::cout;
using std::endl;

Triangle::Triangle(){
    a = Vec4(0.0,0.0,0.0);
    b = Vec4(0.0,0.0,0.0);
    c = Vec4(0.0,0.0,0.0);
    normal = Vec4(0.0,0.0,0.0);
    kEpsilon = 0.0001;
    light = false;
}

Triangle::Triangle(Vec4 & _a, Vec4 & _b, Vec4 & _c, Vec4 & _n){
    a = _a;
    b = _b;
    c = _c;
    normal = _n;
    kEpsilon = 0.0001;
    CENTER_POSITION = Vec4(0.0,0.0,0.0);
    CENTER_POSITION[0] = (a[0] + b[0] + c[0])/3;
    CENTER_POSITION[1] = (a[1] + b[1] + c[1])/3;
    CENTER_POSITION[2] = (a[2] + b[2] + c[2])/3;
    compute_BBox();
    light = false;
}

Vec4 Triangle::interpolated_normal(float beta, float gamma){
    Vec4 normal = ((1 - beta - gamma) * n0 + beta * n1 + gamma * n2);
    normal = normalize(normal);
    return normal;
}

bool Triangle::hit(Ray & ray, double & tmin, ShadeRec & sr){

    double a = this->a[0] - this->b[0], b = this->a[0] - this->c[0], c = ray.d[0], d = this->a[0] - ray.o[0];
    double e = this->a[1] - this->b[1], f = this->a[1] - this->c[1], g = ray.d[1], h = this->a[1] - ray.o[1];
    double i = this->a[2] - this->b[2], j = this->a[2] - this->c[2], k = ray.d[2], l = this->a[2] - ray.o[2];

    double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
    double q = g * i - e * k, s = e * j - f * i;

    double inv_denom  = 1.0 / (a * m + b * q + c * s);

    double e1 = d * m - b * n - c * p;
    double beta = e1 * inv_denom;

    if (beta < 0.0)
        return (false);

    double r = r = e * l - h * i;
    double e2 = a * n + d * q + c * r;
    double gamma = e2 * inv_denom;

    if (gamma < 0.0 )
        return (false);

    if (beta + gamma > 1.0)
        return (false);

    double e3 = a * p - b * r + d * s;
    double t = e3 * inv_denom;

    if (t < kEpsilon)
        return (false);

    tmin 				= t;
    sr.normal 			= normal;
    // sr.normal           = interpolated_normal(beta,gamma);
    sr.local_hit_point 	= ray.o + t * ray.d;

    return (true);

}

bool Triangle::shadow_hit(Ray & ray, float & tmin){
    double a = this->a[0] - this->b[0], b = this->a[0] - this->c[0], c = ray.d[0], d = this->a[0] - ray.o[0];
    double e = this->a[1] - this->b[1], f = this->a[1] - this->c[1], g = ray.d[1], h = this->a[1] - ray.o[1];
    double i = this->a[2] - this->b[2], j = this->a[2] - this->c[2], k = ray.d[2], l = this->a[2] - ray.o[2];

    double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
    double q = g * i - e * k, s = e * j - f * i;

    double inv_denom  = 1.0 / (a * m + b * q + c * s);

    double e1 = d * m - b * n - c * p;
    double beta = e1 * inv_denom;

    if (beta < 0.0)
        return (false);

    double r = r = e * l - h * i;
    double e2 = a * n + d * q + c * r;
    double gamma = e2 * inv_denom;

    if (gamma < 0.0 )
        return (false);

    if (beta + gamma > 1.0)
        return (false);

    double e3 = a * p - b * r + d * s;
    double t = e3 * inv_denom;

    if (t < kEpsilon)
        return (false);

    tmin 				= t;
        return (true);

}

void Triangle::compute_BBox(){
    double delta = 0.000001;

    bbox.minX = fmin(fmin(a[0], b[0]), c[0]) - delta;
    bbox.maxX = fmax(fmax(a[0], b[0]), c[0]) + delta;
    bbox.minY = fmin(fmin(a[1], b[1]), c[1]) - delta;
    bbox.maxY = fmax(fmax(a[1], b[1]), c[1]) + delta;
    bbox.minZ = fmin(fmin(a[2], b[2]), c[2]) - delta;
    bbox.maxZ = fmax(fmax(a[2], b[2]), c[2]) + delta;
}
