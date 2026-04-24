/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Translation
*/

/**
 * @file Translation.hpp
 * @brief Translation class header file.
 * @details This file contains the definition of the Translation class,
 *     which is used to represent a translation transformation in the raytracer project.
 */
#pragma once

#include "ITransformations.hpp"
#include "Define.hpp"
#include "Scene.hpp"

/**
 * @brief A class to represent a translation transformation.
 * @details This class is used to represent a translation transformation
 *     in the raytracer project. It inherits from the ITransformations interface.
 * @note The Translation class is responsible for applying translation transformations
 */
class Translation : public ITransformations {
    public:
        /**
         * @brief Default constructor for Translation class.
         * Initializes the translation with default values.
         * @note This constructor can be used to create a translation with default values.
         */
        Translation();

        /**
         * @brief Destructor for Translation class.
         * Cleans up resources used by the translation.
         * @note This destructor is called when the translation object is destroyed.
         */
        ~Translation() override = default;

        /**
         * @brief Apply the translation to the given vector.
         * @param inverted A boolean indicating whether to apply the transformation in reverse.
         * @note This function applies the translation to the given vector.
         */
        void apply(Math::Point &origin, Math::Vector translation) override;

        /**
         * @brief translate all the scene up
         */
        void translateUp(Scene &scene);

        /**
         * @brief translate all the scene down
         */
        void translateDown(Scene &scene);

        /**
         * @brief translate all the scene left
         */
        void translateLeft(Scene &scene);

        /**
         * @brief translate all the scene right
         */
        void translateRight(Scene &scene);

        /**
         * @brief translate all the scene up
         */
        void translateIn(Scene &scene);

        /**
         * @brief translate all the scene down
         */
        void translateOut(Scene &scene);
};
