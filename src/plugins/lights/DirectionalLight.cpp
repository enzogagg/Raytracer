/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** DirectionalLight
*/

/**
 * @file DirectionalLight.cpp
 * @brief DirectionalLight class implementation.
 * @details This file contains the implementation of the DirectionalLight class,
 *      which is a plugin for the raytracer project.
 * @note The DirectionalLight class represents a directional light source in the scene.
 */
#include "DirectionalLight.hpp"

/**
 * @brief Constructor for the DirectionalLight class.
 * @param position The position of the light source.
 * @param intensity The intensity of the light source.
 * @param direction The direction of the light source.
 */
DirectionalLight::DirectionalLight(const Math::Vector &direction,
    const Color &color, float intensity)
    : _direction(direction), _intensity(intensity), _color(color), _ambient(color * 0.1), _diffuse(color * 0.7), _specular(Color(1, 1, 1))
{
    return;
}

/**
 * @brief Get the type of the light source.
 * @return The type of the light source.
 */
const std::string &DirectionalLight::getType() const
{
    static std::string type("directional");
    return type;
}

/**
 * @brief Get the position of the light source.
 * @return The position of the light source.
 */
const Math::Point &DirectionalLight::getPosition() const
{
    static Math::Point noPosition(0, 0, 0);
    return noPosition;
}

/**
 * @brief Get the direction of the light source.
 * @return The direction of the light source.
 */
const Math::Vector &DirectionalLight::getDirection() const
{
    return _direction;
}

/**
 * @brief Get the intensity of the light source.
 * @return The intensity of the light source.
 */
float DirectionalLight::getIntensity() const
{
    return _intensity;
}

/**
 * @brief Get the color of the light source.
 * @return The color of the light source.
 */
const Color &DirectionalLight::getColor() const
{
    return _color;
}

/**
 * @brief Get the ambient component of the light source.
 * @return The ambient component of the light source.
 */
const Color &DirectionalLight::getAmbientComponent() const
{
    return _ambient;
}

/**
 * @brief Get the diffuse component of the light source.
 * @return The diffuse component of the light source.
 */
const Color &DirectionalLight::getDiffuseComponent() const
{
    return _diffuse;
}

/**
 * @brief Get the specular component of the light source.
 * @return The specular component of the light source.
 */
const Color &DirectionalLight::getSpecularComponent() const
{
    return _specular;
}