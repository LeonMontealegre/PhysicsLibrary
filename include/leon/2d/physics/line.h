#ifndef __LEON_2D_PHYSICS_LINE_H__
#define __LEON_2D_PHYSICS_LINE_H__

#include "collidable.h"

class Line: public Collidable {
public:
    Line(const Vec2& a_, const Vec2& b_): a(a_), b(b_), l(b_ - a_) {
    }
    Line(const Line& other): Line(other.a, other.b) {
    }

    virtual bool hits(const Ray2D& ray, Vec2& point) const {
        auto denom = cross(l, ray.D());
        if (denom == 0)
            return false;
        auto t = cross(l, a - ray.O()) / denom;
        auto s = cross(ray.D(), a - ray.O()) / denom;
        bool hit = (t >= 0) && (0 <= s && s <= 1);
        if (!hit)
            return false;
        point = ray[t];
        return true;
    }

private:
    Vec2 a, b, l;
};

#endif