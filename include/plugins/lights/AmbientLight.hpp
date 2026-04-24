/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** AmbientLight
*/

/**
 * @file AmbientLight.cpp
 * @brief AmbientLight class implementation.
 * @details This file contains the implementation of the AmbientLight class,
 *      which is a plugin for the raytracer project.
 * @note The AmbientLight class represents an ambient light source in the scene.
 */
#pragma once

#include "PluginsManager.hpp"
#include "ILight.hpp"

/**
 * @class AmbientLight
 * @brief A class to represent an ambient light source in the raytracer project.
 */
class AmbientLight : public ILight {
    public:

        /**
         * @brief Constructor for the AmbientLight class.
         * @param intensity The intensity of the light source.
         */
        AmbientLight(float intensity, const Color &color);

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
        float _intensity;
        Color _ambient;
};

extern "C" {

    /**
     * @brief Create an AmbientLight object.
     * @details This function creates a new AmbientLight object.
     * @param setting The settings for the AmbientLight object.
     * @return A pointer to the created AmbientLight object.
     */
    std::shared_ptr<ILight> createLight(const libconfig::Setting &setting)
    {
        try {
            if (!setting.exists("intensity") || !setting.exists("color"))
                throw std::runtime_error("Missing required fields (intensity, color) in AmbientLight settings.");
            if (!setting["color"].isGroup())
                throw std::runtime_error("Invalid types for field in AmbientLight settings");

            const libconfig::Setting &colorSetting = setting["color"];

            if (!colorSetting.exists("r") || !colorSetting.exists("g") ||
                !colorSetting.exists("b") || !colorSetting["r"].isNumber() ||
                !colorSetting["g"].isNumber() || !colorSetting["b"].isNumber())
                throw std::runtime_error("Invalid or missing color fields (r, g, b) in AmbientLight settings.");

            auto getFloatOrInt = [](const libconfig::Setting &s) -> float {
                if (s.getType() == libconfig::Setting::TypeFloat)
                    return static_cast<float>(s);
                if (s.getType() == libconfig::Setting::TypeInt)
                    return static_cast<float>(static_cast<int>(s));
                throw std::runtime_error("AmbientLight: value is not a number");
            };

            float intensity = getFloatOrInt(setting["intensity"]);
            Color color(
                static_cast<int>(colorSetting["r"]),
                static_cast<int>(colorSetting["g"]),
                static_cast<int>(colorSetting["b"])
            );

            return std::make_shared<AmbientLight>(intensity, color);
        } catch (const std::exception &e) {
            std::cerr << "[AmbientLight] Error: " << e.what() << std::endl;
            return nullptr;
        }
    }

    /**
     * @brief Register the AmbientLight plugin.
     * @details This function registers the AmbientLight plugin with the
     *      PluginsManager.
     */
    void registerPlugin()
    {
        PluginsManager::registerLightFactory("ambient", &createLight);
    }
};
