#ifndef __LEON_2D_PHYSICS_COLLISION_H__
#define __LEON_2D_PHYSICS_COLLISION_H__

#include "../../list.h"

#include "../../utils.h"
#include "../../vector.h"
#include "../../ray.h"

#include "collidable.h"

Vec2 DetectCollision(const Ray2D& ray, const List<Collidable const*>& collidables) {
    Vec2 hit = ray[10000000.0];
    for (uint i = 0; i < collidables.size(); i++) {
        Vec2 new_hit;
        if (collidables[i]->hits(ray, new_hit))
            hit = ray.closer(hit, new_hit);
    }
    return hit;
}

#endif