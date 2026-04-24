/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Rotation
*/

/**
 * @file Rotation.hpp
 * @brief Rotation class header file.
 * @details This file contains the definition of the Rotation class,
 *     which is used to represent a Rotation transformation in the raytracer project.
 */
#pragma once

#include "ITransformations.hpp"
#include "Define.hpp"
#include "Scene.hpp"

/**
 * @brief A class to represent a Rotation transformation.
 * @details This class is used to represent a Rotation transformation
 *     in the raytracer project. It inherits from the ITransformations interface.
 * @note The Rotation class is responsible for applying Rotation transformations
 */
class Rotation : public ITransformations {
    public:
        /**
         * @brief Default constructor for Rotation class.
         * Initializes the Rotation with default values.
         * @note This constructor can be used to create a Rotation with default values.
         */
        Rotation();

        /**
         * @brief Destructor for Rotation class.
         * Cleans up resources used by the Rotation.
         * @note This destructor is called when the Rotation object is destroyed.
         */
        ~Rotation() override = default;

        /**
         * @brief Apply the Rotation to the given vector.
         * @param inverted A boolean indicating whether to apply the transformation in reverse.
         * @note This function applies the Rotation to the given vector.
         */
        void apply(Math::Point &origin, Math::Vector Rotation) override;

        /**
         * @brief Rotate in the X axis
         */
        void RotateX(bool Ctrl_pressed, Scene &scene);

        /**
         * @brief Rotate in the Y axis
         */
        void RotateY(bool Ctrl_pressed, Scene &scene);

        /**
         * @brief Rotate in the Y axis
         */
        void RotateZ(bool Ctrl_pressed, Scene &scene);

};
