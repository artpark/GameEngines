/*
 *  Citation: https://github.com/ChinksofLight/Ray-tracer/blob/master/vect.h
 */
#ifndef Vect_h
#define Vect_h

#include <cmath>
#include <ostream>

using namespace std;

class Vec3
{
public:
  float X;
  float Y;
  float Z;

  Vec3() : X(0), Y(0), Z(0) {}
  Vec3(float n) : X(n), Y(n), Z(n) {}
  Vec3(float x, float y, float z) : X(x), Y(y), Z(z) {}

  Vec3 operator+(const Vec3 &vec) const
  {
    return Vec3(X + vec.X, Y + vec.Y, Z + vec.Z);
  }

  Vec3 operator-(const Vec3 &vec) const
  {
    return Vec3(X - vec.X, Y - vec.Y, Z - vec.Z);
  }

  Vec3 operator-() const
  {
    return Vec3(-X, -Y, -Z);
  }

  Vec3 operator*(const double &scalar) const
  {
    return Vec3(scalar * X, scalar * Y, scalar * Z);
  }

  Vec3 operator*(const Vec3 &vec) const
  {
    return Vec3(X * vec.X, Y * vec.Y, Z * vec.Z);
  }

  Vec3 crossProduct(const Vec3 &vec) const
  {
    return Vec3(Y * vec.Z - Z * vec.Y, Z * vec.X - X * vec.Z,
                X * vec.Y - Y * vec.X);
  }

  Vec3 normalize() { return (*this) * (1 / norm()); }

  Vec3 reflect(const Vec3 &N) { return (*this) - N * 2 * (*this).dot(N); }

  double dot(const Vec3 &vec) const
  {
    return X * vec.X + Y * vec.Y + Z * vec.Z;
  }

  double norm() const { return sqrt(dot(*this)); }

  double norm2() const { return dot(*this); }

  friend ostream &operator<<(ostream &os, const Vec3 &v)
  {
    return os << v.X << ", " << v.Y << ", " << v.Z;
  }
};

class Vec2
{
public:
  float X;
  float Y;

  Vec2() : X(0), Y(0) {}
  Vec2(float n) : X(n), Y(n) {}
  Vec2(float x, float y) : X(x), Y(y) {}

  Vec2 operator*(const float &r) const { return Vec2(X * r, Y * r); }

  Vec2 operator+(const Vec2 &v) const { return Vec2(X + v.X, Y + v.Y); }
};

#endif