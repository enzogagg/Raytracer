/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Scene
*/

/**
 * @file Scene.cpp
 * @brief Scene class implementation.
 * @details This file contains the implementation of the Scene class,
 *      which is used to manage the scene in the raytracer project.
 * @note The Scene class is responsible for managing the objects in the scene.
 *     It stores the objects all the entities in the scene like lights, cameras, primitives, etc.
 */
#include "Scene.hpp"

/**
 * @brief Default constructor for Scene class.
 * Initializes the scene with a camera, lights, and primitives.
 * @note This constructor can be used to create a scene with default values.
 */
Scene::Scene()
{
    return;
}

/**
 * @brief Destructor for Scene class.
 * Cleans up the resources used by the scene.
 */
Scene::~Scene()
{
    return;
}

/**
 * @brief Add a camera to the scene.
 * @param camera The camera to add to the scene.
 */
void Scene::addCamera(const Camera &camera)
{
    _camera = camera;
}

/**
 * @brief Add a light to the scene.
 * @param light The light to add to the scene.
 */
void Scene::addLight(const std::shared_ptr<ILight> &light)
{
    _lights.push_back(light);
}

/**
 * @brief Add a primitive to the scene.
 * @param primitive The primitive to add to the scene.
 */
void Scene::addPrimitive(const std::shared_ptr<IPrimitive> &primitive)
{
    _primitives.push_back(primitive);
}

/**
 * @brief Get the camera of the scene.
 * @return The camera of the scene.
 */
Camera Scene::getCamera() const
{
    return _camera;
}

/**
 * @brief Get the camera of the scene.
 * @return The camera of the scene.
 */
Camera& Scene::getModifableCamera()
{
    return _camera;
}

/**
 * @brief Get the vector of primitives
 * @return The vector of primitives in the scene.
 */
const std::vector<std::shared_ptr<IPrimitive>>& Scene::getPrimitives() const
{
    return _primitives;
}

/**
 * @brief Get the vector of lights
 * @return The vector of lights in the scene.
 */
const std::vector<std::shared_ptr<ILight>>& Scene::getLights() const
{
    return _lights;
}

/**
 * @brief Get the diffuse value of the scene.
 * @return The diffuse value of the scene.
 */
double Scene::getDiffuse() const
{
    return _diffuse;
}

/**
 * @brief Set the diffuse value of the scene.
 * @param diffuse The diffuse value to set.
 */
void Scene::setDiffuse(double diffuse)
{
    _diffuse = diffuse;
}

/**
 * @brief Call the translate function of the camera
 * @param translation Vector that define the translation
 */
void Scene::setTranslateScene(Math::Vector translation)
{
    _camera.translate(translation);
}


void Scene::setRotate(double angle, std::string axis)
{
    _camera.rotate(angle, axis);
}

void Scene::setShear(double strength)
{
    _camera.shear(strength);
}
