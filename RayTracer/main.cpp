
#include <iostream>
#include <fstream>
#include <thread>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "sphere.h"
#include "hitableList.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "dieletric.h"
#include "ppm.hpp"

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

void render(int sx, int sy, int nx, int ny, int ns, camera &cam, hitable *world, Ppm &picture)
{
    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);
            
            for (int g = 0; g < ns; g++)
            {
                float u = ((float)(sx + i) + drand48()) / (float)picture.width;
                float v = ((float)(sy + j) + drand48()) / (float)picture.height;
                
                ray r = cam.getRay(u, v);
                col += color(r, world, 0);
                
            }
            
            col /= (float)ns;
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            
            int ir = (int)(255.99 * col.r());
            int ig = (int)(255.99 * col.g());
            int ib = (int)(255.99 * col.b());
            
            int idx = picture.size - ((sy + j) * picture.width + (sx + i));
            
            picture.setPixel(idx, (unsigned char)ir, (unsigned char)ig, (unsigned char)ib);
        }
    }
}

int main(int argc, const char * argv[]) {
    int nx = 640;
    int ny = 480;
    int ns = 200;
    
    time_t startTime = time(0);
    
    Ppm picture(nx, ny);
    
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
    
    std::vector<std::thread> threads;
    
    int chunkW = nx / 4;
    int chunkH = ny / 2;
    
    int i;
    
    for (i = 0; i < 7; i++)
    {
        int x = (i % 4) * chunkW;
        int y = (int)(i / 4) * chunkH;
        threads.push_back(std::thread(render, x, y, chunkW, chunkH, ns, std::ref(cam), world, std::ref(picture)));
    }
    
    render((i % 4) * chunkW, (int)(i / 4) * chunkH, chunkW, chunkH, ns, cam, world, picture);
    
    for (i = 0; i < 7; i++)
    {
        threads[i].join();
    }
    
    picture.save("/Users/caiovelenosi/Desktop/test.ppm");
    
    time_t endTime = time(0);
    
    std::cout << "Total time: " << (endTime - startTime) << std::endl;
    
    return 0;
}
