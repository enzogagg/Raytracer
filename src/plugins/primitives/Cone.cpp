/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cone
*/

#include "Cone.hpp"
#include "Default.hpp"

/**
 * @brief Default constructor for the cone shape.
 * By default tip is at (0, 0, 0), height at (0, 0, 0) and angle at 0
 */
Cone::Cone()
    : _tip(Math::Point()), _height(Math::Vector())
{
    _radiant = 0.0;
    _material = std::make_shared<Default>();
}

/**
 * @brief Constructor of the cone shape
 * @param tip Point that represent the tip of the cone
 * @param height height vector, the vector's origin is the tip of the cone
 * @param angle the angle in degree represented between the height vector and the
 * surface of the shape
 *
 * @note If you want a straight, x and z align axis cone a basic height vector
 * @note would looks like height = (0, -1, 0)
 */
Cone::Cone(Math::Point tip, Math::Vector height, double angle, Color &color,
    const std::shared_ptr<AMaterial> &mat)
    : _tip(tip), _height(height), _color(color), _material(mat)
{
    _radiant = angle * M_PI / 180;
}

/**
 * @brief basic destructor of the Cone class
 */
Cone::~Cone()
{

}

/**
 * @brief Get the type of the primitive shape.
 * @return The type of the shape as a string.
 */
const std::string &Cone::getType() const
{
    static const std::string type = "Cone";
    return type;
}

/**
 * @brief Check if a ray intersect with the base of the cone (represented by a circle)
 * @param ray The ray to check for intersection.
 * @return true if it does, false if not
 */
bool Cone::intersect_base(const Ray &ray) const
{
    Math::Vector normal = _height;
    double denom = normal.dot(ray.getDirection());
    if (std::abs(denom) > 1e-6) {
        Math::Point p0 = _tip + _height;
        Math::Vector p0l0 = p0 - ray.getOrigin();
        double t = p0l0.dot(normal) / denom;
        if (t >= 1e-6) {
            Math::Point p = ray.getOrigin() + ray.getDirection() * t;
            double l = _height.length() / std::cos(_radiant);
            double radius = sqrt((l * l) - (_height.length() * _height.length()));
            if ((p - p0).length() > radius) return false;
            return true;
        }
    }
    return false;
}

/**
 * @brief Check if a ray intersect with the cone
 * @param ray The ray to check for intersection.
 * @return true if it does, false if not
 */
bool Cone::intersectCone(const Ray &ray) const
{
    Math::Vector D = ray.getDirection();
    Math::Vector V = _height.normalize();
    Math::Point C = _tip;
    Math::Point O = ray.getOrigin();
    Math::Vector CO(O.getX() - C.getX(), O.getY() - C.getY(), O.getZ() - C.getZ());
    double cos2 = std::cos(_radiant) * std::cos(_radiant);

    double D_dot_V = D.dot(V);
    double CO_dot_V = CO.dot(V);
    double D_dot_D = D.dot(D);
    double D_dot_CO = D.dot(CO);
    double CO_dot_CO = CO.dot(CO);

    double a = D_dot_V * D_dot_V - D_dot_D * cos2;
    double b = 2.0 * (D_dot_V * CO_dot_V - D_dot_CO * cos2);
    double c = CO_dot_V * CO_dot_V - CO_dot_CO * cos2;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0.0)
        return false;

    double t1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + std::sqrt(discriminant)) / (2.0 * a);

    double t = (t1 > 0) ? t1 : t2;

    if (t < 0)
        return false;

    // Check whether it is the correct cone or not
    Math::Point P(ray.getOrigin() + ray.getDirection() * t);
    Math::Vector CP(P.getX() - C.getX(), P.getY() - C.getY(), P.getZ() - C.getZ());
    if (CP.dot(V) > _height.length())
        return false;
    if ((_radiant * 180 / M_PI) < 90) {
        if (CP.dot(V) > 0)
            return true;
        return false;
    }
    return true;
}

/**
 * @brief Check if a ray intersects with the primitive shape.
 * @param ray The ray to check for intersection.
 * @return True if the ray intersects with the shape, false otherwise.
 */
bool Cone::intersect(const Ray &ray) const
{
    if (!intersect_base(ray)) {
        return intersectCone(ray);
    }
    return true;
}

/**
 * @brief Get the intersection point with the base of the cone (represented by a circle)
 * @param ray The ray to check for intersection.
 * @return the intersection point between the ray and the base
 */
Math::Point Cone::getIntersectBase(const Ray &ray) const
{
    Math::Vector normal = _height * -1;
    double denom = normal.dot(ray.getDirection());
    if (std::abs(denom) > 1e-6) {
        Math::Point p0 = _tip + _height;
        Math::Vector p0l0 = p0 - ray.getOrigin();
        double t = p0l0.dot(normal) / denom;
        if (t >= 1e-6) {
            Math::Point p = ray.getOrigin() + ray.getDirection() * t;
            double l = _height.length() / std::cos(_radiant);
            double radius = sqrt((l * l) - (_height.length() * _height.length()));
            if ((p - p0).length() > radius) return Math::Point();
            return p;
        }
    }
    return Math::Point();
}

/**
 * @brief Get the intersection point with the cone
 * @param ray The ray to check for intersection.
 * @return the intersection point between the ray and the cone
 */
Math::Point Cone::getIntersectCone(const Ray &ray) const
{
    Math::Vector D = ray.getDirection();
    Math::Vector V = _height.normalize();
    Math::Point C = _tip;
    Math::Point O = ray.getOrigin();
    Math::Vector CO(O.getX() - C.getX(), O.getY() - C.getY(), O.getZ() - C.getZ());
    double cos2 = std::cos(_radiant) * std::cos(_radiant);

    double D_dot_V = D.dot(V);
    double CO_dot_V = CO.dot(V);
    double D_dot_D = D.dot(D);
    double D_dot_CO = D.dot(CO);
    double CO_dot_CO = CO.dot(CO);

    double a = D_dot_V * D_dot_V - D_dot_D * cos2;
    double b = 2.0 * (D_dot_V * CO_dot_V - D_dot_CO * cos2);
    double c = CO_dot_V * CO_dot_V - CO_dot_CO * cos2;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0.0)
        return Math::Point();

    double t1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + std::sqrt(discriminant)) / (2.0 * a);

    double t = (t1 > 0) ? t1 : t2;

    if (t < 0)
        return Math::Point();

    // Check whether it is the correct cone or not
    Math::Point P(ray.getOrigin() + ray.getDirection() * t);
    Math::Vector CP(P.getX() - C.getX(), P.getY() - C.getY(), P.getZ() - C.getZ());
    if (CP.dot(V) > _height.length())
        return Math::Point();
    if ((_radiant * 180 / M_PI) < 90) {
        if (CP.dot(V) > 0)
            return ray.getOrigin() + ray.getDirection() * t;
        return Math::Point();
    }
    return ray.getOrigin() + ray.getDirection() * t;
}

/**
 * @brief This function does exactly what you think it does
 * @param ray The ray to check for intersection.
 * @return the intersection point between a Ray and a shape
 */
Math::Point Cone::getIntersection(const Ray &ray) const
{
    Math::Point intersect = getIntersectBase(ray);
    if (intersect == Math::Point(0, 0, 0)) {
        intersect = getIntersectCone(ray);
    }
    return intersect;
}

/**
 * @brief Create a normal vector to the shape
 * @param point origin of the normal vector
 * @return normal vector to the shape
 */
Math::Vector Cone::normal_at(const Math::Point &point) const
{
    Math::Vector CP = point - _tip;
    Math::Vector V = _height.normalize();

    double projection = CP.dot(V);
    double height = _height.length();

    if (fabs(projection - height) < 1e-6) {
        return Math::Vector(
            point.getX() - _tip.getX(),
            point.getY() - _tip.getY(),
            point.getZ() - _tip.getZ()
        ).normalize();
    }
    Math::Vector radial = CP - (V * projection);
    double l = _height.length() / std::cos(_radiant);
    double radius = sqrt((l * l) - (_height.length() * _height.length()));
    Math::Vector normal = (radial - (V * (radius / height))).normalize();
    return normal;
}

/**
 * @brief Get the color of the primitive shape.
 * @return The color of the shape.
 */
Color Cone::getColor() const
{
    return _color;
}

/**
 * @brief Get the material of the primitive shape.
 * @return The material of the shape.
 */
std::shared_ptr<AMaterial> Cone::getMaterial() const
{
    return _material;
}
