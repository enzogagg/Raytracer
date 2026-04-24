/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Translation
*/

/**
 * @file Translation.cpp
 * @brief Translation class implementation file.
 * @details This file contains the implementation of the Translation class,
 *     which is used to represent a translation transformation in the raytracer project.
 */
#include "Translation.hpp"

/**
 * @brief Default constructor for Translation class.
 * Initializes the translation with default values.
 * @param translation The translation
 * @note This constructor can be used to create a translation with default values.
 */
Translation::Translation()
{
}

/**
 * @brief Apply the translation to the given vector.
 * @note This function applies the translation to the given vector.
 */
void Translation::apply(Math::Point &origin, Math::Vector translation)
{
    origin += translation;
}

/**
 * @brief translate all the scene up
 */
void Translation::translateUp(Scene &scene)
{
    scene.setTranslateScene(Math::Vector(0, 0.1, 0));
}

/**
 * @brief translate all the scene down
 */
void Translation::translateDown(Scene &scene)
{
    scene.setTranslateScene(Math::Vector(0, -0.1, 0));
}

/**
 * @brief translate all the scene left
 */
void Translation::translateLeft(Scene &scene)
{
    scene.setTranslateScene(Math::Vector(0.1, 0, 0));
}

/**
 * @brief translate all the scene right
 */
void Translation::translateRight(Scene &scene)
{
    scene.setTranslateScene(Math::Vector(-0.1, 0.0, 0));
}

/**
 * @brief translate all the scene left
 */
void Translation::translateIn(Scene &scene)
{
    scene.setTranslateScene(Math::Vector(0, 0, 0.1));
}

/**
 * @brief translate all the scene right
 */
void Translation::translateOut(Scene &scene)
{
    scene.setTranslateScene(Math::Vector(0, 0.0, -0.1));
}
