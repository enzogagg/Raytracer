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
 * @note The Camera class is used to define the camera's position,
 *      direction, and field of view in the 3D scene.
 */
#include "Camera.hpp"

/**
 * @brief Constructor for the Camera class.
 * @param position The position of the camera in 3D space.
 * @param rotation The rotation the camera is facing.
 * @param fov The field of view of the camera.
 * @param width The width of the camera's viewport.
 * @param height The height of the camera's viewport.
 */
Camera::Camera(const Math::Vector &position, const Math::Vector &rotation, double fov, int width, int height)
    : _fov(fov), _width(width), _height(height)
{
    _position.setX(position.getX());
    _position.setY(position.getY());
    _position.setZ(position.getZ());

    if (rotation != Math::Vector()) {
        rotate(rotation.getX(), "X");
        rotate(rotation.getY(), "Y");
        rotate(rotation.getZ(), "Z");
    }

    double aspect_ratio = static_cast<double>(_width) / _height;
    double viewport_height = 2.0 * tan(_fov / 2.0);
    double viewport_width = aspect_ratio * viewport_height;
    double d = 15.0;

    Math::Vector horizontal(viewport_width, 0, 0);
    Math::Vector vertical(0, viewport_height, 0);
    Math::Point lower_left = _position
                            - horizontal / 2
                            - vertical / 2
                            + Math::Vector(0, 0, d);
    _screen = Screen(
        lower_left,
        horizontal,
        vertical
    );
    return;
}

/**
 * @brief Get the position of the camera.
 * @return The position of the camera in 3D space.
 */
const Math::Point &Camera::getPosition() const
{
    return _position;
}

/**
 * @brief Get the field of view of the camera.
 * @return The field of view of the camera in degrees.
 */
double Camera::getFov() const
{
    return _fov;
}

/**
 * @brief Get the width of the camera's viewport.
 * @return The width of the camera's viewport.
 */
int Camera::getWidth() const
{
    return _width;
}

/**
 * @brief Get the height of the camera's viewport.
 * @return The height of the camera's viewport.
 */
int Camera::getHeight() const
{
    return _height;
}

/**
 * @brief Set the attribute of a ray
 * @param origin the origin of the ray
 * @param direction the direction of the ray
 * @return The height of the camera
 */
void Camera::setRay(double x, double y)
{
    Math::Point point = _screen.pointAt(x, y);
    _ray.setOrigin(_position);
    _ray.setDirection(point - _position);
}

/**
 * @brief Get the current ray send by the camera
 * @return a copy of the pointer to the ray
 */
Ray Camera::getRay() const
{
    Math::Vector direction = _ray.getDirection();
    Math::Point origin = _ray.getOrigin();
    return Ray(origin, direction);
}

/**
 * @brief Set the position of the camera.
 * @param position The new position of the camera in 3D space.
 */
void Camera::setPosition(const Math::Point &position)
{
    _position = position;
}

/**
 * @brief Translate the camera base on a vector
 * @param translation the vector that define the translation
 */
void Camera::translate(Math::Vector translation)
{
    _position += translation;
    _screen.translate(translation);
}

void Camera::rotate(double angle, std::string axis)
{
    if (angle == 0.0)
        return;
    double radiant = angle * M_PI / 180;
    const unsigned int X = 4;
    const unsigned int Y = 1;
    Math::Matrix<X, Y> matrix_origin(_position.pointToMatrix());

    if (axis == "X") { // Rotation around the X axis
        double rot_matrix[X][X] = {
            {1, 0, 0, 0},
            {0, std::cos(radiant), -std::sin(radiant), 0},
            {0, std::sin(radiant), std::cos(radiant), 0},
            {0, 0, 0, 1}
        };
        Math::Matrix<X, X> rot(rot_matrix);
        Math::Matrix<X, Y>new_origin = rot * matrix_origin;

        _position.setX(new_origin(0, 0));
        _position.setY(new_origin(1, 0));
        _position.setZ(new_origin(2, 0));

    } else if (axis == "Y") { // Rotation around the Y axis
        double rot_matrix[X][X] = {
            {std::cos(radiant), 0, std::sin(radiant), 0},
            {0, 1, 0, 0},
            {-std::sin(radiant), 0, std::cos(radiant), 0},
            {0, 0, 0, 1}
        };
        Math::Matrix<X, X> rot(rot_matrix);
        Math::Matrix<X, Y>new_origin = rot * matrix_origin;

        _position.setX(new_origin(0, 0));
        _position.setY(new_origin(1, 0));
        _position.setZ(new_origin(2, 0));

    } else if (axis == "Z") { // Rotation around the Z axis
        double rot_matrix[X][X] = {
            {std::cos(radiant), -std::sin(radiant), 0, 0},
            {std::sin(radiant), std::cos(radiant), 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };
        Math::Matrix<X, X> rot(rot_matrix);
        Math::Matrix<X, Y>new_origin = rot * matrix_origin;

        _position.setX(new_origin(0, 0));
        _position.setY(new_origin(1, 0));
        _position.setZ(new_origin(2, 0));
    }
    _screen.rotate(angle, axis);
}

void Camera::shear(double strength)
{
    const unsigned int X = 1;
    const unsigned int Y = 2;
    Math::Matrix<X, Y> ori(_position.shearToMatrix());
    double shearMatrix[Y][Y] = {
        {1, strength},
        {0, 1}
    };
    Math::Matrix<Y, Y> rot(shearMatrix);
    Math::Matrix<X, Y>new_origin = ori * rot;
    _position = Math::Point(
        new_origin(0, 0),
        new_origin(0, 1),
        _position.getZ()
    );
    _screen.shear(strength);
}
