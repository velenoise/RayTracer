//
//  sphere.h
//  RayTracer
//
//  Created by caiovelenosi on 11/08/17.
//  Copyright © 2017 caiovelenosi. All rights reserved.
//

#ifndef sphere_h
#define sphere_h

#include "hitable.h"
#include "material.h"

class sphere : public hitable
{
public:
    sphere() {}
    sphere(vec3 c, float r, material *m) : center(c), radius(r), mat(m) {};
    
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    
    vec3 center;
    float radius;
    material *mat;
};

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    
    rec.mat_ptr = mat;
    
    if (discriminant > 0)
    {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp > t_min && temp < t_max)
        {
            rec.t = temp;
            rec.p = r.pointAt(temp);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        
        temp = (-b + sqrt(discriminant)) / a;
        if (temp > t_min && temp < t_max)
        {
            rec.t = temp;
            rec.p = r.pointAt(temp);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    
    return false;
}


#endif /* sphere_h */
