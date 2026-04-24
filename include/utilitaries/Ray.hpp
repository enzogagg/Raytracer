/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Ray
*/

/**
 * @file Ray.hpp
 * @brief Ray class header file.
 * @details This file contains the definition of the Ray class,
 *      which is used for ray representation in the raytracer project.
 * @note The Ray class is used to represent rays in 3D space.
 */
#pragma once

#include "Vector.hpp"
#include "Define.hpp"
#include "Point.hpp"

/**
 * @class Ray
 * @brief A class to represent a ray in 3D space.
 */
class Ray {
    public:

        /**
         * @brief Default constructor for Ray class.
         * Initializes the ray with a position and direction.
         * @param origin The origin of the ray.
         * @param direction The direction of the ray.
         * @note If no parameters are provided, the ray is initialized to (0, 0, 0).
         * @note This constructor can be used to create a ray with specific origin and direction.
         */
        Ray(const Math::Point &origin = Math::Point(), const Math::Vector &direction = Math::Vector());

        /**
         * @brief Get the origin of the ray.
         * @return The origin of the ray.
         */
        const Math::Point &getOrigin() const;

        /**
         * @brief Get the direction of the ray.
         * @return The direction of the ray.
         */
        const Math::Vector &getDirection() const;

        /**
         * @brief Set the origin of the ray.
         * @param origin origin to be set
         */
        void setOrigin(const Math::Point &origin);

        /**
         * @brief Set the direction of the ray.
         * @param direction direction of the ray.
         */
        void setDirection(const Math::Vector &direction);

    private:
        Math::Point _origin;
        Math::Vector _direction;
};
