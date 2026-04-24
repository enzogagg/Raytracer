/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cylindre
*/

#include "Cylindre.hpp"

/**
 * @brief Default constructor for the Cylindre shape.
 * By default tip is at (0, 0, 0), height at (0, 0, 0) and angle at 0
 */
Cylindre::Cylindre()
    : _center(Math::Point()), _radius(0.f), _height(0.f), _color(Color())
{
    _material = std::make_shared<Default>();
}

/**
 * @brief Constructor of the Cylindre shape
 * @param center Point that represents the center of the bottom cap of the Cylindre
 * @param radius The radius of both cap of the Cylindre
 * @param height height of the Cylindre
 */
Cylindre::Cylindre(Math::Point center, double radius, double height, Color &color,
    const std::shared_ptr<AMaterial> &mat)
    : _center(center), _radius(radius), _height(height), _color(color), _material(mat)
{}

/**
 * @brief basic destructor of the Cylindre class
 */
Cylindre::~Cylindre()
{

}

/**
 * @brief Get the type of the primitive shape.
 * @return The type of the shape as a string.
 */
const std::string &Cylindre::getType() const
{
    static const std::string type = "Cylindre";
    return type;
}

/**
 * @brief Check if a ray intersects with the primitive shape.
 * @param ray The ray to check for intersection.
 * @return True if the ray intersects with the shape, false otherwise.
 */
bool Cylindre::intersect(const Ray &ray) const
{
    Math::Vector oc = ray.getOrigin() - _center;
    Math::Vector d = ray.getDirection();

    double a = d.getX() * d.getX() + d.getZ() * d.getZ();
    double b = 2 * (oc.getX() * d.getX() + oc.getZ() * d.getZ());
    double c = oc.getX() * oc.getX() + oc.getZ() * oc.getZ() - _radius * _radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;
    double sqrt_disc = std::sqrt(discriminant);
    double t1 = (-b - sqrt_disc) / (2 * a);
    double t2 = (-b + sqrt_disc) / (2 * a);

    for (double t : {t1, t2}) {
        if (t > 0) {
            double y = ray.getOrigin().getY() + t * d.getY();
            if (y >= _center.getY() && y <= _center.getY() + _height)
                return true;
        }
    }
    Math::Point cap1 = intersection_cap(ray, _center, Math::Vector(0, -1, 0));
    Math::Point cap2 = intersection_cap(ray, _center + Math::Vector(0, _height, 0), Math::Vector(0, 1, 0));
    if (!(cap1.getX() == 0.0 && cap1.getY() == 0.0 && cap1.getZ() == 0.0))
        return true;
    if (!(cap2.getX() == 0.0 && cap2.getY() == 0.0 && cap2.getZ() == 0.0))
        return true;
    return false;
}

/**
 * @brief Get the intersection point with the base of the Cylindre (represented by a circle)
 * @param ray The ray to check for intersection.
 * @param cap_center Center of the bottom cap of the Cylindre
 * @param normal vector normal at the cylindre
 * @return the intersection point between one of the cap of the Cylindre and the ray
 */
Math::Point Cylindre::intersection_cap(const Ray &ray, const Math::Point &cap_center, const Math::Vector &normal) const
{
    double denom = normal.dot(ray.getDirection());
    if (std::abs(denom) > 1e-6) {
        double t = (cap_center - ray.getOrigin()).dot(normal) / denom;
        if (t > 0) {
            Math::Point p = ray.getOrigin() + ray.getDirection() * t;
            if ((p - cap_center).length() <= _radius)
                return p;
        }
    }
    return Math::Point(0, 0, 0);
}

/**
 * @brief This function does exactly what you think it does
 * @param ray The ray to check for intersection.
 * @return the intersection point between a Ray and a shape
 */
Math::Point Cylindre::getIntersection(const Ray &ray) const
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

    for (double t : {t1, t2}) {
        if (t > 0) {
            double y = ray.getOrigin().getY() + t * d.getY();
            if (y >= _center.getY() && y <= _center.getY() + _height)
                return ray.getOrigin() + ray.getDirection() * t;
        }
    }
    Math::Point cap1 = intersection_cap(ray, _center, Math::Vector(0, -1, 0));
    Math::Point cap2 = intersection_cap(ray, _center + Math::Vector(0, _height, 0), Math::Vector(0, 1, 0));
    if (!(cap1.getX() == 0.0 && cap1.getY() == 0.0 && cap1.getZ() == 0.0))
        return cap1;
    if (!(cap2.getX() == 0.0 && cap2.getY() == 0.0 && cap2.getZ() == 0.0))
        return cap2;
    return Math::Point();
}

/**
 * @brief Create a normal vector to the shape
 * @param point origin of the normal vector
 * @return normal vector to the shape
 */
Math::Vector Cylindre::normal_at(const Math::Point &point) const
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
Color Cylindre::getColor() const
{
    return _color;
}

/**
 * @brief Get the material of the primitive shape.
 * @return The material of the shape.
 */
std::shared_ptr<AMaterial> Cylindre::getMaterial() const
{
    return _material;
}