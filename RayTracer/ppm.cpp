//
//  ppm.cpp
//  RayTracer
//
//  Created by caiovelenosi on 19/08/17.
//  Copyright © 2017 caiovelenosi. All rights reserved.
//

#include "ppm.hpp"

Ppm::Ppm()
{
    width = 0;
    height = 0;
    size = 0;
}

Ppm::Ppm(const unsigned int w, const unsigned int h)
{
    width = w;
    height = h;
    size = width * height;
    
    r.resize(size);
    g.resize(size);
    b.resize(size);
}

void Ppm::setPixel(const int index, const unsigned char red, const unsigned char green, const unsigned char blue)
{
    r[index] = red;
    g[index] = green;
    b[index] = blue;
}

void Ppm::save(std::string fileName)
{
    std::ofstream file;
    file.open(fileName, std::ios::out | std::ios::trunc | std::ios::binary);
    
    file << "P6\n" << width << " " << height << "\n255\n";
    
    for (int i = 0; i < size; i++)
    {
        //file << (int)r[i] << " " << (int)g[i] << " " << (int)b[i] << "\n";
        file << (char)r[i] << (char)g[i] << (char)b[i];
    }
    
    file.close();
}
