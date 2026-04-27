/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** BVHNode implementation
*/

#include "BVHNode.hpp"
#include <algorithm>
#include <limits>

namespace Math {

    BVHNode::BVHNode() : _left(nullptr), _right(nullptr) {}

    BVHNode::BVHNode(std::vector<std::shared_ptr<IPrimitive>>& objects, size_t start, size_t end) {
        int axis = rand() % 3;
        auto comparator = (axis == 0) ? box_x_compare
                        : (axis == 1) ? box_y_compare
                        : box_z_compare;

        size_t object_span = end - start;

        if (object_span == 1) {
            _left = _right = objects[start];
        } else if (object_span == 2) {
            if (comparator(objects[start], objects[start+1])) {
                _left = objects[start];
                _right = objects[start+1];
            } else {
                _left = objects[start+1];
                _right = objects[start];
            }
        } else {
            std::sort(objects.begin() + start, objects.begin() + end, comparator);
            auto mid = start + object_span / 2;
            _left = std::make_shared<BVHNode>(objects, start, mid);
            _right = std::make_shared<BVHNode>(objects, mid, end);
        }

        _box = AABB::surroundingBox(_left->getBoundingBox(), _right->getBoundingBox());
    }

    const std::string &BVHNode::getType() const {
        static std::string type = "bvh_node";
        return type;
    }

    bool BVHNode::intersect(const Ray& ray) const {
        if (!_box.intersect(ray, 0.001, std::numeric_limits<double>::max()))
            return false;
        return _left->intersect(ray) || _right->intersect(ray);
    }

    std::shared_ptr<IPrimitive> BVHNode::getClosestPrimitive(const Ray& ray, double& t, double t_min) const {
        if (!_box.intersect(ray, t_min, t))
            return nullptr;

        std::shared_ptr<IPrimitive> left_hit = _left->getClosestPrimitive(ray, t, t_min);
        std::shared_ptr<IPrimitive> right_hit = _right->getClosestPrimitive(ray, t, t_min);

        return right_hit ? right_hit : left_hit;
    }

    AABB BVHNode::getBoundingBox() const {
        return _box;
    }

    Point BVHNode::getIntersection(const Ray& ray) const {
        bool hit_left = _left->intersect(ray);
        bool hit_right = _right->intersect(ray);

        if (hit_left && hit_right) {
            Point p_left = _left->getIntersection(ray);
            Point p_right = _right->getIntersection(ray);
            if ((p_left - ray.getOrigin()).length() < (p_right - ray.getOrigin()).length())
                return p_left;
            return p_right;
        } else if (hit_left) {
            return _left->getIntersection(ray);
        } else {
            return _right->getIntersection(ray);
        }
    }

    Vector BVHNode::normal_at(const Point& point) const {
        (void)point;
        return Vector(0, 0, 0);
    }

    Color BVHNode::getColor() const { return Color(0, 0, 0); }
    std::shared_ptr<AMaterial> BVHNode::getMaterial() const { return nullptr; }

    bool BVHNode::box_compare(const std::shared_ptr<IPrimitive> a, const std::shared_ptr<IPrimitive> b, int axis) {
        AABB box_a = a->getBoundingBox();
        AABB box_b = b->getBoundingBox();
        double min_a = (axis == 0) ? box_a.min().getX() : (axis == 1 ? box_a.min().getY() : box_a.min().getZ());
        double min_b = (axis == 0) ? box_b.min().getX() : (axis == 1 ? box_b.min().getY() : box_b.min().getZ());
        return min_a < min_b;
    }

    bool BVHNode::box_x_compare(const std::shared_ptr<IPrimitive> a, const std::shared_ptr<IPrimitive> b) { return box_compare(a, b, 0); }
    bool BVHNode::box_y_compare(const std::shared_ptr<IPrimitive> a, const std::shared_ptr<IPrimitive> b) { return box_compare(a, b, 1); }
    bool BVHNode::box_z_compare(const std::shared_ptr<IPrimitive> a, const std::shared_ptr<IPrimitive> b) { return box_compare(a, b, 2); }
}
