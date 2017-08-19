//
//  hitable.h
//  RayTracer
//
//  Created by caiovelenosi on 11/08/17.
//  Copyright © 2017 caiovelenosi. All rights reserved.
//

#ifndef hitable_h
#define hitable_h

#include "ray.h"

class material;

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
    material *mat_ptr;
};

class hitable {
    
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record &rec) const = 0;
};

#endif /* hitable_h */
