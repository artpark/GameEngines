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

class Scene
{
public:
  list<Geometry *> geometries;
  list<LightSource> lightSources;

  Scene() {}

  void add(Geometry *g) { geometries.push_back(g); }

  void add(LightSource l) { lightSources.push_back(l); }

  Vec3 Shading(const Ray &ray, const Geometry &hitGeometry, double t,
               int depth)
  {
    Vec3 hitColor = Vec3(255, 255, 255);
    if (depth < 0)
    {
      return hitColor;
    }
    Vec3 rayOrig = ray.origin;
    Vec3 rayDir = ray.direction;
    Vec3 hitPoint = ray.origin + rayDir * t;
    Vec3 normal;
    Vec2 uv;
    Vec2 st;
    uint32_t index = 0;

    hitGeometry.getSurfaceProperties(hitPoint, rayDir, index, uv, normal, st);
    Vec3 tmp = hitPoint;

    switch (hitGeometry.materialType)
    {
    case (REFLECTION):
    {
      Vec3 reflectionDir = rayDir.reflect(normal).normalize();
      Vec3 reflectionRayOrig = (reflectionDir.dot(normal) < 0) ? hitPoint + normal * 0.00001 : hitPoint - normal * 0.00001;
      hitColor = trace_ray(Ray(reflectionRayOrig, reflectionDir), depth - 1);
      break;
    }
    case (REFLECTION_AND_REFRACTION):
    {
      break;
    }
    default: //DIFFUSE_AND_GLOSSY
    {
      Vec3 lightAmt = 0, specularColor = 0;
      Vec3 shadowPointOrig = (rayDir.dot(normal) < 0)
                                 ? hitPoint + normal * 0.00001
                                 : hitPoint - normal * 0.00001;
      for (const LightSource light : lightSources)
      {
        Vec3 lightDir = light.position - hitPoint;
        float lightDistance2 = lightDir.dot(lightDir);
        lightDir = lightDir.normalize();
        float LdotN = max(0.0, lightDir.dot(normal));
        Geometry *shadowHitObject = nullptr;
        bool inShadow = check_occlusion(hitPoint, lightDir, hitGeometry);
        lightAmt = lightAmt + (light.intensity * LdotN * (1 - inShadow));
        Vec3 reflectionDirection = (-lightDir).reflect(normal).normalize();
        specularColor = specularColor +
                        (light.intensity *
                         powf(max(0.0, -(reflectionDirection.dot(rayDir))),
                              hitGeometry.specularExponent));
      }
      //cout << st.X << " X " << st.Y << " Y\n";
      hitColor = hitGeometry.ambientColor * hitGeometry.Ka + lightAmt * hitGeometry.evalDiffuseColor(st) * hitGeometry.Kd +
                 specularColor * hitGeometry.Ks;
      break;
    }
    }
    return hitColor;
  }

  Vec3 trace(float x, float y)
  {
    // This function works as the camera, translating pixels to rays
    Vec3 ray_origin = Vec3(0, 0, 0);
    Vec3 ray_direction = Vec3(x, y, -1).normalize();

    return trace_ray(Ray(ray_origin, ray_direction), 50);
  }

  Vec3 trace_ray(const Ray &ray, int depth)
  {
    float tNearK = __FLT_MAX__;
    uint32_t indexK;
    Vec2 uvK;
    const Geometry *nearest_obj = nullptr;
    double tNear = __FLT_MAX__;

    for (const Geometry *geometry : geometries)
    {
      if ((*geometry).intersect(ray.origin, ray.direction, tNearK, indexK,
                                uvK) &&
          tNearK < tNear)
      {
        nearest_obj = geometry;
        tNear = tNearK;
      }
    }

    if (nearest_obj != nullptr)
    {
      return Shading(ray, *nearest_obj, tNearK, depth);
    }
    return Vec3(255, 255, 255);
  }

  bool check_occlusion(Vec3 source, Vec3 target, const Geometry &self)
  {
    float tNearK = __FLT_MAX__;
    uint32_t indexK;
    Vec2 uvK;
    const Geometry *nearest_obj = nullptr;
    double tNear = __FLT_MAX__;

    for (const Geometry *geometry : geometries)
    {
      if (geometry == &self)
      {
        continue;
      }
      if ((*geometry).intersect(source, target, tNearK, indexK,
                                uvK) &&
          tNearK < tNear)
      {
        nearest_obj = geometry;
        tNear = tNearK;
      }
    }

    if (nearest_obj != nullptr)
    {
      return true;
    }
    return false;
  }
};

#endif