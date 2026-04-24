/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Color
*/

/**
 * @file Color.cpp
 * @brief Color class implementation.
 * @details This file contains the implementation of the Color class,
 *      which is used for color representation in the raytracer project.
 * @note The Color class is used to represent colors in RGB format.
 */
#include "Color.hpp"

/**
 * @brief Default constructor for Color class.
 * Initializes the color to (0, 0, 0).
 * @param r The red component of the color.
 * @param g The green component of the color.
 * @param b The blue component of the color.
 * @note If no parameters are provided, the color is initialized to (0, 0, 0).
 */
Color::Color(double r, double g, double b)
    : _r(r), _g(g), _b(b)
{
}

/**
 * @brief Get the red component of the color.
 * @return The red component of the color.
 */

Color Color::operator+(const Color &other) const
{
    double colorR;
    double colorB;
    double colorG;
    double max = 255;

    colorR = std::min(this->_r + other._r, max);
    colorB = std::min(this->_b + other._b, max);
    colorG = std::min(this->_g + other._g, max);

    Color result(colorR, colorB, colorG);
    return result;
}

Color &Color::operator+=(const Color &other)
{
    _r += other._r;
    _g += other._g;
    _b += other._b;
    return *this;
}

Color &Color::operator/=(int divide)
{
    _r /= divide;
    _g /= divide;
    _b /= divide;
    return *this;
}

Color Color::operator-(const Color &other) const
{
    double colorR;
    double colorB;
    double colorG;
    double min = 0;

    colorR = std::max(this->_r - other._r, min);
    colorB = std::max(this->_b - other._b, min);
    colorG = std::max(this->_g - other._g, min);

    Color result(colorR, colorB, colorG);
    return result;
}

Color Color::operator/(double scalar) const
{
    double colorR;
    double colorB;
    double colorG;

    colorR = (scalar != 0) ? this->_r / scalar : 0;
    colorB = (scalar != 0) ? this->_b / scalar : 0;
    colorG = (scalar != 0) ? this->_g / scalar : 0;

    Color result(colorR, colorB, colorG);
    return result;
}

Color Color::operator*(double scalar) const
{
    double colorR;
    double colorB;
    double colorG;
    double max = 255;

    colorR = std::min(this->_r * scalar, max);
    colorB = std::min(this->_b * scalar, max);
    colorG = std::min(this->_g * scalar, max);

    Color result(colorR, colorB, colorG);
    return result;
}

Color &Color::operator*=(double scalar)
{
    _r *= scalar;
    _g *= scalar;
    _b *= scalar;
    return *this;
}

/**
 * @brief Multiplication operator overload.
 * @param other The color to multiply with.
 * @return A new color that is the product of this color and the other color.
 */
Color Color::operator*(const Color &other) const
{
    double colorR = this->_r * other._r;
    double colorG = this->_g * other._g;
    double colorB = this->_b * other._b;

    return Color(colorR, colorG, colorB);
}

/**
 * @brief Multiplication operator overload.
 * @param other The color to multiply with.
 * @return A reference to this color after multiplying by the other color.
 */
Color &Color::operator*=(const Color &other)
{
    this->_r *= other._r;
    this->_b *= other._b;
    this->_g *= other._g;

    return *this;
}

/**
 * @brief Apply the color intensity.
 * @param intensity The intensity to apply.
 * @return A new color that is the product of this color and the intensity.
 */
Color Color::applyIntensity(double intensity) const
{
    double colorR;
    double colorB;
    double colorG;

    colorR = this->_r * intensity;
    colorB = this->_b * intensity;
    colorG = this->_g * intensity;

    Color result(colorR, colorB, colorG);
    return result;
}

/**
 * @brief Clamp the color components to be in the range [0, 255].
 * @return A new color with clamped components.
 */
Color Color::clamp() const
{
    return Color(
        std::clamp(_r, 0.0, 255.0),
        std::clamp(_g, 0.0, 255.0),
        std::clamp(_b, 0.0, 255.0)
    );
}

/**
 * @brief Get the red component of the color.
 * @return The red component of the color.
 */
double Color::getR() const
{
    return _r;
}

/**
 * @brief Get the green component of the color.
 * @return The green component of the color.
 */
double Color::getG() const
{
    return _g;
}

/**
 * @brief Get the blue component of the color.
 * @return The blue component of the color.
 */
double Color::getB() const
{
    return _b;
}

/**
 * @brief Set the blue component of the color.
 * @return The blue component of the color.
 */
void Color::setColor(double r, double g, double b)
{
    _r = r;
    _g = g;
    _b = b;
}

std::ostream &operator<<(std::ostream &os, const Color &color)
{
    os << "Color(" << color.getR() << ", " << color.getG() << ", " << color.getB() << ")";
    return os;
}
