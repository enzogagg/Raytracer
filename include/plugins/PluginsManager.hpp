/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** PluginsManager
*/

/**
 * @file PluginsManager.hpp
 * @brief PluginsManager class header file.
 * @details This file contains the definition of the PluginsManager class,
 *      which is used to manage plugins in the raytracer project and load the .so.
 * @note The PluginsManager class is responsible for loading and managing
 *     plugins that extend the functionality of the raytracer.
 */
#pragma once

#include "Exception.hpp"
#include "PluginsFactory.hpp"
#include "PluginsHandle.hpp"
#include "Define.hpp"

/**
 * @class PluginsManager
 * @brief A class to manage plugins in the raytracer project.
 */
class PluginsManager {
    public:

        /**
         * @brief Load the plugins from the specified path.
         * @param path The path to the directory containing the plugins.
         */
        void loadPlugins(const std::string &path);

        /**
         * @brief Get a symbol from the plugin handle.
         * @param symbol The name of the symbol to retrieve.
         * @return A pointer to the symbol.
         */
        template<typename T>
        T getSymbol(const std::string &symbol)
        {
            auto raw = _plugins.back().getSymbol<T>(symbol);
            if (!raw)
                throw PluginsException("Failed to load symbol: " + symbol);
            return raw;
        }

        /**
         * @brief Register a factory for creating IPrimitive objects.
         * @param type The type of the primitive ( e.g., "sphere", "cube").
         * @param factory The factory function to create IPrimitive objects.
         */
        static void registerPrimitiveFactory(const std::string &type, PrimitivesFactory factory);

        /**
         * @brief Register a factory for creating ILight objects.
         * @param type The type of the light (e.g., "point", "directional").
         * @param factory The factory function to create ILight objects.
         */
        static void registerLightFactory(const std::string &type, LightsFactory factory);

        /**
         * @brief Create a primitive object based on the specified name and settings.
         * @param name The name of the primitive type.
         * @param setting The settings for the primitive.
         * @return A shared pointer to the created IPrimitive object.
         */
        static std::shared_ptr<IPrimitive> createPrimitive(const std::string &name, const libconfig::Setting &setting);

        /**
         * @brief Create a light object based on the specified name and settings.
         * @param name The name of the light type.
         * @param setting The settings for the light.
         * @return A shared pointer to the created ILight object.
         */
        static std::shared_ptr<ILight> createLight(const std::string &name, const libconfig::Setting &setting);

        /**
         * @brief Unergister all factory for creating IPrimitive objects and Ilight objects.
         */
        static void unregisterAllFactories();

    private:
        static inline std::map<std::string, PrimitivesFactory> _primitiveFactories;
        static inline std::map<std::string, LightsFactory> _lightFactories;

        static inline std::vector <PluginsHandle> _plugins;
};
