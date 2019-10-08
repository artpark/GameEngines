#ifndef Sphere_h
#define Sphere_h

#include "../../vect.h"

class Sphere {
    public:
        Vec3 center;
        float radius;
        Vec3 color;
        Vec3 ambient;
        Vec3 diffuse;
        Vec3 specular;

        Sphere(Vec3 c, float r) : center(c), radius(r), color(Vec3(255,0,0)), ambient(Vec3(0.5,0.5,0.5)), diffuse(Vec3(0.5,0.5,0.5)), specular(Vec3(0.5,0.5,0.5)) {}
        Sphere(Vec3 c, float r, Vec3 col, Vec3 a, Vec3 d, Vec3 s) : center(c), radius(r), color(col), ambient(a), diffuse(d), specular(s) {}
};

#endif