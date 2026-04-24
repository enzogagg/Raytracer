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
#include "Core.hpp"

/**
 * @brief Default constructor for Core class.
 * Initializes the core of the raytracer project.
 * @note This constructor can be used to create a core with default values.
 */
Core::Core()
{
    _translate = std::make_unique<Translation>();
    _rotation = std::make_unique<Rotation>();
    _shear = std::make_unique<Shear>();
    return;
}

/**
 * @brief Destructor for Core class.
 * Cleans up the resources used by the core.
 */
Core::~Core()
{
    {
        std::lock_guard<std::mutex> lock(_renderMutex);
        _needRenderUpdate = true;
    }
    _renderCondition.notify_one();
    if (_renderThread.joinable()) {
        _renderCondition.notify_one();
        _renderThread.join();
    }
    if (_guiThread.joinable()) {
        _guiThread.join();
    }
    _pluginsManager.unregisterAllFactories();
}

/**
 * @brief Initialize the core of the raytracer project.
 * @param filename The name of the file to load the scene from.
 * @note This function is used to initialize the core of the raytracer project.
 */
void Core::init(const std::string &filename)
{
    std::string pluginPath = "./plugins";

    _scenePath = std::filesystem::absolute(filename).string();
    _eventKey = -1;
    _Ctrl_pressed = false;
    std::fill(_pixelsRender.begin(), _pixelsRender.end(), Color(0, 0, 0));
    std::fill(_pixelsFastRender.begin(), _pixelsFastRender.end(), Color(0, 0, 0));
    _pluginsManager.loadPlugins(pluginPath);
    _scene = SceneLoader::parseSceneFile(filename);
    _pixelsRender.resize(_scene.getCamera().getWidth() * _scene.getCamera().getHeight());
    _pixelsFastRender.resize(_scene.getCamera().getWidth() * _scene.getCamera().getHeight());
    _render = std::make_shared<Render>(_scene.getCamera().getWidth(), _scene.getCamera().getHeight(), _scene);
    _needRenderUpdate = true;
    _lastModificationTime = std::filesystem::last_write_time(_scenePath);
    setHandleTranslation();
    setHandleRotation();
    createGuiThread();
    {
        std::unique_lock<std::mutex> lock(_guiReadyMutex);
        _guiReadyCond.wait(lock, [this]() { return _guiReady; });
    }
    createRenderThread();
}

/**
 * @brief Create the GUI thread.
 * @note This function is used to create the GUI thread.
 */
void Core::createGuiThread()
{
    _guiThread = std::thread([this]() {
        auto gui = std::make_shared<Gui>(_scene.getCamera().getWidth(), _scene.getCamera().getHeight());
        {
            std::lock_guard<std::mutex> lock(_guiMutex);
            _gui = gui;
        }
        {
            std::lock_guard<std::mutex> lock(_guiReadyMutex);
            _guiReady = true;
            _guiReadyCond.notify_one();
        }
        gui->renderScene(_eventKey);
    });
}

/**
 * @brief Create the render thread.
 * @note This function is used to create the render thread.
 */
void Core::createRenderThread()
{
    _render->setProgressCallback([this]() {
        std::lock_guard<std::mutex> lock(_guiMutex);
        if (_gui && _gui->isOpen())
            _gui->updateScene(_pixelsRender, _pixelsFastRender);
    });

    _renderThread = std::thread([this]() {
        while (true) {
            {
                std::lock_guard<std::mutex> guiLock(_guiMutex);
                if (!_gui || !_gui->isOpen())
                    break;
            }
            std::unique_lock<std::mutex> renderLock(_renderMutex);
            _renderCondition.wait(renderLock, [this]() { return _needRenderUpdate.load(); });

            if (!_needRenderUpdate)
                continue;
            _needRenderUpdate = false;
            _render->computeFastRender(_pixelsFastRender);
            _render->computeRender(_pixelsRender);
        }
    });
}

void Core::setCtrl()
{
    _Ctrl_pressed = !_Ctrl_pressed;
}

/**
 * @brief set the pointer to function for the translation
 */
void Core::setHandleTranslation()
{
    _handle_translation[sf::Keyboard::Up] = &Translation::translateUp;
    _handle_translation[sf::Keyboard::Down] = &Translation::translateDown;
    _handle_translation[sf::Keyboard::Left] = &Translation::translateLeft;
    _handle_translation[sf::Keyboard::Right] = &Translation::translateRight;
    _handle_translation[sf::Keyboard::I] = &Translation::translateIn;
    _handle_translation[sf::Keyboard::O] = &Translation::translateOut;
}

/**
 * @brief set the pointer to function for the translation
 */
void Core::setHandleRotation()
{
    _handle_rotation[sf::Keyboard::X] = &Rotation::RotateX;
    _handle_rotation[sf::Keyboard::Y] = &Rotation::RotateY;
    _handle_rotation[sf::Keyboard::Z] = &Rotation::RotateZ;
}

/**
 * @brief Notify the render thread that a render update is needed.
 * @note This function is used to notify the render thread that a render update is needed.
 */
void Core::notifyRenderThread()
{
    {
        std::lock_guard<std::mutex> lock(_renderMutex);
        _needRenderUpdate = true;
    }
    _renderCondition.notify_one();
}

/**
 * @brief Loop the core of the raytracer project.
 * @note This function is used to loop the core of the raytracer project.
 */
void Core::loop()
{
    while (true) {
        {
            std::lock_guard<std::mutex> lock(_guiMutex);
            if (!_gui || !_gui->isOpen())
                break;
        }
        checkSceneFile();
        if (_eventKey != -1 && _eventKey != 40) {
            for (auto const &[key, function] : _handle_translation) {
                if (key == _eventKey) {
                    (_translate.get()->*function)(_scene);
                    notifyRenderThread();
                    break;
                }
            }
            for (auto const &[key, function] : _handle_rotation) {
                if (key == _eventKey) {
                    (_rotation.get()->*function)(_Ctrl_pressed, _scene);
                    notifyRenderThread();
                    break;
                }
            }
            if (_eventKey == sf::Keyboard::S) {
                Image image(_scene.getCamera().getWidth(), _scene.getCamera().getHeight(), _pixelsRender);
                image.save("screenshot");
                _eventKey = -1;
            }
            if (_eventKey == sf::Keyboard::LControl)
                setCtrl();
            if (_eventKey == sf::Keyboard::C) {
                _shear.get()->shear(_scene);
                notifyRenderThread();
            }
        }
    }
}
