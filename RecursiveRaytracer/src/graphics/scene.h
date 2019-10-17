#ifndef Scene_h
#define Scene_h

#include "../vect.h"
#include "camera.h"
#include "geometry/meshTriangle.h"
#include "geometry/sphere.h"
#include "lightSource.h"

#include <iostream>
#include <list>

using namespace std;

class Scene {
public:
  list<Geometry *> geometries;
  list<LightSource> lightSources;

  Scene() {}

  void add(Geometry *g) { geometries.push_back(g); }

  void add(LightSource l) { lightSources.push_back(l); }

  Color_t Shading(const Ray &ray, const Geometry &hitGeometry, double t,
                  int depth) {
    // Vec3 rayOrig = ray.origin;
    // Vec3 rayDir = ray.direction;
    // Vec3 hitPoint = ray.origin + rayDir * t;
    // Vec3 normal;
    // Vec2 uv;
    // Vec2 st;
    // uint32_t index = 0;

    // hitGeometry.getSurfaceProperties(hitPoint, rayDir, index, uv, normal,
    // st); Vec3 tmp = hitPoint;

    switch (hitGeometry.materialType) {
    default:
      Color_t c = Color_t(255, 0, 0);
      return c;
    }
  }

  Color_t trace(float x, float y) {
    // This function works as the camera, translating pixels to rays
    Vec3 ray_origin = Vec3(0, 0, 0);
    Vec3 ray_direction = Vec3(x, y, -1).normalize();

    return trace_ray(Ray(ray_origin, ray_direction), 0, 50);
  }

  Color_t trace_ray(const Ray &ray, const Geometry *exclude_obj, int depth) {
    float tNearK = __FLT_MAX__;
    uint32_t indexK;
    Vec2 uvK;
    const Geometry *nearest_obj = nullptr;
    double tNear = __FLT_MAX__;

    for (const Geometry *geometry : geometries) {
      if ((*geometry).intersect(ray.origin, ray.direction, tNearK, indexK,
                                uvK) &&
          tNearK < tNear) {
        nearest_obj = geometry;
        tNear = tNearK;
      }
    }

    if (nearest_obj != nullptr) {
      return Shading(ray, *nearest_obj, tNearK, depth);
    }
    return Color_t(0, 0, 0);
  }
};

#endif