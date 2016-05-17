#include <math.h>
#include "RGBColor.h"


RGBColor::RGBColor()
    :   r(0.0),
        g(0.0),
        b(0.0)
{}

RGBColor::RGBColor(float _r, float _g, float _b)
    :   r(_r),
        g(_g),
        b(_b)
{}

RGBColor::RGBColor(const RGBColor & color)
    :   r(color.r),
        g(color.g),
        b(color.b)
{}

std::ostream& operator<< (std::ostream &out, RGBColor &cRGBColor)
{
    out << "(" << cRGBColor.r << ", " << cRGBColor.g << ", " << cRGBColor.b << ")";
    return out;
}

RGBColor RGBColor::gamma_correction(float p){
    return (RGBColor(pow(r, p), pow(g, p), pow(b, p)));
}
