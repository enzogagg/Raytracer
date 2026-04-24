/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Plane
*/

/**
 * @file Plane.cpp
 * @brief Plane class implementation.
 * @details This file contains the implementation of the Plane class,
 *      which is a plugin for the raytracer project.
 * @note The Plane class represents a plane in 3D space.
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
 * @class Plane
 * @brief A class to represent a plane in 3D space.
 */
class Plane : public IPrimitive {
    public:

        /**
         * @brief Constructor for the Plane class.
         * @param axis The axis of the plane (x, y, or z).
         * @param position The position of the plane along the specified axis.
         * @param color The color of the plane.
         */
        Plane(Math::Point p0, Math::Point p1, Math::Point p2, const Color &color, const std::shared_ptr<AMaterial> &mat);

        /**
         * @brief Destructor for the Plane class.
         * @note This destructor is virtual to ensure proper cleanup of derived classes.
         */
        ~Plane() override = default;

        /**
         * @brief Get the type of the plane.
         * @return The type of the plane as a string.
         */
        const std::string &getType() const override;

        /**
         * @brief Check if a ray intersects with the plane.
         * @param ray The ray to check for intersection.
         * @return True if the ray intersects with the plane, false otherwise.
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
         * @brief Get the color of the plane.
         * @return The color of the plane.
         */
        Color getColor() const override;

        /**
         * @brief Get the material of the primitive shape.
         * @return The material of the shape.
         */
        std::shared_ptr<AMaterial> getMaterial() const override;

    private:
        std::string _axis;
        float _position;
        Math::Point _a, _b, _c;
        Math::Vector _normal;
        Color _color;
        std::shared_ptr<AMaterial> _material;
};

extern "C" {

    /**
     * @brief Create a Plane object.
     * @details This function creates a new Plane object.
     * @param setting The settings for the Plane object.
     * @return A pointer to the created Plane object.
     */
    std::shared_ptr<IPrimitive> createPrimitive(const libconfig::Setting &setting)
    {
        try {
            if (!setting.exists("p0") || !setting.exists("p1") || !setting.exists("p2") ||
                !setting.exists("color")) {
                throw std::runtime_error("[Plane] Missing required fields (p0, p1, p2, color) in Plane settings.");
            }
            if (!setting["color"].isGroup()) {
                throw std::runtime_error("[Plane] Plane: color is not a group");
            }

            const libconfig::Setting &p0Setting = setting["p0"];
            const libconfig::Setting &p1Setting = setting["p1"];
            const libconfig::Setting &p2Setting = setting["p2"];
            const libconfig::Setting &colorSetting = setting["color"];

            if (!p0Setting.exists("x") || !p0Setting.exists("y") ||
                !p0Setting.exists("z") || !p0Setting["x"].isNumber() ||
                !p0Setting["y"].isNumber() || !p0Setting["z"].isNumber()) {
                throw std::runtime_error("[Plane] Invalid or missing p0 fields (x, y, z) in Plane settings.");
            }

            if (!p1Setting.exists("x") || !p1Setting.exists("y") ||
                !p1Setting.exists("z") || !p1Setting["x"].isNumber() ||
                !p1Setting["y"].isNumber() || !p1Setting["z"].isNumber()) {
                throw std::runtime_error("[Plane] Invalid or missing p1 fields (x, y, z) in Plane settings.");
            }

            if (!p2Setting.exists("x") || !p2Setting.exists("y") ||
                !p2Setting.exists("z") || !p2Setting["x"].isNumber() ||
                !p2Setting["y"].isNumber() || !p2Setting["z"].isNumber()) {
                throw std::runtime_error("[Plane] Invalid or missing p2 fields (x, y, z) in Plane settings.");
            }

            if (!colorSetting.exists("r") || !colorSetting.exists("g") ||
                !colorSetting.exists("b") || !colorSetting["r"].isNumber() ||
                !colorSetting["g"].isNumber() || !colorSetting["b"].isNumber()) {
                throw std::runtime_error("[Plane] Invalid or missing color fields (r, g, b) in Plane settings.");
            }

            float p0x = (p0Setting["x"].getType() == libconfig::Setting::TypeFloat) ? (float)p0Setting["x"] : (float)(int)p0Setting["x"];
            float p0y = (p0Setting["y"].getType() == libconfig::Setting::TypeFloat) ? (float)p0Setting["y"] : (float)(int)p0Setting["y"];
            float p0z = (p0Setting["z"].getType() == libconfig::Setting::TypeFloat) ? (float)p0Setting["z"] : (float)(int)p0Setting["z"];
            float p1x = (p1Setting["x"].getType() == libconfig::Setting::TypeFloat) ? (float)p1Setting["x"] : (float)(int)p1Setting["x"];
            float p1y = (p1Setting["y"].getType() == libconfig::Setting::TypeFloat) ? (float)p1Setting["y"] : (float)(int)p1Setting["y"];
            float p1z = (p1Setting["z"].getType() == libconfig::Setting::TypeFloat) ? (float)p1Setting["z"] : (float)(int)p1Setting["z"];
            float p2x = (p2Setting["x"].getType() == libconfig::Setting::TypeFloat) ? (float)p2Setting["x"] : (float)(int)p2Setting["x"];
            float p2y = (p2Setting["y"].getType() == libconfig::Setting::TypeFloat) ? (float)p2Setting["y"] : (float)(int)p2Setting["y"];
            float p2z = (p2Setting["z"].getType() == libconfig::Setting::TypeFloat) ? (float)p2Setting["z"] : (float)(int)p2Setting["z"];

            int r = (int)colorSetting["r"];
            int g = (int)colorSetting["g"];
            int b = (int)colorSetting["b"];

            Math::Point p0(p0x, p0y, p0z);
            Math::Point p1(p1x, p1y, p1z);
            Math::Point p2(p2x, p2y, p2z);
            Color color(r, g, b);

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
                throw std::runtime_error("Plane: Unknown material type");
            }

            return std::make_shared<Plane>(p0, p1, p2, color, mat);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            return nullptr;
        }
    }

    /**
     * @brief Register the Plane plugin.
     * @details This function is called to register the Plane plugin.
     */
    void registerPlugin()
    {
        PluginsManager::registerPrimitiveFactory("plane", &createPrimitive);
    }
};
