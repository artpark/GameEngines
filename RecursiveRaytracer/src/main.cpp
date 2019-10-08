/*
 *  Name: Thanut (Art) Parkeenvincha
 *  Class: CMPM 164 - Game Engines
 *  Date: 10/07/2019
 *  Homework #2: Recursive Raytracing
 */
 
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