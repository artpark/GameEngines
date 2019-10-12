#ifndef Sphere_h
#define Sphere_h

#include "geometry.h"

class Sphere : public Geometry {
    public:
        Vec3 center;
        float radius;

        Sphere(float x, float y, float z, float r, Color_t color_, Texture_t texture_=MAT) : Geometry(color_, texture_), center(Vec3(x, y, z)), radius(r) {}
        Sphere(Vec3 c, float r, Color_t color_, Texture_t texture_=MAT) : Geometry(color_, texture_), center(c), radius(r) {}

        Vec3 get_normal(const Vec3& p) const {
            return ((p - center) * (-1/radius)).normalize();
        }

        bool intersect(const Ray& ray, double &t) const {
            Vec3 v = ray.origin - center;
            
            const double b = 2 * v.dot(ray.direction);
            const double c = v.dot(v) - radius * radius;
            double delta = b*b - 4 * c;
            if(delta < 0)
            {
                t = __FLT_MAX__;
                return false;
            }
            const double t1 = (-b - sqrt(delta)) / 2;
            const double t2 = (-b + sqrt(delta)) / 2;
            if(t2 < SELF_AVOID_T)
            {
                t = __FLT_MAX__;
                return false;
            }
            
            t = (t1 >= SELF_AVOID_T) ? t1 : t2;
            return true;
        }
};

#endif