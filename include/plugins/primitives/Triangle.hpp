/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Triangle
*/

/**
 * @file Triangle.cpp
 * @brief Triangle class implementation.
 * @details This file contains the implementation of the Triangle class,
 *      which is a plugin for the raytracer project.
 * @note The Triangle class represents a Triangle in 3D space.
 */
#pragma once

#include "PluginsManager.hpp"
#include "IPrimitive.hpp"
#include "Point.hpp"
#include "AMaterial.hpp"
#include "Default.hpp"
#include "Metal.hpp"
#include "Chessboard.hpp"
#include "PerlinNoise.hpp"

/**
 * @class Triangle
 * @brief A class to represent a Triangle in 3D space.
 */
class Triangle : public IPrimitive {
    public:

        /**
         * @brief Constructor for the Triangle class.
         * @param axis The axis of the Triangle (x, y, or z).
         * @param v0 The position of the first vertex
         * @param v1 The position of the second vertex
         * @param v2 The position of the third vertex
         * @param color The color of the Triangle.
         */
        Triangle(Math::Point v0, Math::Point v1, Math::Point v2, const Color &color,
            const std::shared_ptr<AMaterial> &mat);

        /**
         * @brief Destructor for the Triangle class.
         * @note This destructor is virtual to ensure proper cleanup of derived classes.
         */
        ~Triangle() override = default;

        /**
         * @brief Get the type of the Triangle.
         * @return The type of the Triangle as a string.
         */
        const std::string &getType() const override;

        /**
         * @brief Check if a ray intersects with the Triangle.
         * @param ray The ray to check for intersection.
         * @return True if the ray intersects with the Triangle, false otherwise.
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
         * @brief Get the color of the Triangle.
         * @return The color of the Triangle.
         */
        Color getColor() const override;

        /**
         * @brief Get the material of the primitive shape.
         * @return The material of the shape.
         */
        std::shared_ptr<AMaterial> getMaterial() const override;

    private:
        std::string _axis;
        Math::Point _v0, _v1, _v2;
        Color _color;
        Math::Vector _normal;
        std::shared_ptr<AMaterial> _material;
};

extern "C" {

    /**
     * @brief Create a Triangle object.
     * @details This function creates a new Triangle object.
     * @param setting The settings for the Triangle object.
     * @return A pointer to the created Triangle object.
     */
    std::shared_ptr<IPrimitive> createPrimitive(const libconfig::Setting &setting)
    {
        try {
            if (!setting.exists("v0") || !setting.exists("v1") || !setting.exists("v2") ||
                !setting.exists("color"))
                throw std::runtime_error("Missing required fields (v0, v1, v2, color) in Triangle settings.");
            if (!setting["color"].isGroup())
                throw std::runtime_error("Triangle: color is not a group");

            const libconfig::Setting &v0Setting = setting["v0"];
            const libconfig::Setting &v1Setting = setting["v1"];
            const libconfig::Setting &v2Setting = setting["v2"];
            const libconfig::Setting &colorSetting = setting["color"];

            if (!v0Setting.exists("x") || !v0Setting.exists("y") ||
                !v0Setting.exists("z") || !v0Setting["x"].isNumber() ||
                !v0Setting["y"].isNumber() || !v0Setting["z"].isNumber())
                throw std::runtime_error("Invalid or missing v0 fields (x, y, z) in Triangle settings.");

            if (!v1Setting.exists("x") || !v1Setting.exists("y") ||
                !v1Setting.exists("z") || !v1Setting["x"].isNumber() ||
                !v1Setting["y"].isNumber() || !v1Setting["z"].isNumber())
                throw std::runtime_error("Invalid or missing v1 fields (x, y, z) in Triangle settings.");

            if (!v2Setting.exists("x") || !v2Setting.exists("y") ||
                !v2Setting.exists("z") || !v2Setting["x"].isNumber() ||
                !v2Setting["y"].isNumber() || !v2Setting["z"].isNumber())
                throw std::runtime_error("Invalid or missing v2 fields (x, y, z) in Triangle settings.");

            if (!colorSetting.exists("r") || !colorSetting.exists("g") ||
                !colorSetting.exists("b") || !colorSetting["r"].isNumber() ||
                !colorSetting["g"].isNumber() || !colorSetting["b"].isNumber()) {
                throw std::runtime_error("Invalid or missing color fields (r, g, b) in Triangle settings.");
            }

            auto getFloatOrInt = [](const libconfig::Setting &s) -> float {
                if (s.getType() == libconfig::Setting::TypeFloat)
                    return static_cast<float>(s);
                if (s.getType() == libconfig::Setting::TypeInt)
                    return static_cast<float>(static_cast<int>(s));
                throw std::runtime_error("Triangle: value is not a number");
            };

            Math::Point v0(
                getFloatOrInt(v0Setting["x"]),
                getFloatOrInt(v0Setting["y"]),
                getFloatOrInt(v0Setting["z"])
            );
            Math::Point v1(
                getFloatOrInt(v1Setting["x"]),
                getFloatOrInt(v1Setting["y"]),
                getFloatOrInt(v1Setting["z"])
            );
            Math::Point v2(
                getFloatOrInt(v2Setting["x"]),
                getFloatOrInt(v2Setting["y"]),
                getFloatOrInt(v2Setting["z"])
            );
            Color color(
                static_cast<int>(colorSetting["r"]),
                static_cast<int>(colorSetting["g"]),
                static_cast<int>(colorSetting["b"])
            );
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
            } else {
                throw std::runtime_error("Triangle: Unknown material type");
            }
            return std::make_shared<Triangle>(v0, v1, v2, color, mat);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            return nullptr;
        }
    }

    /**
     * @brief Register the Triangle plugin.
     * @details This function is called to register the Triangle plugin.
     */
    void registerPlugin()
    {
        PluginsManager::registerPrimitiveFactory("triangle", &createPrimitive);
    }
};
