#include <stdio.h>
#include <iostream>
#include "Viewplane.h"


Viewplane::Viewplane(){
    hres = 0;
    vres = 0;
    s = 1.0;
    image = 0;
    maxDepth = 1;
    IMAGE_RGB = 3;
    gamma = 1.8;
    inv_gamma = 0.5555555556;
}

Viewplane::Viewplane(int _hres, int _vres){
    gamma = 1.8;
    inv_gamma = 0.5555555556;
    hres = _hres;
    vres = _vres;
    s = 1.0;
    maxDepth = 6;
    IMAGE_RGB = 3;
    // Allocate image data
    image = (unsigned char *)calloc(hres*vres*IMAGE_RGB,sizeof(unsigned char));
    printf(" - - Image Setup Complete - - \n");
}

Viewplane::~Viewplane(){

}
