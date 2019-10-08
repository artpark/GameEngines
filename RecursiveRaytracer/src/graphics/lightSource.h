#ifndef LightSource_h
#define LightSource_h

#include "../vect.h"

class LightSource {
    public:
        Vec3 center;

        LightSource(Vec3 c) : center(c) {}
};

#endif