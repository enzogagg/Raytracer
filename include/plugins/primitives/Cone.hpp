/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cone
*/

/**
 * @file Cone.cpp
 * @brief Cone class implementation.
 * @details This file contains the implementation of the Cone class,
 *      which is a plugin for the raytracer project.
 * @note The Cone class represents a Cone in 3D space.
 */

#pragma once

#include "PluginsManager.hpp"
#include "IPrimitive.hpp"
#include "AMaterial.hpp"
#include "Default.hpp"
#include "Metal.hpp"
#include "Chessboard.hpp"
#include "PerlinNoise.hpp"


/**
 * @class Plane
 * @brief A class to represent a plane in 3D space.
 */
class Cone : public IPrimitive {
    public:
        /**
         * @brief Default constructor for the cone shape.
         * By default tip is at (0, 0, 0), height at (0, 0, 0) and angle at 0
         */
        Cone();

        /**
         * @brief Constructor of the cone shape
         * @param tip Point that represent the tip of the cone
         * @param height height vector, the vector's origin is the tip of the cone
         * @param angle the angle in degree represented between the height vector and the
         * surface of the shape
         * @param color The color of the cone.
         *
         * @note If you want a straight, x and z align axis cone a basic height vector
         * @note would looks like height = (0, -1, 0)
         */
        Cone(Math::Point tip, Math::Vector height, double angle, Color &color,
            const std::shared_ptr<AMaterial> &mat);

        /**
         * @brief basic destructor of the Cone class
         */
        ~Cone();

        /**
         * @brief Get the type of the primitive shape.
         * @return The type of the shape as a string.
         */
        const std::string &getType() const override;

        /**
         * @brief Check if a ray intersect with the base of the cone (represented by a circle)
         * @param ray The ray to check for intersection.
         * @return true if it does, false if not
         */
        bool intersect_base(const Ray &ray) const;

        /**
         * @brief Check if a ray intersect with the cone
         * @param ray The ray to check for intersection.
         * @return true if it does, false if not
         */
        bool intersectCone(const Ray &ray) const;

        /**
         * @brief Check if a ray intersects with the primitive shape.
         * @param ray The ray to check for intersection.
         * @return True if the ray intersects with the shape, false otherwise.
         */
        bool intersect(const Ray &ray) const override;

        /**
         * @brief Get the intersection point with the base of the cone (represented by a circle)
         * @param ray The ray to check for intersection.
         * @return the intersection point between the ray and the base
         */
        Math::Point getIntersectBase(const Ray &ray) const;

        /**
         * @brief Get the intersection point with the cone
         * @param ray The ray to check for intersection.
         * @return the intersection point between the ray and the cone
         */
        Math::Point getIntersectCone(const Ray &ray) const;

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
         * @brief Get the color of the primitive shape.
         * @return The color of the shape.
         */
        Color getColor() const override;

        /**
         * @brief Get the material of the primitive shape.
         * @return The material of the shape.
         */
        std::shared_ptr<AMaterial> getMaterial() const override;

    protected:
    private:
        Math::Point _tip;
        Math::Vector _height;
        double _radiant;
        Color _color;
        std::shared_ptr<AMaterial> _material;

};

extern "C" {

    /**
     * @brief Create a Cone object.
     * @details This function creates a new Cone object.
     * @param setting The settings for the Cone object.
     * @return A pointer to the created Cone object.
     */
    std::shared_ptr<IPrimitive> createPrimitive(const libconfig::Setting &setting)
    {
        try {
            if (!setting.exists("x") || !setting.exists("y") ||
                !setting.exists("z") || !setting.exists("height") ||
                !setting.exists("angle")  || !setting.exists("color"))
                throw std::runtime_error("Missing required fields (x, y, z, height, angle, color) in Cone settings.");
            if (!setting["color"].isGroup())
                throw std::runtime_error("Cone: color is not a group");

            const libconfig::Setting &heightSetting = setting["height"];
            const libconfig::Setting &colorSetting = setting["color"];

            if (!heightSetting.exists("x") || !heightSetting.exists("y") ||
                !heightSetting.exists("z") || !heightSetting["x"].isNumber() ||
                !heightSetting["y"].isNumber() || !heightSetting["z"].isNumber())
                throw std::runtime_error("Invalid or missing height fields (x, y, z) in Cone settings.");

            if (!colorSetting.exists("r") || !colorSetting.exists("g") ||
                !colorSetting.exists("b") || !colorSetting["r"].isNumber() ||
                !colorSetting["g"].isNumber() || !colorSetting["b"].isNumber())
                throw std::runtime_error("Invalid or missing color fields (r, g, b) in Cone settings.");

            auto getFloatOrInt = [](const libconfig::Setting &s) -> float {
                if (s.getType() == libconfig::Setting::TypeFloat)
                    return static_cast<float>(s);
                if (s.getType() == libconfig::Setting::TypeInt)
                    return static_cast<float>(static_cast<int>(s));
                throw std::runtime_error("Cone: value is not a number");
            };

            Math::Point position(
                getFloatOrInt(setting["x"]),
                getFloatOrInt(setting["y"]),
                getFloatOrInt(setting["z"])
            );
            Math::Vector height(
                getFloatOrInt(heightSetting["x"]),
                getFloatOrInt(heightSetting["y"]),
                getFloatOrInt(heightSetting["z"])
            );
            double angle = getFloatOrInt(setting["angle"]);
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
                throw std::runtime_error("Cone: Unknown material type");
            }
            return std::make_shared<Cone>(position, height, angle, color, mat);
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
        PluginsManager::registerPrimitiveFactory("cone", &createPrimitive);
    }
};

