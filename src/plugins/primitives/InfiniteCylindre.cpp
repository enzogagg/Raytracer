/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** InfiniteCylindre
*/

#include "InfiniteCylindre.hpp"

/**
 * @brief Default constructor for the InfiniteCylindre shape.
 * By default tip is at (0, 0, 0), height at (0, 0, 0) and angle at 0
 */
InfiniteCylindre::InfiniteCylindre()
    : _center(Math::Point()), _radius(0.f), _height(0.f), _color(Color())
{
    _material = std::make_shared<Default>();
}

/**
 * @brief Constructor of the InfiniteCylindre shape
 * @param center Point that represents the center of the bottom cap of the InfiniteCylindre
 * @param radius The radius of both cap of the InfiniteCylindre
 * @param height height of the InfiniteCylindre
 */
InfiniteCylindre::InfiniteCylindre(Math::Point center, double radius, double height, Color &color,
    const std::shared_ptr<AMaterial> &mat)
    : _center(center), _radius(radius), _height(height), _color(color), _material(mat)
{}

/**
 * @brief basic destructor of the InfiniteCylindre class
 */
InfiniteCylindre::~InfiniteCylindre()
{

}

/**
 * @brief Get the type of the primitive shape.
 * @return The type of the shape as a string.
 */
const std::string &InfiniteCylindre::getType() const
{
    static const std::string type = "infinite_cylindre";
    return type;
}

/**
 * @brief Check if a ray intersects with the primitive shape.
 * @param ray The ray to check for intersection.
 * @return True if the ray intersects with the shape, false otherwise.
 */
bool InfiniteCylindre::intersect(const Ray &ray) const
{
    Math::Vector oc = ray.getOrigin() - _center;
    Math::Vector d = ray.getDirection();

    double a = d.getX() * d.getX() + d.getZ() * d.getZ();
    double b = 2 * (oc.getX() * d.getX() + oc.getZ() * d.getZ());
    double c = oc.getX() * oc.getX() + oc.getZ() * oc.getZ() - _radius * _radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;
    return true;
}

/**
 * @brief This function does exactly what you think it does
 * @param ray The ray to check for intersection.
 * @return the intersection point between a Ray and a shape
 */
Math::Point InfiniteCylindre::getIntersection(const Ray &ray) const
{
    Math::Vector oc = ray.getOrigin() - _center;
    Math::Vector d = ray.getDirection();

    double a = d.getX() * d.getX() + d.getZ() * d.getZ();
    double b = 2 * (oc.getX() * d.getX() + oc.getZ() * d.getZ());
    double c = oc.getX() * oc.getX() + oc.getZ() * oc.getZ() - _radius * _radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return Math::Point();
    double sqrt_disc = std::sqrt(discriminant);
    double t1 = (-b - sqrt_disc) / (2 * a);
    double t2 = (-b + sqrt_disc) / (2 * a);

    double t = (t1 > 0) ? t1 : t2;

    if (t < 0)
        return Math::Point();
    return ray.getOrigin() + ray.getDirection() * t;
}

/**
 * @brief Create a normal vector to the shape
 * @param point origin of the normal vector
 * @return normal vector to the shape
 */
Math::Vector InfiniteCylindre::normal_at(const Math::Point &point) const
{
    if (std::abs(point.getY() - _center.getY()) < 1e-6)
        return Math::Vector(0, -1, 0);
    if (std::abs(point.getY() - (_center.getY() + _height)) < 1e-6)
        return Math::Vector(0, 1, 0);
    return Math::Vector(point.getX() - _center.getX(), 0, point.getZ() - _center.getZ()).normalize();
}

/**
 * @brief Get the color of the primitive shape.
 * @return The color of the shape.
 */
Color InfiniteCylindre::getColor() const
{
    return _color;
}

/**
 * @brief Get the material of the primitive shape.
 * @return The material of the shape.
 */
std::shared_ptr<AMaterial> InfiniteCylindre::getMaterial() const
{
    return _material;
}