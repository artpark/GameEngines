#ifndef LightSource_h
#define LightSource_h

#include "../vect.h"

class LightSource {
public:
  Vec3 position;
  Vec3 intensity;

  LightSource(float x, float y, float z, Vec3 intensity_)
      : position(Vec3(x, y, z)), intensity(intensity_) {}
  LightSource(Vec3 p, Vec3 intensity_) : position(p), intensity(intensity_) {}
};

#endif