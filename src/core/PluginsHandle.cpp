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
#include "PluginsHandle.hpp"

/**
 * @brief Constructor for PluginsHandle.
 */
PluginsHandle::PluginsHandle(const std::string &path)
{
    _handle = std::unique_ptr<void, int(*)(void*)>(
        dlopen(path.c_str(), RTLD_LAZY), dlclose);
    if (!_handle) {
        throw std::runtime_error("Failed to load plugin: " + path + ": " + dlerror());
    }
}

/**
 * @brief Destructor for PluginsHandle.
 * @note Ensures the plugin handle is properly closed.
 */
PluginsHandle::~PluginsHandle()
{
    _handle.reset();
}

/**
 * @brief Move constructor for PluginsHandle.
 * @param other The PluginsHandle object to move from.
 */
PluginsHandle::PluginsHandle(PluginsHandle &&other) noexcept
    : _handle(std::move(other._handle))
{
    other._handle = nullptr;
}

/**
 * @brief Move assignment operator for PluginsHandle.
 * @param other The PluginsHandle object to move from.
 * @return A reference to this object.
 */
PluginsHandle &PluginsHandle::operator=(PluginsHandle &&other) noexcept
{
    if (this != &other) {
        // Utilisation de reset pour libérer l'ancien handle avant d'en assigner un nouveau
        _handle.reset();
        _handle = std::move(other._handle);
    }
    return *this;
}

/**
 * @brief Close the plugin handle.
 * @param handle The handle to close.
 */
void PluginsHandle::closeHandle(void* handle)
{
    if (handle) {
        if (dlclose(handle) != 0) {
            std::cerr << "Error closing plugin handle: " << dlerror() << std::endl;
        }
    }
}
