#ifndef Sphere_h
#define Sphere_h

#include "geometry.h"
#include <iostream>

class Sphere : public Geometry {
public:
  Vec3 center;
  float radius, radius2;

  Sphere(float x, float y, float z, float r)
      : center(Vec3(x, y, z)), radius(r), radius2(r * r) {}
  Sphere(Vec3 c, float r) : center(c), radius(r), radius2(r * r) {}

  bool intersect(const Vec3 &orig, const Vec3 &dir, float &tnear,
                 uint32_t &index, Vec2 &uv) const {
    // analytic solution
    Vec3 L = orig - center;
    float a = dir.dot(dir);
    float b = 2 * dir.dot(L);
    float c = L.dot(L) - radius2;
    float t0, t1;
    if (!solveQuadratic(a, b, c, t0, t1))
      return false;
    if (t0 < 0)
      t0 = t1;
    if (t0 < 0)
      return false;
    tnear = t0;
    return true;
  }

  void getSurfaceProperties(const Vec3 &P, const Vec3 &I, const uint32_t &index,
                            const Vec2 &uv, Vec3 &N, Vec2 &st) const {
    N = (P - center).normalize();
  }
};

#endif