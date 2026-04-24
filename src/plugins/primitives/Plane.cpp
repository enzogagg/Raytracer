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
    _normal = edge1.crossProduct(edge2);
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
    return _normal;
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
