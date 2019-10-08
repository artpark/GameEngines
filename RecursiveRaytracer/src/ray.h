/*
 *  Citation: https://github.com/ChinksofLight/Ray-tracer/blob/master/ray.h
 */
#ifndef Ray_h
#define Ray_h

#include "vect.h"

class Ray {
	public:
		Vec3 origin;
		Vec3 direction;

		Ray(Vec3 ori, Vec3 dir) : origin(ori), direction(dir) {}
		
		Vec3 get_point(double t) const{
			return origin + direction * t;
		}
		Vec3 reflect_by(const Vec3& normal) const{
			return direction - normal * normal.dot(direction) * 2;
		}
};

#endif