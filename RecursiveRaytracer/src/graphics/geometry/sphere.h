#ifndef Sphere_h
#define Sphere_h

#include "geometry.h"

class Sphere : public Geometry {
    public:
        Vec3 center;
        float radius;

        Sphere(float x, float y, float z, float r, Color_t color_, Texture_t texture_=MAT) : Geometry(color_, texture_), center(Vec3(x, y, z)), radius(r) {}
        Sphere(Vec3 c, float r, Color_t color_, Texture_t texture_=MAT) : Geometry(color_, texture_), center(c), radius(r) {}
};

#endif