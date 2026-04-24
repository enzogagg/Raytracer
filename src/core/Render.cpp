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
    return;
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
 * @brief Function to compute the render columns.
 * @param pixelsRender The vector to store the rendered pixels.
 * @param start The starting index of the range.
 * @param end The ending index of the range.
 * @note This function computes the render columns
 *   and stores the result in the provided vector.
 */
void Render::computeRenderColumns(std::vector<Color> &pixelsRender, int start, int end)
{
    for (int y = 0; y < _height; y++) {
        for (int x = start; x < end; x++) {
            Color pixel = renderPixel(x, y, _width, _height);
            pixel *= 255;
            int index = (_height - y) * _width + (_width - x);
            if (index >= 0 && index < static_cast<int>(pixelsRender.size())) {
                pixelsRender[index] = pixel;
            }
        }
    }
    if (_progressCallback)
        _progressCallback();
}

/**
 * @brief Worker thread function for rendering.
 * @param pixelsRender The vector to store the rendered pixels.
 * @param threadId The ID of the thread.
 * @note This function is executed by each worker thread
 *      to compute the render of the scene.
 */
void Render::workerThread(std::vector<Color> &pixelsRender)
{
    while (true)
    {
        std::pair<int, int> range;

        {
            std::unique_lock<std::mutex> lock(_queueMutex);
            _queueCondition.wait(lock, [this]
                                 { return !_queue.empty() || _stopThread; });
            if (_stopThread && _queue.empty())
                return;

            range = _queue.front();
            _queue.pop();
        }
        computeRenderColumns(pixelsRender, range.first, range.second);
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
    _stopThread = false;
    {
        std::lock_guard<std::mutex> lock(_queueMutex);
        for (int startColumn = 0; startColumn < _width; startColumn += RENDER_COLOMNS_DIVISION_PIXEL)
        {
            int endColumn = std::min(startColumn + RENDER_COLOMNS_DIVISION_PIXEL, _width);
            if (startColumn >= endColumn)
                continue;
            _queue.emplace(startColumn, endColumn);
            ++_tasksRemaining;
        }
    }
    for (int i = 0; i < THREADS_NUMBER; ++i)
    {
        _threads.emplace_back([this, &pixelsRender]()
                              {
            while (true) {
                std::pair<int, int> range;
                {
                    std::unique_lock<std::mutex> lock(_queueMutex);
                    _queueCondition.wait(lock, [this] {
                        return !_queue.empty() || _stopThread;
                    });
                    if (_stopThread && _queue.empty())
                        return;
                    range = _queue.front();
                    _queue.pop();
                }
                computeRenderColumns(pixelsRender, range.first, range.second);
                _tasksRemaining.fetch_sub(1, std::memory_order_relaxed);
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
            Color pixel(0, 0, 0);
            pixel = renderPixel(x, y, fastWidth, fastHeight);
            int index = (fastHeight - y) * fastWidth + (fastWidth - x);
            if (index >= 0 && index < static_cast<int>(pixelsFastRender.size())) {
                pixel *= 255;
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
