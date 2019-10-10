#ifndef Geometry_h
#define Geometry_h

#include "../../vect.h"
#include "../../color.h"

enum Texture_t {MAT, REFLECTIVE, SPECULAR};
class Geometry {
    public:
        Color_t color;
        Texture_t texture;
        Geometry(Color_t color_, Texture_t texture_=MAT) : color(color_), texture(texture_) {}
};

#endif