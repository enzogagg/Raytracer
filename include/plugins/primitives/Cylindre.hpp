/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cylindre
*/

/**
 * @file Cylindre.cpp
 * @brief Cylindre class implementation.
 * @details This file contains the implementation of the Cylindre class,
 *      which is a plugin for the raytracer project.
 * @note The Cylindre class represents a Cylindre in 3D space.
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
class Cylindre : public IPrimitive {
    public:
        /**
         * @brief Default constructor for the Cylindre shape.
         * By default tip is at (0, 0, 0), height at (0, 0, 0) and angle at 0
         */
        Cylindre();

        /**
         * @brief Constructor of the Cylindre shape
         * @param center Point that represents the center of the bottom cap of the Cylindre
         * @param radius The radius of both cap of the Cylindre
         * @param height height of the Cylindre
         */
        Cylindre(Math::Point center, double radius, double height, Color &color,
            const std::shared_ptr<AMaterial> &mat);

        /**
         * @brief basic destructor of the Cylindre class
         */
        ~Cylindre();

        /**
         * @brief Get the type of the primitive shape.
         * @return The type of the shape as a string.
         */
        const std::string &getType() const override;

        /**
         * @brief Check if a ray intersects with the primitive shape.
         * @param ray The ray to check for intersection.
         * @return True if the ray intersects with the shape, false otherwise.
         */
        bool intersect(const Ray &ray) const override;

        /**
         * @brief Get the intersection point with the base of the Cylindre (represented by a circle)
         * @param ray The ray to check for intersection.
         * @param cap_center Center of the bottom cap of the Cylindre
         * @param normal vector normal at the cylindre
         * @return the intersection point between one of the cap of the Cylindre and the ray
         */
        Math::Point intersection_cap(const Ray &ray, const Math::Point &cap_center, const Math::Vector &normal) const;

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
        Math::Point _center;
        double _radius;
        double _height;
        Color _color;
        std::shared_ptr<AMaterial> _material;

};

extern "C" {

    /**
     * @brief Create a Cylindre object.
     * @details This function creates a new Cylindre object.
     * @param setting The settings for the Cylindre object.
     * @return A pointer to the created Cylindre object.
     */
    std::shared_ptr<IPrimitive> createPrimitive(const libconfig::Setting &setting)
    {
        try {
            if (!setting.exists("x") || !setting.exists("y") ||
                !setting.exists("z") || !setting.exists("height") ||
                !setting.exists("angle")  || !setting.exists("color"))
                throw std::runtime_error("Missing required fields (x, y, z, radius, color) in Cylindre settings.");
            if (!setting["color"].isGroup())
                throw std::runtime_error("Cylindre: color is not a group");

            const libconfig::Setting &colorSetting = setting["color"];

            if (!colorSetting.exists("r") || !colorSetting.exists("g") ||
                !colorSetting.exists("b") || !colorSetting["r"].isNumber() ||
                !colorSetting["g"].isNumber() || !colorSetting["b"].isNumber())
                throw std::runtime_error("Invalid or missing color fields (r, g, b) in Cylindre settings.");

            auto getFloatOrInt = [](const libconfig::Setting &s) -> float {
                if (s.getType() == libconfig::Setting::TypeFloat)
                    return static_cast<float>(s);
                if (s.getType() == libconfig::Setting::TypeInt)
                    return static_cast<float>(static_cast<int>(s));
                throw std::runtime_error("Cylindre: value is not a number");
            };

            Math::Point position(
                getFloatOrInt(setting["x"]),
                getFloatOrInt(setting["y"]),
                getFloatOrInt(setting["z"])
            );
            double height = getFloatOrInt(setting["height"]);
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
                throw std::runtime_error("Cylinder: Unknown material type");
            }
            return std::make_shared<Cylindre>(position, angle, height, color, mat);
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
        PluginsManager::registerPrimitiveFactory("cylindre", &createPrimitive);
    }
};

