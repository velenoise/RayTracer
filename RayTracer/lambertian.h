//
//  lambertian.h
//  RayTracer
//
//  Created by caiovelenosi on 12/08/17.
//  Copyright © 2017 caiovelenosi. All rights reserved.
//

#ifndef lambertian_h
#define lambertian_h

#include "material.h"

class lambertian : public material
{
public:
    lambertian(const vec3 a) : albedo(a) {}
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
    {
        vec3 target = rec.p + rec.normal + pointInSphere();
        scattered = ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }
    
    vec3 albedo;
};


#endif /* lambertian_h */
