//
//  main.cpp
//  RayTracer
//
//  Created by caiovelenosi on 11/08/17.
//  Copyright © 2017 caiovelenosi. All rights res/Users/caiovelenosi/Projects/_RayTracer/RayTracer/src/main.cpperved.
//

#include <iostream>
#include <fstream>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "sphere.h"
#include "hitableList.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "dieletric.h"

vec3 color(ray &r, hitable *world, int depth)
{
    hit_record rec;
    
    if (world->hit(r, 0.001, MAXFLOAT, rec))
    {
        ray scattered;
        vec3 attenuation;
        
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, world, depth + 1);
        }
        else
        {
            return vec3(0, 0, 0);
        }
    }
    else
    {
        vec3 unitDir = unit_vector(r.direction());
        float t = 0.5 * (unitDir.y() + 1.);
        return (1. - t) * vec3(1., 1., 1.) + t*vec3(0.5, 0.7, 1.);
    }
}

int main(int argc, const char * argv[]) {
    int nx = 200;
    int ny = 100;
    int ns = 200;
    
    std::ofstream picture;
    picture.open("/Users/caiovelenosi/Desktop/test.ppm", std::ios::out | std::ios::trunc);
    
    picture << "P3\n" << nx << " " << ny << "\n255\n";
    
    hitable *list[5];
    list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
    list[1] = new sphere(vec3(0, -100.5, -1), 100., new lambertian(vec3(0.8, 0.8, 0)));
    list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.3));
    list[3] = new sphere(vec3(-1, 0, -1), -0.45, new dieletric(1.5));
    list[4] = new sphere(vec3(-1, 0, -1), 0.5, new dieletric(1.5));
    hitable *world = new hitableList(list, 5);
    
    vec3 origin(3, 2, 2);
    vec3 dest(0, 0, -1);
    float f = (origin - dest).length();
    
    camera cam(20, (float)nx / (float)ny, origin, dest, vec3(0, 1, 0), 0., f);
    
    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);
            
            for (int g = 0; g < ns; g++)
            {
                float u = ((float)i + drand48()) / (float)nx;
                float v = ((float)j + drand48()) / (float)ny;
                
                ray r = cam.getRay(u, v);
                col += color(r, world, 0);
                
            }
            
            col /= (float)ns;
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            
            int ir = (int)(255.99 * col.r());
            int ig = (int)(255.99 * col.g());
            int ib = (int)(255.99 * col.b());
            
            picture << ir << " " << ig << " " << ib << "\n";
        }
    }
    
    picture.close();
    
    return 0;
}
