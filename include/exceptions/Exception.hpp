/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Exception
*/

/**
 * @file Exception.hpp
 * @brief Exception class for the raytracer project.
 * @details This class is used to handle exceptions in the raytracer project.
 * @note This class is used to handle exceptions in the raytracer project.
 */
#pragma once

#include "Define.hpp"

/**
 * @class RaytracerException
 * @brief Exception class for the raytracer project.
 * @details This class is used to handle exceptions in the raytracer project.
 */
class RaytracerException : public std::runtime_error {
    public:

        /**
         * @brief Handle the exception in raytracer project.
         */
        explicit RaytracerException(const std::string &message);
};

/**
 * @class PlugInException
 * @brief Exception class for the raytracer project.
 * @details This class is used to handle exceptions in the plugin system of the raytracer project.
 */
class PluginsException : public std::runtime_error {
    public:

        /**
         * @brief Handle the exception in plugin.
         */
        explicit PluginsException(const std::string &message);
};

/**
 * @class SceneException
 * @brief Exception class for the raytracer project.
 * @details This class is used to handle exceptions in the scene system of the raytracer project.
 */
class SceneException : public std::runtime_error {
    public:

        /**
         * @brief Handle the exception in scene.
         */
        explicit SceneException(const std::string &message);
};

/**
 * @class RenderException
 * @brief Exception class for the raytracer project.
 * @details This class is used to handle exceptions in the render system of the raytracer project.
 */
class RenderException : public std::runtime_error {
    public:

        /**
         * @brief Handle the exception in render.
         */
        explicit RenderException(const std::string &message);
};

/**
 * @class ImageException
 * @brief Exception class for the raytracer project.
 * @details This class is used to handle exceptions in the image system of the raytracer project.
 */
class ImageException : public std::runtime_error {
    public:

        /**
         * @brief Handle the exception in image.
         */
        explicit ImageException(const std::string &message);
};
