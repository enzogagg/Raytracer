/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Sphere
*/

/**
 * @file Sphere.cpp
 * @brief Sphere class implementation.
 * @details This file contains the implementation of the Sphere class,
 *      which is a plugin for the raytracer project.
 * @note The Sphere class represents a Sphere in 3D space.
 */
#pragma once

#include "PluginsManager.hpp"
#include "IPrimitive.hpp"
#include "AMaterial.hpp"
#include "Default.hpp"
#include "Metal.hpp"
#include "Chessboard.hpp"
#include "PerlinNoise.hpp"
#include "Transparent.hpp"

/**
 * @class Sphere
 * @brief A class to represent a Sphere in 3D space.
 */
class Sphere : public IPrimitive {
    public:
        /**
         * @brief Constructor for the Sphere class.
         * @param center the center of the sphere (x, y, or z).
         * @param radius the radius of the sphere
         * @param color The color of the sphere.
         */
        Sphere(Math::Vector center, float radius, const Color &color, const std::shared_ptr<AMaterial> &mat);

        /**
         * @brief Destructor for the Sphere class.
         * @note This destructor is virtual to ensure proper cleanup of derived classes.
         */
        ~Sphere() override = default;

        /**
         * @brief Get the type of the Sphere.
         * @return The type of the Sphere as a string.
         */
        const std::string &getType() const override;

        /**
         * @brief Check if a ray intersects with the Sphere.
         * @param ray The ray to check for intersection.
         * @return True if the ray intersects with the Sphere, false otherwise.
         */
        bool intersect(const Ray &ray) const override;

        /**
         * @brief This function does exactly what you think it does
         * @param ray The ray to check for intersection.
         * @return the intersection point between a Ray and a shape
         */
        Math::Point getIntersection(const Ray &ray) const override;

        /**
         * @brief Create a normal vector to the shape
         * @param point origin of the normal vector
         * @return normal vector to the shape
         */
        Math::Vector normal_at(const Math::Point &point) const override;

        /**
         * @brief Get the color of the Sphere.
         * @return The color of the Sphere.
         */
        Color getColor() const override;

        /**
         * @brief Get the material of the primitive shape.
         * @return The material of the shape.
         */
        std::shared_ptr<AMaterial> getMaterial() const override;

    private:
        Math::Point _center;
        double _radius;
        Color _color;
        std::shared_ptr<AMaterial> _material;
};

extern "C" {

    /**
     * @brief Create a Sphere object.
     * @details This function creates a new Sphere object.
     * @param setting The settings for the Sphere object.
     * @return A pointer to the created Sphere object.
     */
    std::shared_ptr<IPrimitive> createPrimitive(const libconfig::Setting &setting)
    {
        try {
            if (!setting.exists("x") || !setting.exists("y") ||
                !setting.exists("z") || !setting.exists("radius") ||
                !setting.exists("color") || !setting.exists("material"))
                throw std::runtime_error("Missing required fields (x, y, z, radius, color, material) in Sphere settings.");
            if (!setting["color"].isGroup() || setting["material"].getType() != libconfig::Setting::TypeString)
                throw std::runtime_error("Sphere: color is not a group");
            const libconfig::Setting &colorSetting = setting["color"];

            if (!colorSetting.exists("r") || !colorSetting.exists("g") ||
                !colorSetting.exists("b") || !colorSetting["r"].isNumber() ||
                !colorSetting["g"].isNumber() || !colorSetting["b"].isNumber())
                throw std::runtime_error("Invalid or missing color fields (r, g, b) in Sphere settings.");

            auto getFloatOrInt = [](const libconfig::Setting &s) -> float {
                if (s.getType() == libconfig::Setting::TypeFloat)
                    return static_cast<float>(s);
                if (s.getType() == libconfig::Setting::TypeInt)
                    return static_cast<float>(static_cast<int>(s));
                throw std::runtime_error("Sphere: value is not a number");
            };

            std::string material = setting["material"].c_str();
            std::shared_ptr<AMaterial> mat;
            if (material == "Default") {
                mat = std::make_shared<Default>();
            } else if (material == "Metal") {
                mat = std::make_shared<Metal>();
            } else if (material == "Chessboard") {
                mat = std::make_shared<ChessboardMaterial>();
            } else if (material == "PerlinNoise") {
                mat = std::make_shared<PerlinNoiseMaterial>();
            } else if (material == "Transparent") {
                mat = std::make_shared<Transparent>();
            } else {
                throw std::runtime_error("Sphere: Unknown material type");
            }
            Math::Vector position(
                getFloatOrInt(setting["x"]),
                getFloatOrInt(setting["y"]),
                getFloatOrInt(setting["z"])
            );
            float radius = getFloatOrInt(setting["radius"]);
            Color color(
                static_cast<int>(colorSetting["r"]),
                static_cast<int>(colorSetting["g"]),
                static_cast<int>(colorSetting["b"])
            );
            return std::make_shared<Sphere>(position, radius, color, mat);
        } catch (const std::exception &e) {
            std::cerr << "[Sphere] Error: " << e.what() << std::endl;
            return nullptr;
        }
    }

    /**
     * @brief Register the Sphere plugin.
     * @details This function is called to register the Sphere plugin.
     */
    void registerPlugin()
    {
        PluginsManager::registerPrimitiveFactory("sphere", &createPrimitive);
    }
};
