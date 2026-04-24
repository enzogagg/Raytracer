/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Face
*/

/**
 * @file Face.cpp
 * @brief Face class implementation.
 * @details This file contains the implementation of the Face class,
 *      which is a plugin for the raytracer project.
 * @note The Face class represents a Face in 3D space.
 */
#include "Face.hpp"

/**
 * @brief Constructor for the Face class.
 * @param axis The axis of the Face (x, y, or z).
 * @param v0 The position of the first vertex
 * @param v1 The position of the second vertex
 * @param v2 The position of the third vertex
 * @param color The color of the Face.
 */
Face::Face(Math::Point v0, Math::Point v1, Math::Point v2, const Color &color)
    : _v0(v0), _v1(v1), _v2(v2), _color(color)
{
    Math::Vector edge1 = _v1 - _v0;
    Math::Vector edge2 = _v2 - _v0;
    _normal = edge1.crossProduct(edge2);
    _normal.normalize();
    // _material = std::make_unique<AMaterial>();
    return;
}

/**
 * @brief Get the type of the Face.
 * @return The type of the Face as a string.
 */
const std::string &Face::getType() const
{
    static std::string type("Face");
    return type;
}

/**
 * @brief Check if a ray intersects with the Face.
 * @param ray The ray to check for intersection.
 * @return True if the ray intersects with the Face, false otherwise.
 */
bool Face::intersect(const Ray &ray) const
{
    double denom = _normal.dot(ray.getDirection());
    if (std::abs(denom) > 1e-6) {
        Math::Vector p0l0 = _v0 - ray.getOrigin();
        double t = p0l0.dot(_normal) / denom;
        if (t >= 1e-6) {
            Math::Point P = ray.getOrigin() + ray.getDirection() * t;
            Math::Vector N = _normal;
            Math::Vector edge0 = _v1 - _v0;
            Math::Vector edge1 = _v2 - _v1;
            Math::Vector edge2 = _v0 - _v2;

            Math::Vector c0 = edge0.crossProduct(P - _v0);
            Math::Vector c1 = edge1.crossProduct(P - _v1);
            Math::Vector c2 = edge2.crossProduct(P - _v2);

            if (N.dot(c0) >= 0 && N.dot(c1) >= 0 && N.dot(c2) >= 0)
                return true;
        }
    }
    return false;
}

/**
 * @brief This function does exactly what you think it does
 * @param ray The ray to check for intersection.
 * @return the intersection point between a Ray and a shape
 */
Math::Point Face::getIntersection(const Ray &ray) const
{
    double denom = _normal.dot(ray.getDirection());
    if (std::abs(denom) > 1e-6) {
        Math::Vector p0l0 = _v0 - ray.getOrigin();
        double t = p0l0.dot(_normal) / denom;
        if (t >= 1e-6) {
            Math::Point P = ray.getOrigin() + ray.getDirection() * t;
            Math::Vector N = _normal;
            Math::Vector edge0 = _v1 - _v0;
            Math::Vector edge1 = _v2 - _v1;
            Math::Vector edge2 = _v0 - _v2;

            Math::Vector c0 = edge0.crossProduct(P - _v0);
            Math::Vector c1 = edge1.crossProduct(P - _v1);
            Math::Vector c2 = edge2.crossProduct(P - _v2);

            if (N.dot(c0) >= 0 && N.dot(c1) >= 0 && N.dot(c2) >= 0)
                return P;
        }
    }
    return Math::Point();
}

/**
 * @brief Create a normal vector to the shape
 * @param point origin of the normal vector
 * @return normal vector to the shape
 */
Math::Vector Face::normal_at(const Math::Point &point) const
{
    static_cast<void>(point);
    return _normal;
}

/**
 * @brief Get the color of the Face.
 * @return The color of the Face.
 */
Color Face::getColor() const
{
    return _color;
}

/**
 * @brief Get the material of the primitive shape.
 * @return The material of the shape.
 */
std::shared_ptr<AMaterial> Face::getMaterial() const
{
    return _material;
}
