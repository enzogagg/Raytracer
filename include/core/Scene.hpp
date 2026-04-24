/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Scene
*/

/**
 * @file Scene.hpp
 * @brief Scene class header file.
 * @details This file contains the definition of the Scene class,
 *      which is used to manage the scene in the raytracer project.
 * @note The Scene class is responsible for managing the objects in the scene.
 *     It stores the objects all the entities in the scene like lights, cameras, primitives, etc.
 */
#pragma once

#include "Camera.hpp"
#include "Vector.hpp"
#include "ILight.hpp"
#include "IPrimitive.hpp"
#include "Define.hpp"

/**
 * @class Scene
 * @brief A class to represent a scene in the raytracer project.
 */
class Scene {
    public:
        /**
         * @brief Default constructor for Scene class.
         * Initializes the scene with a camera, lights, and primitives.
         * @note This constructor can be used to create a scene with default values.
         */
        Scene();

        /**
         * @brief Destructor for Scene class.
         * Cleans up the resources used by the scene.
         */
        ~Scene();

        /**
         * @brief Add a camera to the scene.
         * @param camera The camera to add to the scene.
         */
        void addCamera(const Camera &camera);

        /**
         * @brief Add a light to the scene.
         * @param light The light to add to the scene.
         */
        void addLight(const std::shared_ptr<ILight> &light);

        /**
         * @brief Add a primitive to the scene.
         * @param primitive The primitive to add to the scene.
         */
        void addPrimitive(const std::shared_ptr<IPrimitive> &primitive);

        /**
         * @brief Get the camera of the scene.
         * @return The camera of the scene.
         */
        Camera getCamera() const;

        /**
         * @brief Get the camera of the scene.
         * @return The camera of the scene.
         */
        Camera& getModifableCamera();

        /**
         * @brief Get the vector of primitives
         */
        const std::vector<std::shared_ptr<IPrimitive>>& getPrimitives() const;

        /**
         * @brief Get the vector of lights
         */
        const std::vector<std::shared_ptr<ILight>>& getLights() const;

        /**
         * @brief Get the diffuse value of the scene.
         * @return The diffuse value of the scene.
         */
        double getDiffuse() const;

        /**
         * @brief Set the diffuse value of the scene.
         * @param diffuse The diffuse value to set.
         */
        void setDiffuse(double diffuse);

        /**
         * @brief Call the translate function of the camera
         * @param translation Vector that define the translation
         */
        void setTranslateScene(Math::Vector translation);

        void setRotate(double angle, std::string axis);

        void setShear(double strength);

    private:
        Camera _camera;
        std::vector<std::shared_ptr <ILight>> _lights;
        std::vector<std::shared_ptr <IPrimitive>> _primitives;

        double _diffuse = 0.0f;
};