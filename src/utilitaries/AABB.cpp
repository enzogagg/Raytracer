/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** AABB implementation
*/

#include "AABB.hpp"
#include <algorithm>
#include <limits>

namespace Math {

    AABB::AABB() : 
        _min(Point(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max())),
        _max(Point(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest())) 
    {}

    AABB::AABB(const Point& min, const Point& max) : _min(min), _max(max) {}

    const Point& AABB::min() const { return _min; }
    const Point& AABB::max() const { return _max; }

    bool AABB::intersect(const Ray& ray, double t_min, double t_max) const {
        for (int a = 0; a < 3; a++) {
            double dir_a = (a == 0 ? ray.getDirection().getX() : (a == 1 ? ray.getDirection().getY() : ray.getDirection().getZ()));
            double orig_a = (a == 0 ? ray.getOrigin().getX() : (a == 1 ? ray.getOrigin().getY() : ray.getOrigin().getZ()));
            double min_a = (a == 0 ? _min.getX() : (a == 1 ? _min.getY() : _min.getZ()));
            double max_a = (a == 0 ? _max.getX() : (a == 1 ? _max.getY() : _max.getZ()));

            double invD = 1.0f / dir_a;
            double t0 = (min_a - orig_a) * invD;
            double t1 = (max_a - orig_a) * invD;
            if (invD < 0.0f) std::swap(t0, t1);
            t_min = t0 > t_min ? t0 : t_min;
            t_max = t1 < t_max ? t1 : t_max;
            if (t_max <= t_min) return false;
        }
        return true;
    }

    AABB AABB::surroundingBox(const AABB& box0, const AABB& box1) {
        Point small(
            std::min(box0.min().getX(), box1.min().getX()),
            std::min(box0.min().getY(), box1.min().getY()),
            std::min(box0.min().getZ(), box1.min().getZ())
        );
        Point big(
            std::max(box0.max().getX(), box1.max().getX()),
            std::max(box0.max().getY(), box1.max().getY()),
            std::max(box0.max().getZ(), box1.max().getZ())
        );
        return AABB(small, big);
    }
}
