//
//  ray.h
//  RayTracer
//
//  Created by caiovelenosi on 11/08/17.
//  Copyright © 2017 caiovelenosi. All rights reserved.
//

#ifndef ray_h
#define ray_h

#include "vec3.h"

class ray {
public:
    ray() {}
    ray(const vec3& a, const vec3& b) { A = a; B = b; }
    vec3 origin() const { return A; }
    vec3 direction() const { return B; }
    vec3 pointAt(float t) const { return A + t*B; }
    
    vec3 A, B;
};


#endif /* ray_h */
