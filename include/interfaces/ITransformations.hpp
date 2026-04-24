/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** ITransformations
*/

/**
 * @file ITransformations.hpp
 * @brief ITransformations interface header file.
 * @details This file contains the definition of the ITransformations interface,
 *     which is used to define the transformations of the objects in the raytracer project.
 */
#pragma once

#include "Define.hpp"
#include "Point.hpp"
#include "Vector.hpp"

/**
 * @class ITransformations
 * @brief An interface for transformations in the raytracer project.
 * @details This interface is used to define the transformations of the objects in the raytracer project.
 * @note All transformations must implement this interface.
 */
class ITransformations {
    public:
        /**
         * @brief Virtual destructor for ITransformations class.
         * @note This destructor is virtual to ensure proper cleanup of derived classes.
         */
        virtual ~ITransformations() = default;

        /**
         * @brief Apply the transformation to the given vector.
         * @param inverted A boolean indicating whether to apply the transformation in reverse.
         * @note This function applies the transformation to the given vector.
         */
        virtual void apply(Math::Point &origin, Math::Vector translation) = 0;
};
