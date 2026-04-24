/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Point
*/

#include "Point.hpp"

namespace Math {
    /**
     * @brief Default constructor for Point class.
     * Initializes the point to (0, 0, 0).
     * @note This constructor can be used to create a "null" point.
     */
    Point::Point() : _x(0), _y(0), _z(0)
    {
    }

    /**
     * @brief Default constructor for Point class.
     * Initializes the point to (0, 0, 0).
     * @param x The x-coordinate of the point.
     * @param y The y-coordinate of the point.
     * @param z The z-coordinate of the point.
     * @note This constructor can be used to create a point with specific coordinates.
     */
    Point::Point(double x, double y, double z) : _x(x), _y(y), _z(z)
    {
    }

    /**
     * @brief Overload of the operator + for two Points
     * @param point point to add to the other
     * @return a newly created point represented by the add of two points
     */
    Point Point::operator+(const Point &point) const
    {
        return Point(_x + point.getX(), _y + point.getY(), _z + point.getZ());
    }

    /**
     * @brief Overload of the operator + for a Point and a Vector
     * @param Vector vector to add to the other point
     * @return a newly created point represented by the add of a point
     * and a vector
     */
    Point Point::operator+(const Vector &vector) const
    {
        return Point(_x + vector.getX(), _y + vector.getY(), _z + vector.getZ());
    }

    /**
     * @brief Overload of the operator + for a Point and a Vector
     * @param Vector vector to add to the other point
     * @return a newly created point represented by the add of a point
     * and a vector
     */
    Point Point::operator-(const Vector &vector) const
    {
        return Point(_x - vector.getX(), _y - vector.getY(), _z - vector.getZ());
    }

    /**
     * @brief Overload of the operator += for a Point and a Vector
     * @param Vector vector to add to the other point
     * @return add to the current point coordinate of the vector
     */
    Point &Point::operator+=(const Vector &vector)
    {
        _x += vector.getX();
        _y += vector.getY();
        _z += vector.getZ();
        return *this;
    }

    /**
     * @brief Overload of the operator == for a Point and another Point
     * @param point point to check the equality
     * @return true if both are the same, false if not
     */
    bool Point::operator==(const Point &point) const
    {
        return (_x == point.getX() && _y == point.getY() && _z == point.getZ());
    }

    /**
     * @brief Generate a vector between two points
     * @param other other end of the vector represented by a point
     * @return a newly created vector
     */
    Vector Point::operator-(const Point &other) const
    {
        return Vector(_x - other.getX(), _y - other.getY(), _z - other.getZ());
    }

    /**
     * @brief This does exactly what you think it does
     * @return the X attribute of the current point
     */
    double Point::getX() const
    {
        return _x;
    }

    /**
     * @brief This does exactly what you think it does
     * @return the Y attribute of the current point
     */
    double Point::getY() const
    {
        return _y;
    }

    /**
     * @brief This does exactly what you think it does
     * @return the Z attribute of the current point
     */
    double Point::getZ() const
    {
        return _z;
    }

    /**
     * @return set X attribute of the current point
     */
    void Point::setX(const double x)
    {
        this->_x = x;
    }

    /**
     * @return set Y attribute of the current point
     */
    void Point::setY(const double y)
    {
        this->_y = y;
    }

    /**
     * @brief This does exactly what you think it does
     */
    void Point::setZ(const double z)
    {
        this->_z = z;
    }

    /**
     * @brief Dot product of two vectors.
     * @param other The vector to dot with.
     * @return The dot product of this vector and the other vector.
     */
    double Point::dot(const Vector &other) const
    {
        return (_x * other.getX() + _y * other.getY() + _z * other.getZ());
    }
}
