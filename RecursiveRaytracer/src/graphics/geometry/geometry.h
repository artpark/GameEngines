#ifndef Geometry_h
#define Geometry_h

#include "../../color.h"
#include "../../ray.h"
#include "../../vect.h"
#include <cstdint>
#include <stdio.h>
#include <utility>

enum MaterialType
{
  DIFFUSE_AND_GLOSSY,
  REFLECTION_AND_REFRACTION,
  REFLECTION
};

bool solveQuadratic(const float &a, const float &b, const float &c, float &x0,
                    float &x1)
{
  float discr = b * b - 4 * a * c;
  if (discr < 0)
    return false;
  else if (discr == 0)
    x0 = x1 = -0.5 * b / a;
  else
  {
    float q = (b > 0) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
    x0 = q / a;
    x1 = c / q;
  }
  if (x0 > x1)
    swap(x0, x1);
  return true;
}

class Geometry
{
public:
  MaterialType materialType;
  float ior;
  float Ka, Kd, Ks;
  Vec3 ambientColor;
  Vec3 diffuseColor;
  float specularExponent;

  Geometry()
      : materialType(DIFFUSE_AND_GLOSSY), ior(1.3), Ka(0.5), Kd(0.8), Ks(0.2),
        ambientColor(0.05), diffuseColor(0.2), specularExponent(25) {}

  virtual ~Geometry() {}
  virtual void getSurfaceProperties(const Vec3 &, const Vec3 &,
                                    const uint32_t &, const Vec2 &, Vec3 &,
                                    Vec2 &) const = 0;
  virtual bool intersect(const Vec3 &, const Vec3 &, float &, uint32_t &,
                         Vec2 &) const = 0;
  virtual Vec3 evalDiffuseColor(const Vec2 &) const { return diffuseColor; }
  const double SELF_AVOID_T = 1e-2;
};

#endif