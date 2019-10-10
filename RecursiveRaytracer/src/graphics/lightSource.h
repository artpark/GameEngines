#ifndef LightSource_h
#define LightSource_h

#include "../vect.h"

class LightSource {
    public:
        Vec3 center;

        LightSource(float x, float y, float z) : center(Vec3(x, y, z)) {}
        LightSource(Vec3 c) : center(c) {}
};

#endif