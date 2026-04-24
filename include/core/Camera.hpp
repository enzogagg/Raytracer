/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Camera
*/

/**
 * @file Camera.cpp
 * @brief Camera class implementation.
 * @details This file contains the implementation of the Camera class,
 *        which is used to represent a camera in the raytracer project.
 * @note The Camera class is used to define the position and direction of the camera.
 *      It also provides methods to get the camera's position and direction.
 */

#pragma once

#include "Vector.hpp"
#include "Matrix.hpp"
#include "Ray.hpp"
#include "Screen.hpp"
/**
 * @class Camera
 * @brief A class to represent a camera in the raytracer project.
 * @details The Camera class contains a position and a direction vector.
 */
class Camera {
    public:
        /**
         * @brief Default constructor for Camera class.
         * Initializes the camera with a position and rotation.
         * @param position The position of the camera.
         * @param rotation The rotation of the camera.
         * @note If no parameters are provided, the camera is initialized to (0, 0, 0).
         * @note This constructor can be used to create a camera with specific position and rotation.
         */
        Camera(const Math::Vector &position = Math::Vector(), const Math::Vector &rotation = Math::Vector(),
               double fov = 90.0f, int width = 800, int height = 600);

        /**
         * @brief Get the position of the camera.
         * @return The position of the camera.
         * @note This method returns the position point of the camera.
         */
        const Math::Point &getPosition() const;

        /**
         * @brief Get the field of view of the camera.
         * @return The field of view of the camera.
         * @note This method returns the field of view of the camera in degrees.
         */
        double getFov() const;

        /**
         * @brief Get the width of the camera.
         * @return The width of the camera.
         * @note This method returns the width of the camera in pixels.
         */
        int getWidth() const;

        /**
         * @brief Get the height of the camera.
         * @return The height of the camera.
         * @note This method returns the height of the camera in pixels.
         */
        int getHeight() const;

        /**
         * @brief Set the attribute of a ray
         * @param origin the origin of the ray
         * @param direction the direction of the ray
         * @return The height of the camera
         */
        void setRay(double x, double y);

        /**
         * @brief Get the current ray send by the camera
         * @return a copy of the pointer to the ray
         */
        Ray getRay() const;

        /**
         * @brief Set the position of the camera.
         * @param position The new position of the camera.
         * @note This method sets the position vector of the camera.
         */
        void setPosition(const Math::Point &position);

        /**
         * @brief Translate the camera base on a vector
         * @param translation the vector that define the translation
         */
        void translate(Math::Vector translation);

        void rotate(double angle, std::string axis);

        void shear(double strength);

    private:
        Math::Point _position;
        Math::Vector _rotation;
        Ray _ray;
        Screen _screen;
        double _fov;
        int _width;
        int _height;
};
