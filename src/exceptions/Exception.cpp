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
 */
#include "Exception.hpp"


/**
 * @brief Handle the exception
 * @param message The message to display.
 */
RaytracerException::RaytracerException(const std::string &message)
    : std::runtime_error( "Error in raytracer project: " + message)
{}

/**
 * @brief Handle the exception in plugin loader.
 * @param message The message to display.
 */
PluginsException::PluginsException(const std::string &message)
    : std::runtime_error( "Error in plugin: " + message)
{}

/**
 * @brief Handle the exception in scene parsing.
 * @param message The message to display.
 */
SceneException::SceneException(const std::string &message)
    : std::runtime_error( "Error in scene parser: " + message)
{}

/**
 * @brief Handle the exception in render scene.
 * @param message The message to display.
 */
RenderException::RenderException(const std::string &message)
    : std::runtime_error( "Error in render: " + message)
{}

/**
 * @brief Handle the exception in image generation.
 * @param message The message to display.
 */
ImageException::ImageException(const std::string &message)
    : std::runtime_error( "Error in image generation: " + message)
{}
