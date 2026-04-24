/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** IPrimitive
*/

/**
 * @file IPrimitive.hpp
 * @brief IPrimitive class header file.
 * @details This file contains the definition of the IPrimitive class,
 *      which is an interface for primitive shapes in the raytracer project.
 * @note The IPrimitive class is used to define the interface for all primitive shapes.
 */
#pragma once

#include "Ray.hpp"
#include "Color.hpp"
#include "Define.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "AMaterial.hpp"

/**
 * @class IPrimitive
 * @brief An interface for primitive shapes in the raytracer project.
 */
class IPrimitive {
    public:
        /**
         * @brief Virtual destructor for IPrimitive class.
         * @note This destructor is virtual to ensure proper cleanup of derived classes.
         */
        virtual ~IPrimitive() = default;

        /**
         * @brief Get the type of the primitive shape.
         * @return The type of the shape as a string.
         */
        virtual const std::string &getType() const = 0;

        /**
         * @brief Check if a ray intersects with the primitive shape.
         * @param ray The ray to check for intersection.
         * @return True if the ray intersects with the shape, false otherwise.
         */
        virtual bool intersect(const Ray &ray) const = 0;

        /**
         * @brief This function does exactly what you think it does
         * @param ray The ray to check for intersection.
         * @return the intersection point between a Ray and a shape
         */
        virtual Math::Point getIntersection(const Ray &ray) const = 0;

        /**
         * @brief Create a normal vector to the shape
         * @param point origin of the normal vector
         * @return normal vector to the shape
         */
        virtual Math::Vector normal_at(const Math::Point &point) const = 0;

        /**
         * @brief Get the color of the primitive shape.
         * @return The color of the shape.
         */
        virtual Color getColor() const = 0;

        /**
         * @brief Get the material of the primitive shape.
         * @return The material of the shape.
         */
        virtual std::shared_ptr<AMaterial> getMaterial() const = 0;
};
