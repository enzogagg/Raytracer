/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** PointLight
*/

/**
 * @file PointLight.cpp
 * @brief PointLight class implementation.
 * @details This file contains the implementation of the PointLight class,
 *      which is a plugin for the raytracer project.
 * @note The PointLight class represents a point light source in the scene.
 */
#pragma once

#include "PluginsManager.hpp"
#include "ILight.hpp"

/**
 * @class PointLight
 * @brief A class to represent a point light source in the raytracer project.
 */
class PointLight : public ILight {
    public:
        /**
         * @brief Constructor for the PointLight class.
         * @param position The position of the light source.
         * @param intensity The intensity of the light source.
         * @param color The color of the light source.
         */
        PointLight(const Math::Vector &position, const Color &color, float intensity);

        /**
         * @brief Get the type of the light source.
         * @return The type of the light source.
         */
        const std::string &getType() const override;

        /**
         * @brief Get the position of the light source.
         * @return The position of the light source.
         */
        const Math::Point &getPosition() const override;

        /**
         * @brief Get the direction of the light source.
         * @return The color of the light source.
         */
        const Math::Vector &getDirection() const override;

        /**
         * @brief Get the intensity of the light source.
         * @return The intensity of the light source.
         */
        float getIntensity() const override;

        /**
         * @brief Get the color of the light source.
         * @return The color of the light source.
         */
        const Color &getColor() const override;

        /**
         * @brief Get the ambient component of the light source.
         * @return The ambient component of the light source.
         */
        const Color &getAmbientComponent() const override;

        /**
         * @brief Get the diffuse component of the light source.
         * @return The diffuse component of the light source.
         */
        const Color &getDiffuseComponent() const override;

        /**
         * @brief Get the specular component of the light source.
         * @return The specular component of the light source.
         */
        const Color &getSpecularComponent() const override;

    private:
        Math::Point _position;
        float _intensity;
        Color _color;
        Color _ambient;
        Color _diffuse;
        Color _specular;
};

extern "C" {

    /**
     * @brief Create a PointLight object.
     * @details This function creates a new PointLight object.
     * @param file The file to parse.
     * @return A pointer to the created PointLight object.
     */
    std::shared_ptr<ILight> createLight(const libconfig::Setting &setting)
    {
        try {
            if (!setting.exists("x") || !setting.exists("y") ||
                !setting.exists("z") || !setting.exists("intensity") ||
                !setting.exists("color"))
                throw std::runtime_error("Missing required fields (x, y, z, intensity, color) in PointLight settings.");
            if (!setting["color"].isGroup())
                throw std::runtime_error("PointLight: color is not a group");

            const libconfig::Setting &colorSetting = setting["color"];

            if (!colorSetting.exists("r") || !colorSetting.exists("g") ||
                !colorSetting.exists("b") || !colorSetting["r"].isNumber() ||
                !colorSetting["g"].isNumber() || !colorSetting["b"].isNumber())
                throw std::runtime_error("PointLight: r, g, b is not a number");

            auto getFloatOrInt = [](const libconfig::Setting &s) -> float {
                if (s.getType() == libconfig::Setting::TypeFloat)
                    return static_cast<float>(s);
                if (s.getType() == libconfig::Setting::TypeInt)
                    return static_cast<float>(static_cast<int>(s));
                throw std::runtime_error("PointLight: value is not a number");
            };

            Math::Vector position(
                getFloatOrInt(setting["x"]),
                getFloatOrInt(setting["y"]),
                getFloatOrInt(setting["z"])
            );
            float intensity = getFloatOrInt(setting["intensity"]);
            Color color(
                static_cast<int>(colorSetting["r"]),
                static_cast<int>(colorSetting["g"]),
                static_cast<int>(colorSetting["b"])
            );
            return std::make_shared<PointLight>(position, color, intensity);
        } catch (const std::exception &e) {
            std::cerr << "[PointLight] Error: " << e.what() << std::endl;
            return nullptr;
        }
    }

    /**
     * @brief Register the PointLight plugin.
     * @details This function is called to register the PointLight plugin.
     */
    void registerPlugin()
    {
        PluginsManager::registerLightFactory("point", &createLight);
    }
};
