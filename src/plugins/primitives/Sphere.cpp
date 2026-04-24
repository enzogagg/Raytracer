/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Sphere
*/

/**
 * @file Sphere.cpp
 * @brief Sphere class implementation.
 * @details This file contains the implementation of the Sphere class,
 *         which is a plugin for the raytracer project.
 */
#include "Sphere.hpp"

/**
 * @brief Constructor for the Sphere class.
 * @param center the center of the sphere (x, y, or z).
 * @param radius the radius of the sphere
 * @param color The color of the sphere.
 */
Sphere::Sphere(Math::Vector center, float radius, const Color &color, const std::shared_ptr<AMaterial> &mat)
    : _radius(radius), _color(color), _material(mat)
{
    _center.setX(center.getX());
    _center.setY(center.getY());
    _center.setZ(center.getZ());
    return;
}

/**
 * @brief Get the type of the sphere.
 * @return The type of the sphere as a string.
 */
const std::string &Sphere::getType() const
{
    static std::string type("sphere");
    return type;
}

/**
 * @brief Check if a ray intersects with the sphere.
 * @param ray The ray to check for intersection.
 * @return True if the ray intersects with the sphere, false otherwise.
 */
bool Sphere::intersect(const Ray &ray) const
{
    Math::Vector oc = Math::Vector(
        ray.getOrigin().getX() - _center.getX(),
        ray.getOrigin().getY() - _center.getY(),
        ray.getOrigin().getZ() - _center.getZ()
    );

    double a = ray.getDirection().dot(ray.getDirection());
    double b = 2.0 * oc.dot(ray.getDirection());
    double c = oc.dot(oc) - (_radius * _radius);

    double discriminant = b * b - 4 * a * c;

    return discriminant >= 0;
}

/**
 * @brief This function does exactly what you think it does
 * @param ray The ray to check for intersection.
 * @return the intersection point between a Ray and a shape
 */
Math::Point Sphere::getIntersection(const Ray &ray) const
{
    Math::Vector oc = Math::Vector(
        ray.getOrigin().getX() - _center.getX(),
        ray.getOrigin().getY() - _center.getY(),
        ray.getOrigin().getZ() - _center.getZ()
    );

    double a = ray.getDirection().dot(ray.getDirection());
    double b = 2.0 * oc.dot(ray.getDirection());
    double c = oc.dot(oc) - (_radius * _radius);

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return Math::Point();

    double sqrt_disc = std::sqrt(discriminant);
    double t1 = (-b - sqrt_disc) / (2.0 * a);
    double t2 = (-b + sqrt_disc) / (2.0 * a);

    const double epsilon = 1e-4;
    double t = -1;
    if (t1 > epsilon && t2 > epsilon)
        t = std::min(t1, t2);
    else if (t1 > epsilon)
        t = t1;
    else if (t2 > epsilon)
        t = t2;

    if (t < 0)
        return Math::Point();

    return ray.getOrigin() + ray.getDirection() * t;
}

/**
 * @brief Create a normal vector to the shape
 * @param point origin of the normal vector
 * @return normal vector to the shape
 */
Math::Vector Sphere::normal_at(const Math::Point &point) const
{
    return Math::Vector(
        point.getX() - _center.getX(),
        point.getY() - _center.getY(),
        point.getZ() - _center.getZ()
    ).normalize();
}

/**
 * @brief Get the color of the sphere.
 * @return The color of the sphere.
 */
Color Sphere::getColor() const
{
    return _color;
}

/**
 * @brief Get the material of the primitive shape.
 * @return The material of the shape.
 */
std::shared_ptr<AMaterial> Sphere::getMaterial() const
{
    return _material;
}
