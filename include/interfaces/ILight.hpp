/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** ILight
*/

/**
 * @file ILight.hpp
 * @brief ILight class header file.
 * @details This file contains the definition of the ILight class,
 *     which is an interface for light sources in the raytracer project.
 * @note The ILight class is used to define the interface for all light sources.
 * @note All light sources must implement this interface.
 */
#pragma once

#include "Vector.hpp"
#include "Color.hpp"
#include "Define.hpp"
#include "Point.hpp"

/**
 * @class ILight
 * @brief An interface for light sources in the raytracer project.
 */
class ILight {
    public:
        /**
         * @brief Virtual destructor for ILight class.
         * @note This destructor is virtual to ensure proper cleanup of derived classes.
         */
        virtual ~ILight() = default;

        /**
         * @brief Get the type of the light source.
         * @return The type of the light source.
         */
        virtual const std::string &getType() const = 0;

        /**
         * @brief Get the position of the light source.
         * @return The position of the light source.
         */
        virtual const Math::Point &getPosition() const = 0;

        /**
         * @brief getDirection
         * @brief Get the direction of the light source.
         * @return The direction of the light source.
         */
        virtual const Math::Vector &getDirection() const = 0;

        /**
         * @brief Get the intensity of the light source.
         * @return The intensity of the light source.
         */
        virtual float getIntensity() const = 0;

        /**
         * @brief Get the color of the light source.
         * @return The color of the light source.
         */
        virtual const Color &getColor() const = 0;

        /**
         * @brief Get the ambient component of the light source.
         * @return The ambient component of the light source.
         */
        virtual const Color &getAmbientComponent() const = 0;

        /**
         * @brief Get the diffuse component of the light source.
         * @return The diffuse component of the light source.
         */
        virtual const Color &getDiffuseComponent() const = 0;

        /**
         * @brief Get the specular component of the light source.
         * @return The specular component of the light source.
         */
        virtual const Color &getSpecularComponent() const = 0;
};
