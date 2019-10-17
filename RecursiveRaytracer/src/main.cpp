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

int main() {
  // Constants
  const uint32_t HEIGHT = 500;
  const uint32_t WIDTH = 500;
  const uint32_t RGB_MAX = 255;
  const uint32_t FOV = 90;
  const float SCALE = tan((FOV * 0.5) * M_PI / 180);
  const float ASPECT_RATIO = WIDTH / (float)HEIGHT;

  Scene scene = Scene();

  // Spheres
  Sphere sphere1 = Sphere(-1, 0, -12, 2);
  Sphere sphere2 = Sphere(0.5, -0.5, -8, 1.5);

  // Mesh Triangles
  Vec3 verts[4] = {{-5, -3, -6}, {5, -3, -6}, {5, -3, -16}, {-5, -3, -16}};
  uint32_t vertIndex[6] = {0, 1, 3, 1, 2, 3};
  Vec2 st[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
  MeshTriangle mesh = MeshTriangle(verts, vertIndex, 2, st);

  // Light source
  LightSource lightSource1 = LightSource(-20, 70, -20);
  LightSource lightSource2 = LightSource(30, 50, -12);

  scene.add(&sphere1);
  scene.add(&sphere2);
  scene.add(&mesh);
  scene.add(lightSource1);
  scene.add(lightSource2);

  ofstream outputImage("output.ppm");
  if (outputImage.is_open()) {
    /*
     *  "P3" means this is a RGB color image in ASCII
     *  "WIDTH HEIGHT" is the image's width and height
     *  "RBG_MAX" is the maximum value for each color
     */
    outputImage << "P3\n" << WIDTH << " " << HEIGHT << "\n" << RGB_MAX << "\n";
    // For each pixel, calculate the color using the raytracer
    for (uint32_t h = 0; h < HEIGHT; h++) {
      for (uint32_t w = 0; w < WIDTH; w++) {
        // Generating ray per pixel
        float rayX = (2 * (w + 0.5) / (float)WIDTH - 1) * ASPECT_RATIO * SCALE;
        float rayY = (1 - 2 * (h + 0.5) / (float)HEIGHT) * SCALE;

        Color_t pix_col = scene.trace(rayX, rayY);
        outputImage << (int)pix_col.r << ' ' << (int)pix_col.g << ' '
                    << (int)pix_col.b << "\n";
      }
    }
    outputImage.close();
  } else {
    cout << "Could not open the file";
  }

  return 0;
}