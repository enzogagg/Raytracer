/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-raytracer-yanis.dolivet
** File description:
** PerlinNoise
*/

#pragma once

#include "AMaterial.hpp"
#include "Color.hpp"
#include "Define.hpp"

class PerlinNoiseMaterial : public AMaterial {
    public:
        /**
         * @brief Default constructor for the PerlinNoiseMaterial class
         */
        PerlinNoiseMaterial();

        /**
         * @brief Constructor for the PerlinNoiseMaterial class
         * @param color1 First color of the Perlin noise
         * @param color2 Second color of the Perlin noise
         * @param scale Scale of the Perlin noise
         */
        PerlinNoiseMaterial(const Color &color1, const Color &color2, double scale = 1.0);

        /**
         * @brief Destructor for the PerlinNoiseMaterial class
         */
        ~PerlinNoiseMaterial() override = default;

        /**
         * @brief Calculate the color of the material at a given point using Perlin noise
         * @param point Intersection point where to calculate the color
         * @return Color at this point
         */
        Color getColorAt(const Math::Point &point) const override;

    private:
        Color _color1;
        Color _color2;
        double _scale;

        double noise(double x, double y) const;
        double fade(double t) const;
        double lerp(double t, double a, double b) const;
        double grad(int hash, double x, double y) const;
        std::vector<int> _p;
};
