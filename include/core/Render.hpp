/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Render
*/

/**
 * @file Render.hpp
 * @brief Render class header file.
 * @details This file contains the definition of the Render class,
 *    which is used to render the scene in the raytracer project.
 * @note The Render class is responsible for rendering the scene
 *   and generating the final image.
 * @note The Render class calculates the color of each pixel in the image
 */
#pragma once

#include "Color.hpp"
#include "Define.hpp"
#include "IPrimitive.hpp"
#include "PluginsManager.hpp"
#include "Scene.hpp"

/**
 * @class Render
 * @brief A class to render the scene in the raytracer project.
 */
class Render {
    public:
        /**
         * @brief Default constructor for Render class.
         * Initializes the render with default settings.
         * @param width The width of the render.
         * @param height The height of the render.
         * @note This constructor can be used to create a render with default values.
         */
        Render(int width, int height, Scene &scene);

        /**
         * @brief Destructor for Render class.
         * Cleans up resources used by the render.
         * @note This destructor is called when the render object is destroyed.
         */
        ~Render();

        /**
         * @brief Compute the render of the scene.
         * @param pixelsRender The vector to store the rendered pixels.
         * @note This function computes the render of the scene
         *   and stores the result in the provided vector.
         */
        void computeRender(std::vector<Color> &pixelsRender);

        /**
         * @brief Compute the fast render of the scene.
         * @param pixelsFastRender The vector to store the fast rendered pixels.
         * @note This function computes the fast render of the scene
         *   and stores the result in the provided vector.
         */
        void computeFastRender(std::vector<Color> &pixelsFastRender);

        /**
         * @brief Set the progress callback function.
         * @param callback The callback function to be called on progress.
         * @note This function sets the callback function to be called
         *   when the rendering progress is updated.
         */
        void setProgressCallback(const std::function<void()> &callback);

        /**
         * @brief Compute the color of the pixel based on the ray tracing
         * @param x The x coordinate of the pixel.
         * @param y The y coordinate of the pixel.
         * @param maxWidth The maximum width of the render.
         * @param maxHeight The maximum height of the render.
         *
         * @note the width parameters and the height one are not the same depending on the mode
         * @note the fast render will have a smallest size of screen compare to the normal render
         */
        Color renderPixel(int x, int y, int maxWidth, int maxHeight);

        Color ComputeSpecularLight(Math::Vector &lightSource,
            Math::Vector normal, const Camera &cam, const std::shared_ptr<ILight> &light,
            float specularIntensity);

        Color ComputeDiffuseLights(const std::shared_ptr<ILight> &light,
            float diffuseStrength);

        Color ComputePixelColor(std::shared_ptr<IPrimitive> closest_object, const Camera& cam,
            const Ray& ray, int ao);

        Math::Vector randomHemisphereDirection(const Math::Vector& normal);

        float AmbiantOcclusion(std::shared_ptr<IPrimitive> closest_object, Ray &ray);

        /**
         * @brief Check if a shape is in the shadow of another shape
         * @param hit_point The point hit by the current ray in the closest shape of the current one
         * @param closest_object a pointer to the closest shape of the current one
         * @return true if it is, false if not
         */
        bool isInShadowOfShape(Math::Point &hit_point, std::shared_ptr<IPrimitive> closest_object,
            Math::Vector &lightSource);

        /**
         * @brief Calculate the reflection of a ray based on the normal vector
         * @param incident The incident vector (the direction of the incoming ray).
         * @param normal The normal vector at the point of intersection.
         * @return The reflected vector.
         */
        Math::Vector reflect(Math::Vector incident, Math::Vector normal);

        /**
         * @brief Function to handle reflection rendering.
         * @param closest_object The closest object to the ray.
         * @param ray The ray to be rendered.
         * @param cam The camera used for rendering.
         * @param depthReflection The depth of reflection.
         * @return The color of the pixel after reflection rendering.
         * @note This function computes the reflection of the ray
         *   and returns the color of the pixel.
         */
        Color renderReflection(std::shared_ptr<IPrimitive> closest_object,
            const Ray &ray, Camera &cam, int depthReflection);

        Color renderRefraction(std::shared_ptr<IPrimitive> closest_object,
            const Ray &ray, Camera &cam, int depthReflection);

        /**
         * @brief Function to send a ray for rendering.
         * @param ray The ray to be sent.
         * @param pixel The color of the pixel.
         * @param cam The camera used for rendering.
         * @param depthReflexion The depth of reflection.
         * @param closest_object The closest object to the ray.
         * @note This function sends the ray for rendering
         *  and computes the color of the pixel.
         */
        void sendRay(Ray &ray, Color &pixel, Camera &cam,
            int depthReflexion, std::shared_ptr<IPrimitive> closest_object);

        /**
         * @brief Function to compute the adaptive sampling of a pixel.
         * @param x The x coordinate of the pixel.
         * @param y The y coordinate of the pixel.
         * @param x1 The x coordinate of the pixel in the image.
         * @param y1 The y coordinate of the pixel in the image.
         * @param maxWidth The maximum width of the image.
         * @param maxHeight The maximum height of the image.
         * @param depth The depth of the pixel.
         * @note This function computes the adaptive sampling of a pixel
         * @return The color of the pixel after adaptive sampling.
         */
        Color adaptiveSample(double x, double y, double x1, double y1,
            int maxWidth, int maxHeight, int depth);

    private:

        /**
         * @brief Worker thread function to process a range of pixels.
         * @param pixelsRender The vector to store the rendered pixels.
         * @param start The starting index of the range.
         * @param end The ending index of the range.
         * @note This function is executed by each worker thread
         *   to process a specific range of pixels in parallel.
         */
        void workerThread(std::vector<Color> &pixelsRender);

        /**
         * @brief Function to compute the render columns.
         * @param pixelsRender The vector to store the rendered pixels.
         * @param start The starting index of the range.
         * @param end The ending index of the range.
         * @note This function computes the render columns
         *   and stores the result in the provided vector.
         */
        void computeRenderColumns(std::vector<Color> &pixelsRender, int start, int end);

        int _width;
        int _height;

        bool _stopThread = false;

        std::atomic<int> _tasksRemaining{0};

        std::vector<std::thread> _threads;

        std::mutex _queueMutex;
        std::mutex renderMutex;

        std::condition_variable _queueCondition;
        std::queue<std::pair<int, int>> _queue;

        std::function<void()> _progressCallback;

        Scene &_scene;
};
