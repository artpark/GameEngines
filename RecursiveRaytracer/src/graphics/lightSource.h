#ifndef LightSource_h
#define LightSource_h

#include "../vect.h"

class LightSource {
    public:
        Vec3 position;
        Color_t color;
        double intensity = 100;

        LightSource(float x, float y, float z, Color_t color_ = Color_t(255,255,255), double intensity_ = 100.0) : position(Vec3(x, y, z)), color(color_), intensity(intensity_) {}
        LightSource(Vec3 p, Color_t color_ = Color_t(255,255,255), double intensity_ = 100.0) : position(p), color(color_), intensity(intensity_) {}
};

#endif