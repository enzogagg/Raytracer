/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Shear
*/

/**
 * @file Shear.hpp
 * @brief Shear class header file.
 * @details This file contains the definition of the Shear class,
 *     which is used to represent a Shear transformation in the raytracer project.
 */
#pragma once

#include "ITransformations.hpp"
#include "Define.hpp"
#include "Scene.hpp"

/**
 * @brief A class to represent a Shear transformation.
 * @details This class is used to represent a Shear transformation
 *     in the raytracer project. It inherits from the ITransformations interface.
 * @note The Shear class is responsible for applying Shear transformations
 */
class Shear : public ITransformations {
    public:
        /**
         * @brief Default constructor for Shear class.
         * Initializes the Shear with default values.
         * @note This constructor can be used to create a Shear with default values.
         */
        Shear();

        /**
         * @brief Destructor for Shear class.
         * Cleans up resources used by the Shear.
         * @note This destructor is called when the Shear object is destroyed.
         */
        ~Shear() override = default;

        /**
         * @brief Apply the Shear to the given vector.
         * @param inverted A boolean indicating whether to apply the transformation in reverse.
         * @note This function applies the Shear to the given vector.
         */
        void apply(Math::Point &origin, Math::Vector Shear) override;

        /**
         * @brief Rotate in the X axis
         */
        void shear(Scene &scene);
};
