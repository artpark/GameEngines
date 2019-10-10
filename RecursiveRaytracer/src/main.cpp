/*
 *  Name: Thanut (Art) Parkeenvincha
 *  Class: CMPM 164 - Game Engines
 *  Date: 10/07/2019
 *  Homework #2: Recursive Ray-Tracing
 */
 
#include "./graphics/scene.h"
#include "vect.h"

#include <iostream>
#include <fstream>
#include <cstdint>

using namespace std;

int main()
{
    // Constants
    const uint32_t HEIGHT = 500;
    const uint32_t WIDTH = 500;
    const uint32_t RGB_MAX = 255;

    Scene scene = Scene();
    
    // Spheres
    Sphere sphere1 = Sphere(0, 0, 0, 1, Color_t(255,0,0));
    Sphere sphere2 = Sphere(0, 1, 1, 2, Color_t(255,0,0));

    // Light source
    LightSource lightSource = LightSource(0, 5, 0);

    scene.add(&sphere1);
    scene.add(&sphere2);
    scene.add(&lightSource);

    ofstream outputImage ("output.ppm");
    if (outputImage.is_open())
    {
        /*  
         *  "P3" means this is a RGB color image in ASCII
         *  "WIDTH HEIGHT" is the image's width and height
         *  "RBG_MAX" is the maximum value for each color
         */
        outputImage << "P3\n" << WIDTH << " " << HEIGHT << "\n" << RGB_MAX << "\n";
        // For each pixel, calculate the color using the raytracer
        for(size_t h = 0; h < HEIGHT; h++)
        {
            for(size_t w = 0; w < WIDTH; w++)
            {
                outputImage << (int)255 << ' ' << (int)255 << ' ' << (int)0 << "\n";
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