/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** AMaterial
*/

#ifndef AMATERIAL_HPP_
#define AMATERIAL_HPP_

#include "Ray.hpp"
#include "Color.hpp"

class AMaterial {
    public:
        /**
         * @brief Construct a new AMaterial object with given coefficients.
         *
         * @param name        Material name identifier.
         * @param ambient     Ambient coefficient (ka).
         * @param diffuse     Diffuse coefficient (kd).
         * @param specular    Specular coefficient (ks).
         * @param shininess   Shininess exponent (alpha).
         */
        AMaterial(const std::string &name, float ambient, float diffuse, float specular, float shininess);

        virtual ~AMaterial() = default;

        // Getters
        const std::string &getName() const;
        float getAmbient() const;
        float getDiffuse() const;
        float getSpecular() const;
        float getShininess() const;
        float getTransparency() const;
        float getRefractionIndex() const;

        /**
         * @brief Set the diffuse color of the material.
         * @param color The diffuse color.
         */
        void setDiffuseColor(const Color &color);

        /**
         * @brief Get the diffuse color of the material.
         * @return The diffuse color.
         */
        const Color &getDiffuseColor() const;

        /**
         * @brief Set the specular color of the material.
         * @param color The specular color.
         */
        void setSpecularColor(const Color &color);

        /**
         * @brief Get the specular color of the material.
         * @return The specular color.
         */
        const Color &getSpecularColor() const;

        /**
         * @brief Set the shininess of the material.
         * @param shininess The shininess value.
         */
        void setShininess(float shininess);

        /**
         * @brief Get the color at a specific point on the surface (for procedural textures)
         * @param point The point on the surface
         * @return The color at that point
         *
         * By default, returns the diffuse color. Override this in derived classes
         * to implement procedural textures like the chessboard pattern.
         */
        virtual Color getColorAt(const Math::Point &point) const;

        /**
         * @brief Set the transparency of the material.
         * @param transparency The transparency value (0 = opaque, 1 = fully transparent).
         */
        void setTransparency(float transparency);

        /**
         * @brief Set the refraction index of the material.
         * @param refractionIndex The refraction index value.
         */
        void setRefractionIndex(float refractionIndex);

        /**
         * @brief Load material properties from a .mtl file line.
         * @param line The line from the .mtl file.
         */
        void loadFromMtlLine(const std::string &line);

    private:
        std::string _name;
        float _ka;
        float _kd;
        float _ks;
        float _shininess;
        float _transparency = 0.0f; // 0 = opaque, 1 = fully transparent
        float _refractionIndex = 1.0f; // Default is air (1.0)
        Color _diffuseColor = Color(255, 255, 255); // Default white color
        Color _specularColor = Color(255, 255, 255); // Default white color
};

#endif // AMATERIAL_HPP_
