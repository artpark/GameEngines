#ifndef Scene_h
#define Scene_h

#include "geometry/sphere.h"
#include "lightSource.h"
#include "camera.h"
#include "../vect.h"

#include <list>
#include <iostream>

using namespace std;

class Scene {
    public:
        list<Geometry*> geometries;
        list<LightSource> lightSources; 

        Scene() {}

        void add(Geometry *g)
        {
            geometries.push_back(g);
        }

        void add(LightSource l)
        {
            lightSources.push_back(l);
        }

        Color_t Shading(const Ray& ray, const Geometry& geometry, double t, int depth)
        {          
            Vec3 intersect_point = ray.origin + ray.direction * t;
            Vec3 normal = geometry.get_normal(intersect_point);
    
            switch (geometry.texture){ 
            case MAT:
                //This was chinkOfLight's formula
                return (geometry.color).scale_by(normal.dot(ray.direction) * 0.5);
            case REFLECTIVE:
            {
                Color_t c = (geometry.color).scale_by(normal.dot(ray.direction) * 0.5); 
                if (depth > 0)
                    c = c+ trace_ray(Ray(intersect_point, (ray.direction - normal * ray.direction.dot(normal) * 2).normalize()), &geometry, depth -1);
                return c;
            }
            // case SPECULAR:
            // {
            //     Color_t c = Color_t(0, 0, 0);
            //     for (const LightSource& light: lightSources){
            //         Vec3 light2pos = light.position - intersect_point;
            //         //specular:
            //         if (check_occlusion(intersect_point, light.position)) {
            //             c = c + light.color.scale_by2(ray.reflect_by(normal).dot(light2pos.normalize())); // add check for occlusion
            //             //mat:
            //             c = c + (geometry.color).mix_with(light.color).scale_by(light.intensity / (light.position - intersect_point).norm2());
            //         }
            //     }
            //     //reflections:
            //     if (depth > 0)
            //         c = c + trace_ray(Ray(intersect_point, (ray.direction - normal * ray.direction.dot(normal) * 2).normalize()), &geometry, depth - 1);
            //     return c;
                
            // }
            default:
                //throw exception("unrecognized texture");// UNRECOGNIZED_TEXTURE
                exit(1);
            }
        }

        Color_t trace(int x, int y) 
        {
            // This function works as the camera, translating pixels to rays
            Vec3 ray_origin = Vec3(0, 0, -1000);
            Vec3 ray_direction = Vec3(x, y, 1250).normalize();

            return trace_ray(Ray(ray_origin, ray_direction), 0, 50);
	    }

	    Color_t trace_ray(const Ray& ray, const Geometry* exclude_obj, int depth)
        {
            double min_t = __FLT_MAX__;
            // int min_i = -1;
            const Geometry* nearest_obj = nullptr;

            double t = __FLT_MAX__;
            for (const Geometry* geometry : geometries) {
                    if ((*geometry).intersect(ray, t)) {
                        if (min_t > t) {
                            nearest_obj = geometry;
                
                            min_t = t;
                        }
                    }
            }
            if (nearest_obj != nullptr) 
            {
                return Shading(ray, *nearest_obj, min_t, depth);
            }
            return Color_t(0, 0, 0);
	    }
};

#endif