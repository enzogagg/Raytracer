/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-raytracer-yanis.dolivet
** File description:
** PerlinNoise
*/

#include "PerlinNoise.hpp"

PerlinNoiseMaterial::PerlinNoiseMaterial()
    : PerlinNoiseMaterial(Color(0, 0, 0), Color(255, 255, 255), 1.0)
{
    _p.resize(256);
    std::iota(_p.begin(), _p.end(), 0);
    std::shuffle(_p.begin(), _p.end(), std::mt19937(std::random_device{}()));
    _p.insert(_p.end(), _p.begin(), _p.end());
}

PerlinNoiseMaterial::PerlinNoiseMaterial(const Color &color1, const Color &color2, double scale)
    : AMaterial("perlin", 0.7, 0.8, 2.0, 0.1), _color1(color1), _color2(color2), _scale(scale)
{
    _p.resize(256);
    std::iota(_p.begin(), _p.end(), 0);
    std::shuffle(_p.begin(), _p.end(), std::mt19937(std::random_device{}()));
    _p.insert(_p.end(), _p.begin(), _p.end());
}

double PerlinNoiseMaterial::fade(double t) const {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinNoiseMaterial::lerp(double t, double a, double b) const {
    return a + t * (b - a);
}

double PerlinNoiseMaterial::grad(int hash, double x, double y) const {
    int h = hash & 7;
    double u = h < 4 ? x : y;
    double v = h < 4 ? y : x;
    return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
}

double PerlinNoiseMaterial::noise(double x, double y) const {
    int X = static_cast<int>(floor(x)) & 255;
    int Y = static_cast<int>(floor(y)) & 255;
    x -= floor(x);
    y -= floor(y);
    double u = fade(x);
    double v = fade(y);

    int A = _p[X] + Y;
    int B = _p[X + 1] + Y;

    return lerp(v,
        lerp(u, grad(_p[A], x, y), grad(_p[B], x - 1, y)),
        lerp(u, grad(_p[A + 1], x, y - 1), grad(_p[B + 1], x - 1, y - 1))
    );
}

Color PerlinNoiseMaterial::getColorAt(const Math::Point &point) const {
    double x = point.getX() / _scale;
    double y = point.getZ() / _scale;
    double value = noise(x, y);
    double t = (value + 1.0) / 2.0;
    return _color1 * (1.0 - t) + _color2 * t;
}
