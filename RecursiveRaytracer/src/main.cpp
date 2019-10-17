/*
 *  Name: Thanut (Art) Parkeenvincha
 *  Class: CMPM 164 - Game Engines
 *  Date: 10/07/2019
 *  Homework #2: Recursive Ray-Tracing
 */

#include "./graphics/scene.h"
#include "ray.h"
#include "vect.h"

#include <cstdint>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
  // Constants
  const uint32_t HEIGHT = 500;
  const uint32_t WIDTH = 500;
  const uint32_t RGB_MAX = 255;
  const uint32_t FOV = 90;
  const float SCALE = tan((FOV * 0.5) * M_PI / 180);
  const float ASPECT_RATIO = WIDTH / (float)HEIGHT;

  Scene scene = Scene();

  // Spheres
  Sphere sphere1 = Sphere(-1.5, -1, -12, 2);
  sphere1.ambientColor = Vec3(1.0, 1.0, 0.0);
  sphere1.diffuseColor = Vec3(1.0, 0.0, 0.0);

  Sphere sphere2 = Sphere(1.5, -0.5, -8, 3);
  sphere2.ambientColor = Vec3(0.0, 1.0, 0.0);
  sphere2.diffuseColor = Vec3(1.0, 1.0, 0.0);
  sphere2.Ks = 1;
  sphere2.materialType = REFLECTION_AND_REFRACTION;

  Sphere sphere3 = Sphere(-2, -2.5, -6, 0.5);
  sphere3.ambientColor = Vec3(0.0, 0.0, 1.0);
  sphere3.diffuseColor = Vec3(0.0, 1.0, 0.0);
  sphere3.Ks = 1;

  // Mesh Triangles
  Vec3 floorVerts[4] = {{-8, -3, -2}, {8, -3, -2}, {8, -3, -20}, {-8, -3, -20}};
  uint32_t floorVertIndex[6] = {0, 1, 3, 1, 2, 3};
  Vec2 floorSt[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
  MeshTriangle floor = MeshTriangle(floorVerts, floorVertIndex, 2, floorSt);
  floor.Ka = 0;

  // Light source
  LightSource lightSource1 = LightSource(-20, 70, -20, 0.5);
  LightSource lightSource2 = LightSource(30, 50, -12, 1);

  scene.add(&sphere1);
  scene.add(&sphere2);
  scene.add(&sphere3);
  scene.add(&floor);
  scene.add(lightSource1);
  scene.add(lightSource2);

  ofstream outputImage("output.ppm");
  if (outputImage.is_open())
  {
    /*
     *  "P3" means this is a RGB color image in ASCII
     *  "WIDTH HEIGHT" is the image's width and height
     *  "RBG_MAX" is the maximum value for each color
     */
    outputImage << "P3\n"
                << WIDTH << " " << HEIGHT << "\n"
                << RGB_MAX << "\n";
    // For each pixel, calculate the color using the raytracer
    for (uint32_t h = 0; h < HEIGHT; h++)
    {
      for (uint32_t w = 0; w < WIDTH; w++)
      {
        // Generating ray per pixel
        float rayX = (2 * (w + 0.5) / (float)WIDTH - 1) * ASPECT_RATIO * SCALE;
        float rayY = (1 - 2 * (h + 0.5) / (float)HEIGHT) * SCALE;

        Vec3 pixCol = scene.trace(rayX, rayY);
        int r = (int)(255 * clamp(0, 1, pixCol.X));
        int g = (int)(255 * clamp(0, 1, pixCol.Y));
        int b = (int)(255 * clamp(0, 1, pixCol.Z));
        outputImage << r << ' ' << g << ' ' << b << "\n";
      }
    }
    outputImage.close();
  }
  else
  {
    cout << "Could not open the file";
  }

  return 0;
}