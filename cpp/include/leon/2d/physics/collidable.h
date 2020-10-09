#ifndef __LEON_2D_PHYSICS_COLLIDABLE_H__
#define __LEON_2D_PHYSICS_COLLIDABLE_H__

#include "../../utils.h"
#include "../../vector.h"
#include "../../ray.h"

class Collidable {
public:
    virtual bool hits(const Ray2D& ray, Vec2& point) const = 0;
};

#endif