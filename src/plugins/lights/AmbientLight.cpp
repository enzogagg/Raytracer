/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** AmbientLight
*/

/**
 * @file AmbientLight.cpp
 * @brief AmbientLight class implementation.
 * @details This file contains the implementation of the AmbientLight class,
 *      which is a plugin for the raytracer project.
 * @note The AmbientLight class represents an ambient light source in the scene.
 */
#include "AmbientLight.hpp"

/**
 * @brief Constructor for the AmbientLight class.
 * @param intensity The intensity of the light source.
 */
AmbientLight::AmbientLight(float intensity, const Color &color)
    : _intensity(intensity), _ambient(color)
{
    return;
}

/**
 * @brief Get the type of the light source.
 * @return The type of the light source.
 */
const std::string &AmbientLight::getType() const
{
    static std::string type("ambient");
    return type;
}

/**
 * @brief Get the position of the light source.
 * @return The position of the light source.
 */
const Math::Point &AmbientLight::getPosition() const
{
    static Math::Point position(0.0f, 0.0f, 0.0f);
    return position;
}

/**
 * @brief Get the direction of the light source.
 * @return The direction of the light source.
 */
const Math::Vector &AmbientLight::getDirection() const
{
    static Math::Vector direction(0.0f, 0.0f, 0.0f);
    return direction;
}

/**
 * @brief Get the intensity of the light source.
 * @return The intensity of the light source.
 */
float AmbientLight::getIntensity() const
{
    return _intensity;
}

/**
 * @brief Get the color of the light source.
 * @return The color of the light source.
 */
const Color &AmbientLight::getColor() const
{
    return _ambient;
}

/**
 * @brief Get the ambient component of the light source.
 * @return The ambient component of the light source.
 */
const Color &AmbientLight::getAmbientComponent() const
{
    return _ambient;
}

/**
 * @brief Get the diffuse component of the light source.
 * @return The diffuse component of the light source.
 */
const Color &AmbientLight::getDiffuseComponent() const
{
    static Color diffuse(0.0f, 0.0f, 0.0f);
    return diffuse;
}

/**
 * @brief Get the specular component of the light source.
 * @return The specular component of the light source.
 */
const Color &AmbientLight::getSpecularComponent() const
{
    static Color specular(0.0f, 0.0f, 0.0f);
    return specular;
}