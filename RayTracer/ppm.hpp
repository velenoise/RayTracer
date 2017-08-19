//
//  ppm.hpp
//  RayTracer
//
//  Created by caiovelenosi on 19/08/17.
//  Copyright © 2017 caiovelenosi. All rights reserved.
//

#ifndef ppm_hpp
#define ppm_hpp

#include <stdio.h>
#include <vector>
#include <fstream>

class Ppm {
public:
    Ppm();
    Ppm(const unsigned int w, const unsigned int h);
    
    void setPixel(const int index, const unsigned char r, const unsigned char g, const unsigned char b);
    void save(std::string fileName);
    
    unsigned int width, height, size;
    
private:
    std::vector<unsigned char> r;
    std::vector<unsigned char> g;
    std::vector<unsigned char> b;
};

#endif /* ppm_hpp */
