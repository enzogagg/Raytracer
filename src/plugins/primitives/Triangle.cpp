/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Triangle
*/

/**
 * @file Triangle.cpp
 * @brief Triangle class implementation.
 * @details This file contains the implementation of the Triangle class,
 *      which is a plugin for the raytracer project.
 * @note The Triangle class represents a Triangle in 3D space.
 */

#include "Triangle.hpp"
#include "Default.hpp"

Triangle::Triangle(Math::Point v0, Math::Point v1, Math::Point v2, const Color &color,
    const std::shared_ptr<AMaterial> &mat)
    : _v0(v0), _v1(v1), _v2(v2), _color(color), _material(mat)
{
    Math::Vector edge1 = _v1 - _v0;
    Math::Vector edge2 = _v2 - _v0;
    _normal = edge1.crossProduct(edge2).normalize();
}

const std::string &Triangle::getType() const
{
    static std::string type("triangle");
    return type;
}

bool Triangle::intersect(const Ray &ray) const
{
    const double epsilon = 1e-6;
    Math::Vector edge1 = _v1 - _v0;
    Math::Vector edge2 = _v2 - _v0;
    Math::Vector h = ray.getDirection().crossProduct(edge2);
    double a = edge1.dot(h);

    if (a > -epsilon && a < epsilon)
        return false;

    double f = 1.0 / a;
    Math::Vector s = ray.getOrigin() - _v0;
    double u = f * s.dot(h);

    if (u < 0.0 || u > 1.0)
        return false;

    Math::Vector q = s.crossProduct(edge1);
    double v = f * ray.getDirection().dot(q);

    if (v < 0.0 || u + v > 1.0)
        return false;

    double t = f * edge2.dot(q);

    return t > epsilon;
}

/**
 * @brief Get the bounding box of the triangle.
 * @return The AABB of the triangle.
 */
Math::AABB Triangle::getBoundingBox() const
{
    double min_x = std::min({_v0.getX(), _v1.getX(), _v2.getX()});
    double min_y = std::min({_v0.getY(), _v1.getY(), _v2.getY()});
    double min_z = std::min({_v0.getZ(), _v1.getZ(), _v2.getZ()});
    double max_x = std::max({_v0.getX(), _v1.getX(), _v2.getX()});
    double max_y = std::max({_v0.getY(), _v1.getY(), _v2.getY()});
    double max_z = std::max({_v0.getZ(), _v1.getZ(), _v2.getZ()});

    double epsilon = 1e-4;
    return Math::AABB(
        Math::Point(min_x - epsilon, min_y - epsilon, min_z - epsilon),
        Math::Point(max_x + epsilon, max_y + epsilon, max_z + epsilon)
    );
}

std::shared_ptr<IPrimitive> Triangle::getClosestPrimitive(const Ray& ray, double& t, double t_min) const
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

Math::Point Triangle::getIntersection(const Ray &ray) const
{
    const double epsilon = 1e-6;
    Math::Vector edge1 = _v1 - _v0;
    Math::Vector edge2 = _v2 - _v0;
    Math::Vector h = ray.getDirection().crossProduct(edge2);
    double a = edge1.dot(h);

    if (a > -epsilon && a < epsilon)
        return Math::Point();

    double f = 1.0 / a;
    Math::Vector s = ray.getOrigin() - _v0;
    double u = f * s.dot(h);

    if (u < 0.0 || u > 1.0)
        return Math::Point();

    Math::Vector q = s.crossProduct(edge1);
    double v = f * ray.getDirection().dot(q);

    if (v < 0.0 || u + v > 1.0)
        return Math::Point();

    double t = f * edge2.dot(q);

    if (t > epsilon)
        return ray.getOrigin() + ray.getDirection() * t;

    return Math::Point();
}

Math::Vector Triangle::normal_at(const Math::Point &point) const
{
    (void)point;
    return _normal;
}

Color Triangle::getColor() const
{
    return _color;
}

std::shared_ptr<AMaterial> Triangle::getMaterial() const
{
    return _material;
}