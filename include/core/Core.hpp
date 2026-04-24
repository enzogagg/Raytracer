/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Core
*/

/**
 * @file Core.hpp
 * @brief Core class header file.
 * @details This file contains the definition of the Core class,
 *      which is used to manage the raytracer project.
 * @note The Core class is responsible for initializing and managing
 *      the raytracer project.
 */
#pragma once

#include "Scene.hpp"
#include "SceneLoader.hpp"
#include "Gui.hpp"
#include "Render.hpp"
#include "Image.hpp"
#include "Define.hpp"
#include "Translation.hpp"
#include "Rotation.hpp"
#include "Shear.hpp"

/**
 * @class Core
 * @brief A class to manage the raytracer project.
 */
class Core {
    public:
        /**
         * @brief Default constructor for Core class.
         * Initializes the core of the raytracer project.
         */
        Core();

        /**
         * @brief Destructor for Core class.
         * Cleans up the resources used by the core.
         */
        ~Core();

        /**
         * @brief Initialize the core of the raytracer project.
         */
        void init(const std::string &filename);

        /**
         * @brief Loop the core of the raytracer project.
         * @note This function is used to loop the core of the raytracer project.
         */
        void loop();

        /**
         * @brief Create the GUI thread.
         * @note This function is used to create the GUI thread.
         */
        void createGuiThread();

        /**
         * @brief Create the render thread.
         * @note This function is used to create the render thread.
         */
        void createRenderThread();

        void setCtrl();

        /**
         * @brief set the pointer to function for the translation
         */
        void setHandleTranslation();

        /**
         * @brief set the pointer to function for the translation
         */
        void setHandleRotation();

        /**
         * @brief notify the render thread that a render update is needed
         * @note This function is used to notify the render thread that a render update is needed.
         */
        void notifyRenderThread();

        /**
         * @brief check changes in the scene file
         * @note This function is used to check changes in the scene file
         *       and reload the scene if needed.
         */
        void checkSceneFile();

        /**
         * @brief reload the scene if needed
         * @note This function is used to reload the scene if needed.
         */
        void reloadScene();

    private:
        bool _guiReady = false;

        std::string _scenePath;
        std::filesystem::file_time_type _lastModificationTime;

        Scene _scene;
        PluginsManager _pluginsManager;
        std::shared_ptr<Gui> _gui;
        std::shared_ptr<Render> _render;

        std::mutex _guiMutex;
        std::mutex _guiReadyMutex;
        std::mutex _renderMutex;

        std::condition_variable _renderCondition;
        std::condition_variable _guiReadyCond;

        std::atomic<bool> _needRenderUpdate;

        std::thread _guiThread;
        std::thread _renderThread;

        std::vector<Color> _pixelsRender;
        std::vector<Color> _pixelsFastRender;

        std::unique_ptr<Translation>_translate;
        std::unique_ptr<Rotation>_rotation;
        std::unique_ptr<Shear>_shear;
        bool _Ctrl_pressed;
        int _eventKey;
        std::map<int, void (Translation::*)(Scene&)> _handle_translation;
        std::map<int, void (Rotation::*)(bool, Scene&)> _handle_rotation;
};