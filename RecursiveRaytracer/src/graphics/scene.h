#ifndef Scene_h
#define Scene_h

#include "./geometry/sphere.h"
#include "./lightSource.h"
#include "./camera.h"

#include <list>

using namespace std;

class Scene {
    public:
        list<Sphere> geometries;
        list<LightSource> lightSources; 
        Camera camera;
};

#endif