#ifndef VIEWPLANE_H_
#define VIEWPLANE_H_
#include "Sampler.h"

class Viewplane{

public:

    int hres;                   /* Image width */
    int vres;                   /* Image height */

    unsigned char * image;      /* Image memory */
    double s;                   /* Pixel size */

    int IMAGE_RGB;              /* For IMAGE library */
    int maxDepth;               /* Recursive depth */

    float gamma;                /* Monitor gamma */
    float inv_gamma;

    Sampler * sampler_ptr;
    int num_samples;

    Viewplane();
    Viewplane(int _hres, int _vres);
    ~Viewplane();

};
#endif
