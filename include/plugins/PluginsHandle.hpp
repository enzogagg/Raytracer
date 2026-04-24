/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** PluginsHandle
*/

/**
 * @file PluginsHandle.hpp
 * @brief Header file for the PluginsHandle class.
 * @details This file contains the definition of the PluginsHandle class,
 *      which is used to manage plugins in the raytracer project.
 * @note The PluginsHandle class is responsible for loading and managing
 *      plugins that extend the functionality of the raytracer.
 */
#pragma once

#include "Define.hpp"

/**
 * @class PluginsHandle
 * @brief A class to manage plugins in the raytracer project.
 */
class PluginsHandle {
    public:
        /**
         * @brief Constructor for PluginsHandle.
         * @param path The path to the plugin file (.so).
         */
        explicit PluginsHandle(const std::string &path);

        /**
         * @brief Destructor for PluginsHandle.
         * @note Ensures the plugin handle is properly closed.
         */
        ~PluginsHandle();

        /**
         * @brief Deleted copy constructor for the PluginsHandle class.
         * @param other The PluginsHandle object to copy from.
         */
        PluginsHandle(const PluginsHandle &) = delete;

        /**
         * @brief Deleted copy assignment operator for the PluginsHandle class.
         * @param other The PluginsHandle object to copy from.
         */
        PluginsHandle &operator=(const PluginsHandle &) = delete;

        /**
         * @brief Move constructor for PluginsHandle.
         */
        PluginsHandle(PluginsHandle &&) noexcept;

        /**
         * @brief Move assignment operator for PluginsHandle.
         * @param other The PluginsHandle object to move from.
         * @return A reference to this object.
         */
        PluginsHandle &operator=(PluginsHandle &&) noexcept;

        /**
         * @brief Get a symbol from the loaded plugin.
         * @tparam T The type of the symbol.
         * @param symbolName The name of the symbol to retrieve.
         * @return A pointer to the symbol.
         * @throws std::runtime_error if the symbol cannot be found.
         */
        template <typename T>
        T getSymbol(const std::string &symbolName)
        {
            T symbol = reinterpret_cast<T>(dlsym(_handle.get(), symbolName.c_str()));
            if (!symbol) {
                throw std::runtime_error("Failed to load symbol: " + symbolName);
            }
            return symbol;
        }

    private:

        /**
         * @brief Close the plugin handle.
         * @param handle The handle to close.
         */
        static void closeHandle(void* handle);
        std::unique_ptr<void, int(*)(void*)> _handle{nullptr, dlclose};
};