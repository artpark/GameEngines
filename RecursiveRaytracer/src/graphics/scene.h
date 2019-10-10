#ifndef Scene_h
#define Scene_h

#include "geometry/sphere.h"
#include "lightSource.h"
#include "camera.h"
#include "../vect.h"

#include <list>

using namespace std;

class Scene {
    public:
        list<Geometry*> geometries;
        list<LightSource*> lightSources; 

        Scene() {}

        void add(Geometry *g)
        {
            geometries.push_back(g);
        }

        void add(LightSource *l)
        {
            lightSources.push_back(l);
        }
};

#endif