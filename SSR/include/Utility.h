#ifndef UTILITY_H_
#define UTILITY_H_
#include <math.h>
#include <stdlib.h>
#include "Vec4.h"
#include "RGBColor.h"
#include "BBox.h"
#include "GeometricObject.h"
#include "BVH.h"

class GeometricObject;
class BVH;

void hitBBox(Ray & ray, BVH * root, vector<GeometricObject *> & possible_hits);
void BVH_TRAVERSE(Ray & ray,vector<BVH_FLAT> & flat_arr,vector<GeometricObject *> & possible_hits);
void bboxes(BVH * root);

double length_of_V(Vec4 v);
double length_of_V_squared(Vec4 v);

const double 	PI 			= 3.1415926535897932384;
const double 	TWO_PI 		= 6.2831853071795864769;
const double 	PI_ON_180 	= 0.0174532925199432957;
const double 	invPI 		= 0.3183098861837906715;
const double 	invTWO_PI 	= 0.1591549430918953358;
const float 	invRAND_MAX = 1.0 / (float)RAND_MAX;
const RGBColor  red = RGBColor(1.0,0.0,0.0);
const RGBColor  black = RGBColor(0.0,0.0,0.0);
const RGBColor  white = RGBColor(1.0,1.0,1.0);

float rand_float(void);
float rand_float(int l, float h);
int	rand_int(int l, int h);
double distance(Vec4 a, Vec4 b);

bool  x_compare(GeometricObject* x, GeometricObject* y);
bool  y_compare(GeometricObject* x, GeometricObject* y);
bool  z_compare(GeometricObject* x, GeometricObject* y);

inline float
rand_float(int l, float h) {
	return (rand_float() * (h - l) + l);
}

inline int
rand_int(int l, int h) {
	return ((int) (rand_float(0, h - l + 1) + l));
}

inline float rand_float(void) {
	return((float)rand() * invRAND_MAX);
}


inline double distance(Vec4 a, Vec4 b){

    double x_m = a[0] - b[0];
    double y_m = a[1] - b[2];
    double z_m = a[2] - b[2];

    double d = sqrt((x_m*x_m) + (y_m * y_m) + (z_m * z_m));
    return (d);
}

#endif
