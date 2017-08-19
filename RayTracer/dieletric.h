//
//  dieletric.h
//  RayTracer
//
//  Created by caiovelenosi on 12/08/17.
//  Copyright © 2017 caiovelenosi. All rights reserved.
//

#ifndef dieletric_h
#define dieletric_h

#include "material.h"

class dieletric : public material
{
public:
    dieletric(float ri) : refIndex(ri) {}
    
    float refIndex;
    
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
    {
        vec3 outwardNormal;
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        float niOverNt;
        attenuation = vec3(1, 1, 1);
        vec3 refracted;
        float reflectProb;
        float cosine;
        
        if (dot(r_in.direction(), rec.normal) > 0)
        {
            outwardNormal = -rec.normal;
            niOverNt = refIndex;
            cosine = refIndex * dot(r_in.direction(), rec.normal) / r_in.direction().length();
        }
        else
        {
            outwardNormal = rec.normal;
            niOverNt = 1. / refIndex;
            cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
        }
        
        if (refract(r_in.direction(), outwardNormal, niOverNt, refracted))
        {
            reflectProb = schlick(cosine, refIndex);
            
        }
        else
        {
            reflectProb = 1.;
        }
        
        if (drand48() < reflectProb)
        {
            scattered = ray(rec.p, reflected);
        }
        else
        {
            scattered = ray(rec.p, refracted);
        }
        
        return true;
    }
    
private:
    bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted) const
    {
        vec3 uv = unit_vector(v);
        float dt = dot(uv, n);
        float discriminant = 1. - ni_over_nt * ni_over_nt * (1. - dt * dt);
        
        if (discriminant > 0)
        {
            refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
            return true;
        }
        else
        {
            return false;
        }
    }
    
    float schlick(float cosine, float refIdx) const
    {
        float r0 = (1 - refIdx) / (1 + refIdx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};

#endif /* dieletric_h */
