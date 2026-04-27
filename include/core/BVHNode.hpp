/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** BVHNode
*/

#pragma once

#include "IPrimitive.hpp"
#include "AABB.hpp"
#include <vector>
#include <memory>

namespace Math {

    class BVHNode : public IPrimitive {
        public:
            BVHNode();
            BVHNode(std::vector<std::shared_ptr<IPrimitive>>& src_objects, size_t start, size_t end);

            const std::string &getType() const override;
            bool intersect(const Ray& ray) const override;
            std::shared_ptr<IPrimitive> getClosestPrimitive(const Ray& ray, double& t, double t_min = 1e-4) const override;
            AABB getBoundingBox() const override;
            Point getIntersection(const Ray& ray) const override;
            Vector normal_at(const Point& point) const override;
            Color getColor() const override;
            std::shared_ptr<AMaterial> getMaterial() const override;

        private:
            std::shared_ptr<IPrimitive> _left;
            std::shared_ptr<IPrimitive> _right;
            AABB _box;

            static bool box_compare(const std::shared_ptr<IPrimitive> a, const std::shared_ptr<IPrimitive> b, int axis);
            static bool box_x_compare(const std::shared_ptr<IPrimitive> a, const std::shared_ptr<IPrimitive> b);
            static bool box_y_compare(const std::shared_ptr<IPrimitive> a, const std::shared_ptr<IPrimitive> b);
            static bool box_z_compare(const std::shared_ptr<IPrimitive> a, const std::shared_ptr<IPrimitive> b);
    };
}
