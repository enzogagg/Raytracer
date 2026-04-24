/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Rotation
*/

#include "Rotation.hpp"

Rotation::Rotation()
{
}

/**
 * @brief Apply the translation to the given vector.
 * @note This function applies the translation to the given vector.
 */
void Rotation::apply(Math::Point &origin, Math::Vector translation)
{
    origin += translation;
}

/**
 * @brief Rotate in the X axis
 */
void Rotation::RotateX(bool Ctrl_pressed, Scene &scene)
{
    if (Ctrl_pressed)
        scene.setRotate(-1.0, "X");
    else
        scene.setRotate(1.0, "X");
}

/**
* @brief Rotate in the Y axis
*/
void Rotation::RotateY(bool Ctrl_pressed, Scene &scene)
{
    if (Ctrl_pressed)
        scene.setRotate(-1.0, "Y");
    else
        scene.setRotate(1.0, "Y");
}

/**
* @brief Rotate in the Y axis
*/
void Rotation::RotateZ(bool Ctrl_pressed, Scene &scene)
{
    if (Ctrl_pressed)
        scene.setRotate(-1.0, "Z");
    else
        scene.setRotate(1.0, "Z");
}