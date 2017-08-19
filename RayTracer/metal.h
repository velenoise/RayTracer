//
//  metal.h
//  RayTracer
//
//  Created by caiovelenosi on 12/08/17.
//  Copyright © 2017 caiovelenosi. All rights reserved.
//

#ifndef metal_h
#define metal_h

#include "material.h"

class metal : public material
{
public:
    metal(const vec3 a, float f) : albedo(a) { fuzz = f < 1 ? f : 1; }
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
    {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * pointInSphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
    
    vec3 albedo;
    float fuzz;
    
};

#endif /* metal_h */
