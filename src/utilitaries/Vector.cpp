/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Vector
*/

/**
 * @file Vector.cpp
 * @brief Vector class implementation.
 * @details This file contains the implementation of the Vector class,
 *      which is used for vector representation in the raytracer project.
 * @note The Vector class is used to represent 3D vectors and perform vector operations.
 */
#include "Vector.hpp"

namespace Math {

    /**
     * @brief Default constructor for Vector class.
     * Initializes the vector to (0, 0, 0).
     * @param x The x-coordinate of the vector.
     * @param y The y-coordinate of the vector.
     * @param z The z-coordinate of the vector.
     * @note If no parameters are provided, the vector is initialized to (0, 0, 0).
     * @note This constructor can be used to create a vector with specific coordinates.
     */
    Vector::Vector(double x, double y, double z)
        : _x(x), _y(y), _z(z)
    {
        return;
    }

    /**
     * @brief Length of the vector.
     * @return The length of the vector.
     */
    double Vector::length() const
    {
        return sqrt(_x * _x + _y * _y + _z * _z);
    }

    /**
     * @brief Dot product of two vectors.
     * @param other The vector to dot with.
     * @return The dot product of this vector and the other vector.
     */
    double Vector::dot(const Vector &other) const
    {
        return (_x * other.getX() + _y * other.getY() + _z * other.getZ());
    }

    /**
     * @brief Normalize the vector.
     * @return A new vector that is the normalized version of this vector.
     */
    Vector Vector::normalize() const
    {
        double len = length();
        if (len == 0)
            return Vector(0, 0, 0);
        return Vector(_x / len, _y / len, _z / len);
    }

    /**
     * @brief Addition operator overload.
     * @param other The vector to add.
     * @return A new vector that is the sum of this vector and the other vector.
     */
    Vector Vector::operator+(const Vector &other) const
    {
        return Vector(_x + other.getX(), _y + other.getY(), _z + other.getZ());
    }

    /**
     * @brief Addition operator overload.
     * @param other The vector to add.
     * @return A new vector that is the sum of this vector and the other vector.
     */
    Vector &Vector::operator+=(const Vector &other)
    {
        _x += other.getX(); _y += other.getY(); _z += other.getZ();
        return *this;
    }

    /**
     * @brief Subtraction operator overload.
     * @param other The vector to subtract.
     * @return A new vector that is the difference of this vector and the other vector.
     */
    Vector Vector::operator-(const Vector &other) const
    {
        return Vector(_x - other.getX(), _y - other.getY(), _z - other.getZ());
    }

    /**
     * @brief Subtraction operator overload.
     * @param other The vector to subtract.
     * @return A new vector that is the difference of this vector and the other vector.
     */
    Vector &Vector::operator-=(const Vector &other)
    {
        _x -= other.getX(); _y -= other.getY(); _z -= other.getZ();
        return *this;
    }

    /**
     * @brief Scalar multiplication operator overload.
     * @param other The vector to multiply with.
     * @return A new vector that is the product of this vector and the scalar.
     */
    Vector Vector::operator*(const Vector &other) const
    {
        return Vector(_x * other.getX(), _y * other.getY(), _z * other.getZ());
    }

    /**
     * @brief Scalar multiplication operator overload.
     * @param other The vector to multiply with.
     * @return A new vector that is the product of this vector and the scalar.
     */
    Vector &Vector::operator*=(const Vector &other)
    {
        _x *= other.getX(); _y *= other.getY(); _z *= other.getZ();
        return *this;
    }

    /**
     * @brief Scalar multiplication operator overload.
     * @param scalar The scalar to multiply with.
     * @return A new vector that is the product of this vector and the scalar.
     */
    Vector Vector::operator*(double scalar) const
    {
        return Vector(_x * scalar, _y * scalar, _z * scalar);
    }

    Vector operator*(double scalar, const Vector &vector)
    {
        return vector * scalar;
    }

    /**
     * @brief Scalar multiplication operator overload.
     * @param scalar The scalar to multiply with.
     * @return A new vector that is the product of this vector and the scalar.
     */
    Vector &Vector::operator*=(double scalar)
    {
        _x *= scalar; _y *= scalar; _z *= scalar;
        return *this;
    }

    /**
     * @brief Scalar division operator overload.
     * @param other The vector to divide with.
     * @return A new vector that is the quotient of this vector and the scalar.
     */
    Vector Vector::operator/(const Vector &other) const
    {
        if (other.getX() == 0 || other.getY() == 0 || other.getZ() == 0) {
            throw RaytracerException("Division by zero");
        }
        return Vector(_x / other.getX(), _y / other.getY(), _z / other.getZ());
    }

    /**
     * @brief Scalar division operator overload.
     * @param other The vector to divide with.
     * @return A new vector that is the quotient of this vector and the scalar.
     */
    Vector &Vector::operator/=(const Vector &other)
    {
        if (other.getX() == 0 || other.getY() == 0 || other.getZ() == 0) {
            throw RaytracerException("Division by zero");
        }
        _x /= other.getX(); _y /= other.getY(); _z /= other.getZ();
        return *this;
    }

    /**
     * @brief Scalar division operator overload.
     * @param scalar The scalar to divide by.
     * @return A new vector that is the quotient of this vector and the scalar.
     */
    Vector Vector::operator/(double scalar) const
    {
        if (scalar == 0) {
            throw RaytracerException("Division by zero");
        }
        return Vector(_x / scalar, _y / scalar, _z / scalar);
    }

    /**
     * @brief Scalar division operator overload.
     * @param scalar The scalar to divide by.
     * @return A new vector that is the quotient of this vector and the scalar.
     */
    Vector &Vector::operator/=(double scalar)
    {
        if (scalar == 0) {
            throw RaytracerException("Division by zero");
        }
        _x /= scalar;
        _y /= scalar;
        _z /= scalar;
        return *this;
    }

    /**
     * @brief Check equality operator overload.
     * @param other The vector to compare with.
     * @return True if the vectors are equal, false otherwise.
     */
    bool Vector::operator==(const Vector &other) const
    {
        if (this->_x == other.getX() && this->_y == other.getY() && this->_z == other.getZ())
            return true;
        return false;
    }

    /**
     * @brief Check equality operator overload.
     * @param other The vector to compare with.
     * @return True if the vectors are equal, false otherwise.
     */
    bool Vector::operator==(std::string axis) const
    {
        if (axis == "X" && *this == Math::Vector(1, 0, 0))
            return true;
        if (axis == "Y" && *this == Math::Vector(0, 1, 0))
            return true;
        if (axis == "Z" && *this == Math::Vector(0, 0, 1))
            return true;
        return false;
    }


    /**
     * @brief Get the x-coordinate of the vector.
     * @return The x-coordinate of the vector.
     */
    double Vector::getX() const
    {
        return _x;
    }

    /**
     * @brif Get the y-coordinate of the vector.
     * @return The y-coordinate of the vector.
     */
    double Vector::getY() const
    {
        return _y;
    }

    /**
     * @brif Get the z-coordinate of the vector.
     * @return The z-coordinate of the vector.
     */
    double Vector::getZ() const
    {
        return _z;
    }

    /**
     * @brief Cross product of two vector
     * @param other The vector to calculate the cross product
     * @return A new vector that is the result of the cross product between two vectors
     * @note This function can be used to calculate a normal vector of two other ones
     */
    Vector Vector::crossProduct(const Vector &other) const
    {
        return Vector(
            (this->_y * other.getZ()) - (this->_z * other.getY()),
            (this->_z * other.getX()) - (this->_x * other.getZ()),
            (this->_x * other.getY()) - (this->_y * other.getX())
        );
    }

    inline double Vector::random_double()
    {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator(std::random_device{}());
        return distribution(generator);
    }

    inline double Vector::random_double(double min, double max)
    {
        static std::uniform_real_distribution<double> distribution(min, max);
        static std::mt19937 generator(std::random_device{}());
        return distribution(generator);
    }

    Vector Vector::random() {
        return Vector(random_double(), random_double(), random_double());
    }

    Vector Vector::random(double min, double max) {
        return Vector(random_double(min,max), random_double(min,max), random_double(min,max));
    }

    bool Vector::near_zero() const {
        auto s = 1e-8;
        return (std::fabs(_x) < s) && (std::fabs(_y) < s) && (std::fabs(_z) < s);
    }

    Vector Vector::reflect(const Vector& v, const Vector& n)
    {
        return v - n * v.dot(n) * 2;
    }

    Vector Vector::invert() const
    {
        return Vector(-_x, -_y, -_z);
    }
}
