/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** PluginsFactory
*/

/**
 * @file PluginsFactory.hpp
 * @brief File that declares the factory type for the plugins
 * @note This file is part of the Raytracer project.
 */
#pragma once

#include "ILight.hpp"
#include "IPrimitive.hpp"
#include "Define.hpp"

/**
 * @brief Type definition for a factory that creates IPrimitive objects.
 * @details This using is a definition for a function that takes a libconfig::Setting object
 *    and returns a pointer to an IPrimitive object.
 * @note The function is expected to be used as a factory for creating IPrimitive objects.
 */
using PrimitivesFactory = std::function<std::shared_ptr<IPrimitive>(const libconfig::Setting &)>;
/**
 * @brief Type definition for a factory that creates ILight objects.
 * @details This using is a definition for a function that takes a libconfig::Setting object
 *   and returns a pointer to an ILight object.
 * @note The function is expected to be used as a factory for creating ILight objects.
 */
using LightsFactory = std::function<std::shared_ptr<ILight>(const libconfig::Setting &)>;
