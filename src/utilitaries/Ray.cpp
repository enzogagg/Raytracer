/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Ray
*/

/**
 * @file Ray.hpp
 * @brief Ray class header file.
 * @details This file contains the definition of the Ray class,
 *      which is used for ray representation in the raytracer project.
 * @note The Ray class is used to represent rays in 3D space.
 */
#include "Ray.hpp"

/**
 * @brief Default constructor for Ray class.
 * Initializes the ray with a position and direction.
 * @param origin The origin of the ray.
 * @param direction The direction of the ray.
 * @note If no parameters are provided, the ray is initialized to (0, 0, 0).
 * @note This constructor can be used to create a ray with specific origin and direction.
 */
Ray::Ray(const Math::Point &origin, const Math::Vector &direction)
    : _origin(origin), _direction(direction)
{
    
}

/**
 * @brief Get the origin of the ray.
 * @return The origin of the ray.
 */
const Math::Point &Ray::getOrigin() const
{
    return _origin;    
}

/**
 * @brief Get the direction of the ray.
 * @return The direction of the ray.
 */
const Math::Vector &Ray::getDirection() const
{
    return _direction;
}

/**
 * @brief Set the origin of the ray.
 * @param origin origin to be set
 */
void Ray::setOrigin(const Math::Point &origin)
{
    _origin = origin;
}

/**
 * @brief Set the direction of the ray.
 * @param direction direction of the ray.
 */
void Ray::setDirection(const Math::Vector &direction)
{
    _direction = direction;
}
