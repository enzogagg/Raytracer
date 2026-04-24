/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Vector
*/

/**
 * @file Vector.hpp
 * @brief Vector class header file.
 * @details This file contains the definition of the Vector class,
 *      which is used for mathematical operations in the raytracer project.
 */
#pragma once

#include "Exception.hpp"
#include "Define.hpp"
#include "Matrix.hpp"

namespace Math {
    /**
     * @class Vector
     * @brief A class to represent a 3D vector with basic operations.
     */
    class Vector {
        public:

            /**
             * @brief Default constructor for Vector class.
             * Initializes the vector to (0, 0, 0).
             * @param x The x-coordinate of the vector.
             * @param y The y-coordinate of the vector.
             * @param z The z-coordinate of the vector.
             * @note If no parameters are provided, the vector is initialized to (0, 0, 0).
             * @note This constructor can be used to create a vector with specific coordinates.
             */
            Vector(double x = 0, double y = 0, double z = 0);

            /**
             * @brief Length of the vector.
             * @return The length of the vector.
             */
            double length() const;

            /**
             * @brief Dot product of two vectors.
             * @param other The vector to dot with.
             * @return The dot product of this vector and the other vector.
             */
            double dot(const Vector &other) const;

            /**
             * @brief Normalize the vector.
             * @return A new vector that is the normalized version of this vector.
             */
            Vector normalize() const;

            Vector invert() const;

            /**
             * @brief Addition operator overload.
             * @param other The vector to add.
             * @return A new vector that is the sum of this vector and the other vector.
             */
            Vector operator+(const Vector &other) const;

            /**
             * @brief Addition operator overload.
             * @param other The vector to add.
             * @return A new vector that is the sum of this vector and the other vector.
             */
            Vector &operator+=(const Vector &other);

            /**
             * @brief Subtraction operator overload.
             * @param other The vector to subtract.
             * @return A new vector that is the difference of this vector and the other vector.
             */
            Vector operator-(const Vector &other) const;

            /**
             * @brief Subtraction operator overload.
             * @param other The vector to subtract.
             * @return A new vector that is the difference of this vector and the other vector.
             */
            Vector &operator-=(const Vector &other);

            /**
             * @brief Scalar multiplication operator overload.
             * @param other The vector to multiply with.
             * @return A new vector that is the product of this vector and the scalar.
             */
            Vector operator*(const Vector &other) const;

            /**
             * @brief Scalar multiplication operator overload.
             * @param other The vector to multiply with.
             * @return A new vector that is the product of this vector and the scalar.
             */
            Vector &operator*=(const Vector &other);

            /**
             * @brief Scalar multiplication operator overload.
             * @param scalar The scalar to multiply with.
             * @return A new vector that is the product of this vector and the scalar.
             */
            Vector operator*(double scalar) const;

            /**
             * @brief Scalar multiplication operator overload.
             * @param scalar The scalar to multiply with.
             * @return A new vector that is the product of this vector and the scalar.
             */
            Vector &operator*=(double scalar);

            /**
             * @brief Scalar division operator overload.
             * @param other The vector to divide with.
             * @return A new vector that is the quotient of this vector and the scalar.
             */
            Vector operator/(const Vector &other) const;

            /**
             * @brief Scalar division operator overload.
             * @param other The vector to divide with.
             * @return A new vector that is the quotient of this vector and the scalar.
             */
            Vector &operator/=(const Vector &other);

            /**
             * @brief Scalar division operator overload.
             * @param scalar The scalar to divide by.
             * @return A new vector that is the quotient of this vector and the scalar.
             */
            Vector operator/(double scalar) const;

            /**
             * @brief Scalar division operator overload.
             * @param scalar The scalar to divide by.
             * @return A new vector that is the quotient of this vector and the scalar.
             */
            Vector &operator/=(double scalar);

            /**
             * @brief Check equality operator overload.
             * @param other The vector to compare with.
             * @return True if the vectors are equal, false otherwise.
             */
            bool operator==(const Vector &other) const;

            /**
             * @brief Check equality operator overload.
             * @param other The vector to compare with.
             * @return True if the vectors are equal, false otherwise.
             */
            bool operator==(std::string axis) const;

            /**
             * @brief Get the x-coordinate of the vector.
             * @return The x-coordinate of the vector.
             */
            double getX() const;

            /**
             * @brief Get the y-coordinate of the vector.
             * @return The y-coordinate of the vector.
             */
            double getY() const;

            /**
             * @brief Get the z-coordinate of the vector.
             * @return The z-coordinate of the vector.
             */
            double getZ() const;

            /**
             * @brief Cross product of two vector
             * @param other The vector to calculate the cross product
             * @return A new vector that is the result of the cross product between two vectors
             * @note This function can be used to calculate a normal vector of two other ones
             */
            Vector crossProduct(const Vector &other) const;

            Math::Matrix<4, 1> vectorToMatrix()
            {
                Math::Matrix<4, 1> result;
                result._matrix[0][0] = _x;
                result._matrix[1][0] = _y;
                result._matrix[2][0] = _z;
                result._matrix[3][0] = 1.0;
                return result;
            }

            Math::Matrix<1, 2> shearToMatrix()
            {
                Math::Matrix<1, 2> result;
                result._matrix[0][0] = _x;
                result._matrix[0][1] = _y;
                return result;
            }

            inline double random_double();
            inline double random_double(double min, double max);
            Vector random();
            Vector random(double min, double max);
            bool near_zero() const;
            Vector reflect(const Vector& v, const Vector& n);
            
            /**
             * @brief Unary negation operator overload.
             * @return A new vector that is the negation of this vector.
             */
            Vector operator-() const { return Vector(-_x, -_y, -_z); } // Unary negation
        private:
            double _x;
            double _y;
            double _z;
    };

    /**
     * @brief Scalar multiplication operator overload (commutative).
     * @param scalar The scalar to multiply with.
     * @param vector The vector to multiply with the scalar.
     * @return A new vector that is the product of the scalar and the vector.
     */
    Vector operator*(double scalar, const Vector &vector);
}
