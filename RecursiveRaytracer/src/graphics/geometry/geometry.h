#ifndef Geometry_h
#define Geometry_h

#include "../../vect.h"
#include "../../ray.h"
#include "../../color.h"

enum Texture_t {MAT, REFLECTIVE, SPECULAR};
class Geometry {
    public:
        Color_t color;
        Texture_t texture;

        Geometry(Color_t color_, Texture_t texture_=MAT) : color(color_), texture(texture_) {}

        virtual Vec3 get_normal(const Vec3& p) const = 0;
        virtual bool intersect(const Ray& ray, double& t) const = 0;
        const double SELF_AVOID_T = 1e-2;
};

#endif