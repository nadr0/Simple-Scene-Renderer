#ifndef RGBCOLOR_H_
#define RGBCOLOR_H_

#include<ostream>

class RGBColor{
public:

    float r, g, b;
    RGBColor();
    RGBColor(float _r, float _g, float _b);
    RGBColor(const RGBColor & color);
    friend std::ostream& operator<<(std::ostream &out, RGBColor & cRGBColor);
    // RGBColor operator =(RGBColor & rhs);
    void operator=(const RGBColor & rhs){ // >>>???
        if(this != &rhs){
            r = rhs.r;
            g = rhs.g;
            b = rhs.b;
        }
    }

    inline RGBColor& operator-=(const RGBColor &rhs) {
        r -= rhs.r;
        g -= rhs.g;
        b -= rhs.b;
        return *this;
    }

    inline RGBColor& operator*=(const RGBColor &rhs) {
        r *= rhs.r;
        g *= rhs.g;
        b *= rhs.b;
        return *this;
    }

    inline RGBColor& operator/=(const RGBColor &rhs) {
        r /= rhs.r;
        g /= rhs.g;
        b /= rhs.b;
        return *this;
    }

    inline RGBColor& operator*=(const double t) {
        r *= t;
        g *= t;
        b *= t;
        return *this;
    }

    inline RGBColor& operator/=(const double t) {
        r /= t;
        g /= t;
        b /= t;
        return *this;
    }
    RGBColor gamma_correction(float p);

    inline RGBColor& operator+=(const RGBColor &rhs) {
		r += rhs.r;
		g += rhs.g;
		b += rhs.b;
		return *this;
	}

};

inline RGBColor operator+(RGBColor lhs, const RGBColor& rhs) {
	lhs += rhs;
	return lhs;
}

inline RGBColor operator-(RGBColor lhs, const RGBColor& rhs) {
	lhs -= rhs;
	return lhs;
}

inline RGBColor operator*(RGBColor lhs, const RGBColor& rhs) {
	lhs *= rhs;
	return lhs;
}

inline RGBColor operator*(RGBColor lhs, const double& rhs) {
	lhs *= rhs;
	return lhs;
}

inline RGBColor operator/(RGBColor lhs, const RGBColor& rhs) {
	lhs /= rhs;
	return lhs;
}

inline RGBColor operator/(RGBColor lhs, const double rhs) {
	lhs /= rhs;
	return lhs;
}


#endif
