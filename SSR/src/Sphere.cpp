#include <iostream>
#include <math.h>
#include "Sphere.h"
#include "Vec4.h"
#include "Utility.h"
#include "MultiJitter.h"

Sphere::Sphere(){
    kEpsilon = 0.001;
    light = false;
}

Sphere::Sphere(Vec4 & c, double r){
    kEpsilon = 0.001;
    center = c;
    radius = r;
    CENTER_POSITION = center;
    compute_BBox();
    int samples = 256;
    sampler_ptr = new MultiJitter(samples);
    sampler_ptr->map_samples_to_sphere();
    light = false;
}

bool Sphere::hit(Ray & ray, double & tmin, ShadeRec & sr){
    double 		t;
	Vec4	temp 	= ray.o - center;
	double 		a 		= dot(ray.d, ray.d);
	double 		b 		= 2.0 * dot(temp, ray.d);
	double 		c 		= dot(temp,temp) - radius * radius;
	double 		disc	= b * b - 4.0 * a * c;

	if (disc < 0.0)
		return(false);
	else {
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root

		if (t > kEpsilon) {
			tmin = t;
			sr.normal 	 = (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		}

		t = (-b + e) / denom;    // larger root

		if (t > kEpsilon) {
			tmin = t;
			sr.normal   = (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		}
	}

	return (false);

}

bool Sphere::shadow_hit(Ray & ray, float & tmin){
    double t;

    Vec4 temp = ray.o - center;
    double a = dot(ray.d, ray.d);
    double b = 2.0 * dot(temp,ray.d);
    double c = dot(temp,temp) - radius * radius;
    double disc = b*b - 4.0 * a * c;


    if(disc < 0){
        return false;
    }else{
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) /denom;

        if(t > this->kEpsilon){
            tmin = t;
            return true;
        }

        t = (-b + e);

        if(t > this->kEpsilon){
            tmin = t;
            return true;
        }
    }
    return false;
}

float Sphere::pdf(ShadeRec & sr){
    return 1/(4*PI*radius*radius);
}

Vec4 Sphere::get_normal(Vec4 p){
    Vec4 n = p;
    n = normalize(n);
    return n;
}

Vec4 Sphere::sample(){
    Vec4 samplePoint = Vec4(0.0,0.0,0.0);
    samplePoint = sampler_ptr->sample_sphere();
    samplePoint *= radius;
    return samplePoint;
}

/* Computes BBox of a sphere */
void Sphere::compute_BBox(){
    bbox.minX = center[0] - (radius);
    bbox.maxX = center[0] + (radius);

    bbox.minY = center[1] - (radius);
    bbox.maxY = center[1] + (radius);

    bbox.minZ = center[2] - (radius);
    bbox.maxZ = center[2] + (radius);
}
