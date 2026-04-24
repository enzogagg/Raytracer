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