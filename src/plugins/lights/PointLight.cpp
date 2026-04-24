/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** PointLight
*/

/**
 * @file PointLight.cpp
 * @brief PointLight class implementation.
 * @details This file contains the implementation of the PointLight class,
 *      which is a plugin for the raytracer project.
 * @note The PointLight class represents a point light source in the scene.
 */
#include "PointLight.hpp"

/**
 * @brief Constructor for the PointLight class.
 * @param position The position of the light source.
 * @param intensity The intensity of the light source.
 * @param color The color of the light source.
 */
PointLight::PointLight(const Math::Vector &position, const Color &color, float intensity)
    : _intensity(intensity), _color(color), 
      _ambient(color * 0.1), _diffuse(color * 0.7), _specular(Color(1, 1, 1))
{
    _position.setX(position.getX());
    _position.setY(position.getY());
    _position.setZ(position.getZ());
}

/**
 * @brief Get the type of the light source.
 * @return The type of the light source.
 */
const std::string &PointLight::getType() const
{
    static std::string type("point");
    return type;
}

/**
 * @brief Get the position of the light source.
 * @return The position of the light source.
 */
const Math::Point &PointLight::getPosition() const
{
    return _position;
}

/**
 * @brief Get the direction of the light source.
 * @return The color of the light source.
 */
const Math::Vector &PointLight::getDirection() const
{
    static Math::Vector noDirection(0, 0, 0);
    return noDirection;
}

/**
 * @brief Get the intensity of the light source.
 * @return The intensity of the light source.
 */
float PointLight::getIntensity() const
{
    return _intensity;
}

/**
 * @brief Get the color of the light source.
 * @return The color of the light source.
 */
const Color &PointLight::getColor() const
{
    return _color;
}

/**
 * @brief Get the ambient component of the light source.
 * @return The ambient component of the light source.
 */
const Color &PointLight::getAmbientComponent() const
{
    return _ambient;
}

/**
 * @brief Get the diffuse component of the light source.
 * @return The diffuse component of the light source.
 */
const Color &PointLight::getDiffuseComponent() const
{
    return _diffuse;
}

/**
 * @brief Get the specular component of the light source.
 * @return The specular component of the light source.
 */
const Color &PointLight::getSpecularComponent() const
{
    return _specular;
}