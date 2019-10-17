#ifndef MeshTriangle_h
#define MeshTriangle_h

#include "../../vect.h"
#include "geometry.h"
#include <cstring>
#include <iostream>
#include <memory>

inline Vec3 mix(const Vec3 &a, const Vec3 &b, const float &mixValue)
{
  return a * (1 - mixValue) + b * mixValue;
}

bool rayTriangleIntersect(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2,
                          const Vec3 &orig, const Vec3 &dir, float &tnear,
                          float &u, float &v)
{
  Vec3 edge1 = v1 - v0;
  Vec3 edge2 = v2 - v0;
  Vec3 pvec = dir.crossProduct(edge2);
  float det = edge1.dot(pvec);
  if (det == 0 || det < 0)
    return false;

  Vec3 tvec = orig - v0;
  u = tvec.dot(pvec);
  if (u < 0 || u > det)
    return false;

  Vec3 qvec = tvec.crossProduct(edge1);
  v = dir.dot(qvec);
  if (v < 0 || u + v > det)
    return false;

  float invDet = 1 / det;

  tnear = edge2.dot(qvec) * invDet;
  u *= invDet;
  v *= invDet;

  return true;
}

class MeshTriangle : public Geometry
{
public:
  unique_ptr<Vec3[]> vertices;
  uint32_t numTriangles;
  unique_ptr<uint32_t[]> vertexIndex;
  unique_ptr<Vec2[]> stCoordinates;

  MeshTriangle(const Vec3 *verts, const uint32_t *vertsIndex,
               const uint32_t &numTris, const Vec2 *st)
  {
    uint32_t maxIndex = 0;
    for (uint32_t i = 0; i < numTris * 3; ++i)
      if (vertsIndex[i] > maxIndex)
        maxIndex = vertsIndex[i];
    maxIndex += 1;
    vertices = unique_ptr<Vec3[]>(new Vec3[maxIndex]);
    memcpy(vertices.get(), verts, sizeof(Vec3) * maxIndex);
    vertexIndex = unique_ptr<uint32_t[]>(new uint32_t[numTris * 3]);
    memcpy(vertexIndex.get(), vertsIndex, sizeof(uint32_t) * numTris * 3);
    numTriangles = numTris;
    stCoordinates = unique_ptr<Vec2[]>(new Vec2[maxIndex]);
    memcpy(stCoordinates.get(), st, sizeof(Vec2) * maxIndex);
  }

  bool intersect(const Vec3 &orig, const Vec3 &dir, float &tnear,
                 uint32_t &index, Vec2 &uv) const
  {
    bool intersect = false;
    for (uint32_t k = 0; k < numTriangles; ++k)
    {
      const Vec3 &v0 = vertices[vertexIndex[k * 3]];
      const Vec3 &v1 = vertices[vertexIndex[k * 3 + 1]];
      const Vec3 &v2 = vertices[vertexIndex[k * 3 + 2]];
      float t, u, v;
      if (rayTriangleIntersect(v0, v1, v2, orig, dir, t, u, v) && t < tnear)
      {
        tnear = t;
        uv.X = u;
        uv.Y = v;
        index = k;
        intersect |= true;
      }
    }

    return intersect;
  }

  void getSurfaceProperties(const Vec3 &P, const Vec3 &I, const uint32_t &index,
                            const Vec2 &uv, Vec3 &N, Vec2 &st) const
  {
    const Vec3 &v0 = vertices[vertexIndex[index * 3]];
    const Vec3 &v1 = vertices[vertexIndex[index * 3 + 1]];
    const Vec3 &v2 = vertices[vertexIndex[index * 3 + 2]];
    Vec3 e0 = (v1 - v0).normalize();
    Vec3 e1 = (v2 - v1).normalize();
    N = (e0.crossProduct(e1)).normalize();
    const Vec2 &st0 = stCoordinates[vertexIndex[index * 3]];
    const Vec2 &st1 = stCoordinates[vertexIndex[index * 3 + 1]];
    const Vec2 &st2 = stCoordinates[vertexIndex[index * 3 + 2]];
    st = st0 * (1 - uv.X - uv.Y) + st1 * uv.X + st2 * uv.Y;
  }

  Vec3 evalDiffuseColor(const Vec2 &st) const
  {
    float scale = 5;
    float pattern =
        (fmodf(st.X * scale, 1) > 0.5) ^ (fmodf(st.Y * scale, 1) > 0.5);
    return mix(Vec3(0.815, 0.235, 0.031), Vec3(0.937, 0.937, 0.231), pattern);
  }
};

#endif