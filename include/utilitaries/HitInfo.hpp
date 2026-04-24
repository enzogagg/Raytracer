/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** HitInfo
*/

/**
 * @file HitInfo.hpp
 * @brief HitInfo class header file
 * @details This file contains the definition of the HitInfo class,
 *         which is used to store information about a hit in the raytracer project.
 */
#pragma once

#include "Vector.hpp"
#include "Color.hpp"
#include "Define.hpp"

/**
 * @class HitInfo
 * @brief A class to represent hit information in the raytracer project.
 */
class HitInfo {
    public:

        /**
         * @brief Default constructor for HitInfo class.
         * Initializes the hit information with default values.
         * @note This constructor can be used to create a HitInfo object with default values.
         */
        HitInfo();

        /**
         * @brief Constructor for HitInfo class with parameters.
         * Initializes the hit information with specific values.
         * @param position The position of the hit.
         * @param normal The normal vector at the hit point.
         * @param color The color of the hit.
         * @param distance The distance from the ray origin to the hit point.
         */
        HitInfo(const Math::Vector &position, const Math::Vector &normal, const Color &color, float distance);

        /**
         * @brief Get the position of the hit.
         * @return The position of the hit.
         * @note This method returns the position vector of the hit.
         */
        const Math::Vector &getPosition() const;

        /**
         * @brief Get the normal vector at the hit point.
         * @return The normal vector at the hit point.
         * @note This method returns the normal vector of the hit.
         */
        const Math::Vector &getNormal() const;

        /**
         * @brief Get the color of the hit.
         * @return The color of the hit.
         * @note This method returns the color of the hit.
         */
        const Color &getColor() const;

        /**
         * @brief Get the distance from the ray origin to the hit point.
         * @return The distance from the ray origin to the hit point.
         * @note This method returns the distance of the hit.
         * @note The distance is a float value representing the distance from the ray origin to the hit point.
         * @note This method can be used to determine how far the hit point is from the ray origin.
         * @note Example usage:
         * HitInfo hitInfo;
         */
        float getDistance() const;

    private:
        Math::Vector _position;
        Math::Vector _normal;
        Color _color;
        float _distance;
};
