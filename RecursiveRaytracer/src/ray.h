#ifndef Ray_h
#define Ray_h

#include "vect.h"

class Ray
{
public:
	Vec3 origin;
	Vec3 direction;

	Ray(Vec3 ori, Vec3 dir) : origin(ori), direction(dir) {}
};

#endif