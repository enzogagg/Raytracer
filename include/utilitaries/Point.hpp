/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Point
*/

#pragma once

#include "Vector.hpp"
#include "Matrix.hpp"

namespace Math {

    /**
     * @class Point
     * @brief A class to represent a 3D point with basic operations.
     */
    class Point {
        public:

            /**
             * @brief Default constructor for Point class.
             * Initializes the point to (0, 0, 0).
             * @note This constructor can be used to create a "null" point.
             */
            Point();

            /**
             * @brief Default constructor for Point class.
             * Initializes the point to (0, 0, 0).
             * @param x The x-coordinate of the point.
             * @param y The y-coordinate of the point.
             * @param z The z-coordinate of the point.
             * @note This constructor can be used to create a point with specific coordinates.
             */
            Point(double x, double y, double z);

            /**
             * @brief Overload of the operator + for two Points
             * @param point point to add to the other
             * @return a newly created point represented by the add of two points
             */
            Point operator+(const Point &point) const;

            /**
             * @brief Overload of the operator + for a Point and a Vector
             * @param Vector vector to add to the other point
             * @return a newly created point represented by the add of a point
             * and a vector
             */
            Point operator+(const Vector &vector) const;

            /**
             * @brief Overload of the operator + for a Point and a Vector
             * @param Vector vector to add to the other point
             * @return a newly created point represented by the add of a point
             * and a vector
             */
            Point operator-(const Vector &vector) const;

            /**
             * @brief Overload of the operator += for a Point and a Vector
             * @param Vector vector to add to the other point
             * @return add to the current point coordinate of the vector
             */
            Point &operator+=(const Vector &vector);

            /**
             * @brief Overload of the operator == for a Point and another Point
             * @param point point to check the equality
             * @return true if both are the same, false if not
             */
            bool operator==(const Point &point) const;

            /**
             * @brief Generate a vector between two points
             * @param other other end of the vector represented by a point
             * @return a newly created vector
             */
            Vector operator-(const Point &other) const;

            /**
             * @brief This does exactly what you think it does
             * @return the X attribute of the current point
             */
            double getX() const;

            /**
             * @brief This does exactly what you think it does
             * @return the Y attribute of the current point
             */
            double getY() const;

            /**
             * @brief This does exactly what you think it does
             * @return the Z attribute of the current point
             */
            double getZ() const;

            /**
             * @return set X attribute of the current point
             */
            void setX(const double x);

            /**
             * @return set Y attribute of the current point
             */
            void setY(const double y);

            /**
             * @brief This does exactly what you think it does
             */
            void setZ(const double z);

            Math::Matrix<4, 1> pointToMatrix()
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

            /**
             * @brief Dot product of two vectors.
             * @param other The vector to dot with.
             * @return The dot product of this vector and the other vector.
             */
            double dot(const Vector &other) const;

        protected:
        private:
            double _x;
            double _y;
            double _z;
    };
}
