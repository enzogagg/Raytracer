/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** SceneLoader
*/

/**
 * @file SceneLoader.hpp
 * @brief SceneLoader class header file
 * @details This file contains the definition of the SceneLoader class,
 *     which is used to load scenes from files in the raytracer project.
 * @note The SceneLoader class is responsible for parsing scene files
 *    and creating the corresponding objects in the scene.
 */
#pragma once

#include "PluginsManager.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Vector.hpp"
#include "Define.hpp"

/**
 * @class SceneLoader
 * @brief A class to load scenes from files in the raytracer project.
 */
class SceneLoader {
    public:

    /**
     * @brief Load a scene from a file.
     * @param filename The name of the file to load the scene from.
     * @return A pointer to the loaded scene.
     */
    static Scene parseSceneFile(const std::string &filename);

    /**
     * @brief Parse the scene file and create the camera.
     * @param file The file to parse.
     * @param scene The scene object to fill.
     */
    static void parseSceneCamera(const libconfig::Setting &file, Scene &scene);

    /**
     * @brief Parse the scene file and create the primitive.
     * @param file The file to parse.
     * @param scene The scene object to fill.
     */
    static void parseScenePrimitive(const libconfig::Setting &file, Scene &scene);

    /**
     * @brief Parse the scene file and create the light.
     * @param file The file to parse.
     * @param scene The scene object to fill.
     */
    static void parseSceneLight(const libconfig::Setting &file, Scene &scene);

};
