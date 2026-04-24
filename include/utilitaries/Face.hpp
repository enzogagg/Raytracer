/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Face
*/

/**
 * @file Face.cpp
 * @brief Face class implementation.
 * @details This file contains the implementation of the Face class,
 *      which is a plugin for the raytracer project.
 * @note The Face class represents a Face in 3D space.
 */
#pragma once

#include "PluginsManager.hpp"
#include "IPrimitive.hpp"
#include "Point.hpp"
#include "AMaterial.hpp"

/**
 * @class Face
 * @brief A class to represent a Face in 3D space.
 */
class Face : public IPrimitive {
    public:

        /**
         * @brief Constructor for the Face class.
         * @param axis The axis of the Face (x, y, or z).
         * @param v0 The position of the first vertex
         * @param v1 The position of the second vertex
         * @param v2 The position of the third vertex
         * @param color The color of the Face.
         */
        Face(Math::Point v0, Math::Point v1, Math::Point v2, const Color &color);

        /**
         * @brief Destructor for the Face class.
         * @note This destructor is virtual to ensure proper cleanup of derived classes.
         */
        ~Face() override = default;

        /**
         * @brief Get the type of the Face.
         * @return The type of the Face as a string.
         */
        const std::string &getType() const override;

        /**
         * @brief Check if a ray intersects with the Face.
         * @param ray The ray to check for intersection.
         * @return True if the ray intersects with the Face, false otherwise.
         */
        bool intersect(const Ray &ray) const override;

        /**
         * @brief This function does exactly what you think it does
         * @param ray The ray to check for intersection.
         * @return the intersection point between a Ray and a shape
         */
        Math::Point getIntersection(const Ray &ray) const override;

        /**
         * @brief Create a normal vector to the shape
         * @param point origin of the normal vector
         * @return normal vector to the shape
         */
        Math::Vector normal_at(const Math::Point &point) const override;

        /**
         * @brief Get the color of the Face.
         * @return The color of the Face.
         */
        Color getColor() const override;

        /**
         * @brief Get the material of the primitive shape.
         * @return The material of the shape.
         */
        std::shared_ptr<AMaterial> getMaterial() const override;

    private:
        std::string _axis;
        Math::Point _v0, _v1, _v2;
        Color _color;
        Math::Vector _normal;
        std::shared_ptr<AMaterial> _material;
};
