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

  Vec3 Shading(const Ray &ray, const Geometry &hitGeometry, double t,
               int depth) {
    Vec3 rayOrig = ray.origin;
    Vec3 rayDir = ray.direction;
    Vec3 hitPoint = ray.origin + rayDir * t;
    Vec3 normal;
    Vec3 hitColor = Vec3(0, 0, 0);
    Vec2 uv;
    Vec2 st;
    uint32_t index = 0;

    hitGeometry.getSurfaceProperties(hitPoint, rayDir, index, uv, normal, st);
    Vec3 tmp = hitPoint;

    switch (hitGeometry.materialType) {
    default:
      Vec3 lightAmt = 0, specularColor = 0;
      Vec3 shadowPointOrig = (rayDir.dot(normal) < 0)
                                 ? hitPoint + normal * 0.00001
                                 : hitPoint - normal * 0.00001;
      for (const LightSource light : lightSources) {
        Vec3 lightDir = light.position - hitPoint;
        float lightDistance2 = lightDir.dot(lightDir);
        lightDir = lightDir.normalize();
        float LdotN = max(0.0, lightDir.dot(normal));
        Geometry *shadowHitObject = nullptr;
        float tNearShadow = __FLT_MAX__;
        bool inShadow = check_occlusion(shadowPointOrig, lightDir, index, uv) &&
                        tNearShadow * tNearShadow < lightDistance2;
        lightAmt = lightAmt + (light.intensity * LdotN * (1 - inShadow));
        Vec3 reflectionDirection = (lightDir * -1).reflect(normal);
        specularColor = specularColor +
                        (light.intensity *
                         powf(max(0.0, reflectionDirection.dot(rayDir) * -1),
                              hitGeometry.specularExponent));
      }
      hitColor = lightAmt * hitGeometry.evalDiffuseColor(st) * hitGeometry.Kd +
                 specularColor * hitGeometry.Ks;
    }
    cout << hitColor << "\n";
    return hitColor;
  }

  Vec3 trace(float x, float y) {
    // This function works as the camera, translating pixels to rays
    Vec3 ray_origin = Vec3(0, 0, 0);
    Vec3 ray_direction = Vec3(x, y, -1).normalize();

    return trace_ray(Ray(ray_origin, ray_direction), 0, 50);
  }

  Vec3 trace_ray(const Ray &ray, const Geometry *exclude_obj, int depth) {
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
    return Vec3(0, 0, 0);
  }

  bool check_occlusion(Vec3 target, Vec3 source, uint32_t &index, Vec2 &uv) {
    Vec3 toSource = source - target;
    float tLight = toSource.norm();
    Ray ray = Ray(target, toSource * (1.0 / tLight));
    float min_t = tLight;
    const Geometry *nearest_obj = nullptr;
    float t = __FLT_MAX__;
    for (const Geometry *geometry : geometries) {
      if ((*geometry).intersect(ray.origin, ray.direction, t, index, uv)) {
        if (min_t > t) {
          nearest_obj = geometry;
          min_t = t;
        }
      }
    }
    return nearest_obj == nullptr;
  }
};

#endif