//
//  hitableList.h
//  RayTracer
//
//  Created by caiovelenosi on 11/08/17.
//  Copyright © 2017 caiovelenosi. All rights reserved.
//

#ifndef hitableList_h
#define hitableList_h

#include "hitable.h"

class hitableList : public hitable
{
public:
    hitableList() {}
    hitableList(hitable **l, int n) { list = l; listSize = n; }
    
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    
    hitable **list;
    int listSize;
};


bool hitableList::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    hit_record tempRec;
    
    bool hitAnything = false;
    double closest = t_max;
    
    for (int i = 0; i < listSize; i++)
    {
        if (list[i]->hit(r, t_min, closest, tempRec))
        {
            hitAnything = true;
            closest = tempRec.t;
            rec = tempRec;
        }
    }
    
    return hitAnything;
}


#endif /* hitableList_h */
