/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** PluginsManager
*/

/**
 * @file PluginsManager.cpp
 * @brief Implementation of the PluginsManager class.
 * @details This file contains the implementation of the methods for managing
 *      plugins in the raytracer project.
 */
#include "PluginsManager.hpp"

/**
 * @brief Load the plugins from the specified path.
 * @param path The path to the directory containing the plugins.
 */
void PluginsManager::loadPlugins(const std::string &path)
{
    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
            if (entry.is_regular_file() && entry.path().extension() == ".so" &&
                entry.path().string().find(".dSYM") == std::string::npos) {
                _plugins.emplace_back(entry.path().string());

                using RegisterFunc = void(*)();
                RegisterFunc registerPlugin = _plugins.back().getSymbol<RegisterFunc>("registerPlugin");

                if (!registerPlugin)
                    throw PluginsException(entry.path().string() + ": missing or invalid registerPlugin symbol");
                registerPlugin();
            }
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Error while loading plugins: " << e.what() << std::endl;
        exit(84);
    }
}

/**
 * @brief Register a factory for creating IPrimitive objects.
 * @param type The type of the primitive (e.g., "sphere", "cube").
 * @param factory The factory function to create IPrimitive objects.
 * @note This method is used to register a factory function for creating
 */
void PluginsManager::registerPrimitiveFactory(const std::string &type, PrimitivesFactory factory)
{
    _primitiveFactories[type] = factory;
}

/**
 * @brief Register a factory for creating ILight objects.
 * @param type The type of the light (e.g., "point", "directional").
 * @param factory The factory function to create ILight objects.
 * @note This method is used to register a factory function for creating
 *      ILight objects.
 */
void PluginsManager::registerLightFactory(const std::string &type, LightsFactory factory)
{
    _lightFactories[type] = factory;
}

/**
 * @brief Create a primitive object based on the specified name and settings.
 * @param name The name of the primitive type.
 * @param setting The settings for the primitive
 * @return A shared pointer to the created IPrimitive object.
 */
std::shared_ptr<IPrimitive> PluginsManager::createPrimitive(const std::string &name, const libconfig::Setting &setting)
{
    try {
        auto it = _primitiveFactories.find(name);
        if (it != _primitiveFactories.end())
            return it->second(setting);
        throw PluginsException("Primitive type not found: " + name);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
}

/**
 * @brief Create a light object based on the specified name and settings.
 * @param name The name of the light type.
 * @param setting The settings for the light.
 * @return A shared pointer to the created ILight object.
 */
std::shared_ptr<ILight> PluginsManager::createLight(const std::string &name, const libconfig::Setting &setting)
{
    try {
        auto it = _lightFactories.find(name);
        if (it != _lightFactories.end())
            return it->second(setting);
        throw PluginsException("Light type not found: " + name);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
}

/**
 * @brief Unregister all factory for creating IPrimitive objects and ILight objects.
 * @note This method is used to unregister all factory functions for creating
 *      IPrimitive and ILight objects.
 */
void PluginsManager::unregisterAllFactories()
{
    _primitiveFactories.clear();
    _lightFactories.clear();
}
