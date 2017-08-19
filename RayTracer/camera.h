//
//  camera.h
//  RayTracer
//
//  Created by caiovelenosi on 11/08/17.
//  Copyright © 2017 caiovelenosi. All rights reserved.
//

#ifndef camera_h
#define camera_h

#include "ray.h"

class camera {
public:
    camera(float vfov, float aspect, vec3 lookFrom, vec3 lookAt, vec3 up, float aperture, float f)
    {
        lensRadius = aperture * .5f;
        
        float theta = vfov * M_PI / 180.;
        float halfHeight = tan(theta * .5);
        float halfWidth = aspect * halfHeight;
        
        origin = lookFrom;
        
        w = unit_vector(lookFrom - lookAt);
        u = unit_vector(cross(up, w));
        v = cross(w, u);
        
        lowerLeft = origin - halfWidth * f * u - halfHeight * f * v - f * w;
        horizontal = 2. * halfWidth * f * u;
        vertical = 2. * halfHeight * f * v;
    }
    
    ray getRay(float s, float t)
    {
        vec3 rd = lensRadius * randonPointInDisk();
        vec3 offset = u * rd.x() + v * rd.y();
        return ray(origin + offset, lowerLeft + s * horizontal + t * vertical - origin - offset);
    }
    
    vec3 origin;
    vec3 lowerLeft;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    float lensRadius;
    
private:
    vec3 randonPointInDisk()
    {
        vec3 p;
        do
        {
            p = 2. * vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
        } while (dot(p, p) >= 1.f);
        
        return p;
    }
};


#endif /* camera_h */
