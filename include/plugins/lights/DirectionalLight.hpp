/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** DirectionalLight
*/

/**
 * @file DirectionalLight.cpp
 * @brief DirectionalLight class implementation.
 * @details This file contains the implementation of the DirectionalLight class,
 *      which is a plugin for the raytracer project.
 * @note The DirectionalLight class represents a directional light source in the scene.
 */
#pragma once

#include "PluginsManager.hpp"
#include "ILight.hpp"

/**
 * @class DirectionalLight
 * @brief A class to represent a directional light source in the raytracer project.
 */
class DirectionalLight : public ILight {
    public:
        /**
         * @brief Constructor for the DirectionalLight class.
         * @param position The position of the light source.
         * @param intensity The intensity of the light source.
         * @param direction The direction of the light source.
         */
        DirectionalLight(const Math::Vector &direction, const Color &color, float intensity);

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
         * @return The direction of the light source.
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
        Math::Vector _direction;
        float _intensity;
        Color _color;
        Color _ambient;
        Color _diffuse;
        Color _specular;
};

extern "C" {

    /**
     * @brief Create a DirectionalLight object.
     * @details This function creates a new DirectionalLight object.
     * @param setting The settings for the DirectionalLight object.
     * @return A pointer to the created DirectionalLight object.
     */
    std::shared_ptr<ILight> createLight(const libconfig::Setting &setting)
    {
        try {
            if (!setting.exists("x") || !setting.exists("y") ||
                !setting.exists("z") || !setting.exists("intensity") ||
                !setting.exists("color"))
                throw std::runtime_error("Missing required fields (x, y, z, intensity, color) in DirectionalLight settings.");
            if (!setting["color"].isGroup())
                throw std::runtime_error("Invalid types for field in DirectionalLight settings");

            const libconfig::Setting &colorSetting = setting["color"];

            if (!colorSetting.exists("r") || !colorSetting.exists("g") ||
                !colorSetting.exists("b") || !colorSetting["r"].isNumber() ||
                !colorSetting["g"].isNumber() || !colorSetting["b"].isNumber())
                throw std::runtime_error("Invalid or missing color fields (r, g, b) in DirectionalLight settings.");

            auto getFloatOrInt = [](const libconfig::Setting &s) -> float {
                if (s.getType() == libconfig::Setting::TypeFloat)
                    return static_cast<float>(s);
                if (s.getType() == libconfig::Setting::TypeInt)
                    return static_cast<float>(static_cast<int>(s));
                throw std::runtime_error("DirectionalLight: value is not a number");
            };

            Math::Vector direction(
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

            return std::make_shared<DirectionalLight>(direction, color, intensity);
        } catch (const std::exception &e) {
            std::cerr << "[DirectionalLight] Error: " << e.what() << std::endl;
            return nullptr;
        }
    }

    /**
     * @brief Register the DirectionalLight plugin.
     * @details This function registers the DirectionalLight plugin with the
     *      PluginsManager.
     */
    void registerPlugin()
    {
        PluginsManager::registerLightFactory("directional", &createLight);
    }
}
