/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Render
*/

/**
 * @file Render.cpp
 * @brief Render class implementation file.
 * @details This file contains the implementation of the Render class,
 *      which is used to render the scene in the raytracer project.
 */
#include "Render.hpp"

/**
 * @brief Default constructor for Render class.
 * Initializes the render with default settings.
 * @param width The width of the render.
 * @param height The height of the render.
 * @note This constructor can be used to create a render with default values.
 */
Render::Render(int width, int height, Scene &scene)
    : _width(width), _height(height), _scene(scene)
{
    _gpuRender = std::make_shared<GPURender>(width, height);
    if (_gpuRender->init()) {
        std::cout << "[Hardware Acceleration] GPU Render initialized (OpenCL)" << std::endl;
        _useGPU = true;
    }
}

/**
 * @brief Destructor for Render class.
 * Cleans up resources used by the render.
 * @note This destructor is called when the render object is destroyed.
 */
Render::~Render()
{
    {
        std::lock_guard<std::mutex> lock(_queueMutex);
        _stopThread = true;
    }
    _queueCondition.notify_all();
}

/**
 * @brief Function to compute a specific tile.
 * @param pixelsRender The vector to store the rendered pixels.
 * @param tile The tile to compute.
 */
void Render::computeTile(std::vector<Color> &pixelsRender, const Tile &tile)
{
    for (int y = tile.y; y < tile.y + tile.height; y++) {
        for (int x = tile.x; x < tile.x + tile.width; x++) {
            Color pixel = renderPixel(x, y, _width, _height);
            int index = (_height - 1 - y) * _width + x;
            if (index >= 0 && index < static_cast<int>(pixelsRender.size())) {
                pixelsRender[index] = pixel;
            }
        }
    }
}

/**
 * @brief Worker thread function for rendering.
 * @param pixelsRender The vector to store the rendered pixels.
 */
void Render::workerThread(std::vector<Color> &pixelsRender)
{
    while (true)
    {
        Tile tile;

        {
            std::unique_lock<std::mutex> lock(_queueMutex);
            _queueCondition.wait(lock, [this]
                                 { return !_queue.empty() || _stopThread; });
            if (_stopThread && _queue.empty())
                return;

            tile = _queue.front();
            _queue.pop();
        }
        computeTile(pixelsRender, tile);
    }
}

/**
 * @brief Compute the render of the scene.
 * @param pixelsRender The vector to store the rendered pixels.
 * @note This function computes the render of the scene
 *      and stores the result in the provided vector.
 */
void Render::computeRender(std::vector<Color> &pixelsRender)
{
    if (_useGPU) {
        _gpuRender->render(_scene, pixelsRender);
        if (_progressCallback)
            _progressCallback();
        return;
    }
    _stopThread = false;
    {
        std::lock_guard<std::mutex> lock(_queueMutex);
        for (int y = 0; y < _height; y += TILE_SIZE)
        {
            for (int x = 0; x < _width; x += TILE_SIZE)
            {
                Tile tile;
                tile.x = x;
                tile.y = y;
                tile.width = std::min(TILE_SIZE, _width - x);
                tile.height = std::min(TILE_SIZE, _height - y);
                _queue.push(tile);
                ++_tasksRemaining;
            }
        }
    }
    for (int i = 0; i < THREADS_NUMBER; ++i)
    {
        _threads.emplace_back([this, &pixelsRender]()
                              {
            while (true) {
                Tile tile;
                {
                    std::unique_lock<std::mutex> lock(_queueMutex);
                    _queueCondition.wait(lock, [this] {
                        return !_queue.empty() || _stopThread;
                    });
                    if (_stopThread && _queue.empty())
                        return;
                    tile = _queue.front();
                    _queue.pop();
                }
                computeTile(pixelsRender, tile);
                _tasksRemaining.fetch_sub(1, std::memory_order_relaxed);
                if (_progressCallback)
                    _progressCallback();
            } });
    }
    _queueCondition.notify_all();
    while (_tasksRemaining > 0)
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    {
        std::lock_guard<std::mutex> lock(_queueMutex);
        _stopThread = true;
    }
    _queueCondition.notify_all();
    for (auto &thread : _threads)
    {
        if (thread.joinable())
            thread.join();
    }
}

/**
 * @brief Compute the fast render of the scene.
 * @param pixelsFastRender The vector to store the fast rendered pixels.
 * @note This function computes the fast render of the scene
 *      and stores the result in the provided vector.
 */
void Render::computeFastRender(std::vector<Color> &pixelsFastRender)
{
    int fastWidth = _width * FAST_RENDER_RATIO;
    int fastHeight = _height * FAST_RENDER_RATIO;

    std::fill(pixelsFastRender.begin(), pixelsFastRender.end(), Color(0, 0, 0));

    for (int y = 0; y < fastHeight; ++y) {
        for (int x = 0; x < fastWidth; ++x) {
            Color pixel = renderPixel(x, y, fastWidth, fastHeight);
            int index = (fastHeight - 1 - y) * fastWidth + x;
            if (index >= 0 && index < static_cast<int>(pixelsFastRender.size())) {
                pixelsFastRender[index] = pixel;
            }
        }
    }
    if (_progressCallback)
        _progressCallback();
}

/**
 * @brief Set the progress callback function.
 * @param callback The callback function to set.
 * @note This function sets the callback function to be called
 */
void Render::setProgressCallback(const std::function<void()> &callback)
{
    _progressCallback = callback;
}
