/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** hotreload
*/

/**
 * @file hotreload.cpp
 * @brief Hot reload implementation for the raytracer project.
 * @details This file contains the implementation of the hot reload feature
 *         for the raytracer project. It allows for reloading of shared
 */
#include "Core.hpp"
#include <thread>
#include <chrono>

/**
 * @brief Reload the scene if needed.
 * @note This function is used to reload the scene if needed.
 */
void Core::reloadScene()
{
    try {
        Scene newScene = SceneLoader::parseSceneFile(_scenePath);
        _pixelsRender.resize(newScene.getCamera().getWidth() * newScene.getCamera().getHeight());
        _pixelsFastRender.resize(newScene.getCamera().getWidth() * newScene.getCamera().getHeight());
        _scene = newScene;
        _lastModificationTime = std::filesystem::last_write_time(_scenePath);
        notifyRenderThread();
    } catch (const std::exception &e) {
        std::cerr << "Error in scene parser: " << e.what() << std::endl;
    }
}

/**
 * @brief Check for changes in the scene file and reload it if modified.
 * @note Avoids accessing the scene file too soon after changes are detected.
 */
void Core::checkSceneFile()
{
    static auto lastSeenChange = std::filesystem::file_time_type::min();

    try {
        if (!std::filesystem::exists(_scenePath)) {
            std::cerr << "Scene file does not exist: " << _scenePath << std::endl;
            return;
        }

        auto currentModificationTime = std::filesystem::last_write_time(_scenePath);

        if (_lastModificationTime != currentModificationTime) {
            if (lastSeenChange != currentModificationTime) {
                lastSeenChange = currentModificationTime;
                return;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
            reloadScene();
            lastSeenChange = std::filesystem::file_time_type::min();
        }

    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
}
