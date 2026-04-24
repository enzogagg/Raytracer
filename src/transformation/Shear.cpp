/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Shear
*/

#include "Shear.hpp"

Shear::Shear()
{
}

/**
 * @brief Apply the translation to the given vector.
 * @note This function applies the translation to the given vector.
 */
void Shear::apply(Math::Point &origin, Math::Vector translation)
{
    origin += translation;
}

/**
* @brief Rotate in the Y axis
*/
void Shear::shear(Scene &scene)
{
    scene.setShear(0.1);
}
