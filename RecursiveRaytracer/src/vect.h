#ifndef Vect_h
#define Vect_h

#include <cmath>

using namespace std;

class Vec3 {
    public:
        float X;
        float Y;
        float Z;
        Vec3(float x, float y, float z) : X(x), Y(y), Z(z) {}
};

#endif