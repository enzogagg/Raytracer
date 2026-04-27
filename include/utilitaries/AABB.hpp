/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** AABB
*/

#pragma once

#include "Point.hpp"
#include "Ray.hpp"

namespace Math {

    class AABB {
        public:
            AABB();
            AABB(const Point& min, const Point& max);

            const Point& min() const;
            const Point& max() const;

            bool intersect(const Ray& ray, double t_min, double t_max) const;

            static AABB surroundingBox(const AABB& box0, const AABB& box1);

        private:
            Point _min;
            Point _max;
    };
}
