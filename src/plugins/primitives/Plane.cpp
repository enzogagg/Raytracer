/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Plane
*/

/**
 * @file Plane.cpp
 * @brief Plane class implementation.
 * @details This file contains the implementation of the Plane class,
 *      which is a plugin for the raytracer project.
 * @note The Plane class represents a plane in 3D space.
 */
#include "Plane.hpp"

/**
 * @brief Constructor for the Plane class.
 * @param axis The axis of the plane (x, y, or z).
 * @param position The position of the plane along the specified axis.
 * @param color The color of the plane.
 */
Plane::Plane(Math::Point p0, Math::Point p1, Math::Point p2, const Color &color,
    const std::shared_ptr<AMaterial> &mat)
    : _a(p0), _b(p1), _c(p2), _color(color), _material(mat)
{
    Math::Vector edge1 = _a - _b;
    Math::Vector edge2 = _a - _c;
    _normal = edge1.crossProduct(edge2).normalize();
    return;
}

/**
 * @brief Get the type of the plane.
 * @return The type of the plane as a string.
 */
const std::string &Plane::getType() const
{
    static std::string type("plane");
    return type;
}

/**
 * @brief Check if a ray intersects with the plane.
 * @param ray The ray to check for intersection.
 * @return True if the ray intersects with the plane, false otherwise.
 */
bool Plane::intersect(const Ray &ray) const
{
    double denom = _normal.dot(ray.getDirection());
    if (std::abs(denom) > 1e-6) {
        Math::Vector p0l0 = _a - ray.getOrigin();
        double t = p0l0.dot(_normal) / denom;
        return t >= 1e-6;
    }
    return false;
}

/**
 * @brief Get the bounding box of the plane.
 * @return The AABB of the plane.
 */
Math::AABB Plane::getBoundingBox() const
{
    // For an infinite plane, we use a very large but finite box.
    // This allows the BVH to work while still covering a huge area.
    double min_x = std::min({_a.getX(), _b.getX(), _c.getX()}) - 1000.0;
    double max_x = std::max({_a.getX(), _b.getX(), _c.getX()}) + 1000.0;
    double min_y = std::min({_a.getY(), _b.getY(), _c.getY()}) - 1000.0;
    double max_y = std::max({_a.getY(), _b.getY(), _c.getY()}) + 1000.0;
    double min_z = std::min({_a.getZ(), _b.getZ(), _c.getZ()}) - 1000.0;
    double max_z = std::max({_a.getZ(), _b.getZ(), _c.getZ()}) + 1000.0;

    // Add a small thickness if the plane is axis-aligned
    if (std::abs(max_x - min_x) < 0.1) { min_x -= 0.1; max_x += 0.1; }
    if (std::abs(max_y - min_y) < 0.1) { min_y -= 0.1; max_y += 0.1; }
    if (std::abs(max_z - min_z) < 0.1) { min_z -= 0.1; max_z += 0.1; }

    return Math::AABB(Math::Point(min_x, min_y, min_z), Math::Point(max_x, max_y, max_z));
}

std::shared_ptr<IPrimitive> Plane::getClosestPrimitive(const Ray& ray, double& t, double t_min) const
{
    if (this->intersect(ray)) {
        Math::Point hit = this->getIntersection(ray);
        double dist = (hit - ray.getOrigin()).length();
        if (dist > t_min && dist < t) {
            t = dist;
            return std::const_pointer_cast<IPrimitive>(shared_from_this());
        }
    }
    return nullptr;
}

/**
 * @brief This function does exactly what you think it does
 * @param ray The ray to check for intersection.
 * @return the intersection point between a Ray and a shape
 */
Math::Point Plane::getIntersection(const Ray &ray) const
{
    double denom = _normal.dot(ray.getDirection());
    if (std::abs(denom) > 1e-6) {
        Math::Vector p0l0 = _a - ray.getOrigin();
        double t = p0l0.dot(_normal) / denom;
        if (t >= 1e-6) {
            return ray.getOrigin() + ray.getDirection() * t;
        }
    }
    return Math::Point();
}

/**
 * @brief Create a normal vector to the shape
 * @param point origin of the normal vector
 * @return normal vector to the shape
 */
Math::Vector Plane::normal_at(const Math::Point &point) const
{
    static_cast<void>(point);
    return _normal.normalize();
}

/**
 * @brief Get the color of the plane.
 * @return The color of the plane.
 */
Color Plane::getColor() const
{
    return _color;
}

/**
 * @brief Get the material of the primitive shape.
 * @return The material of the shape.
 */
std::shared_ptr<AMaterial> Plane::getMaterial() const
{
    return _material;
}
