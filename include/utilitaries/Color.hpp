/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Color
*/

/**
 * @file Color.hpp
 * @brief Color class header file.
 * @details This file contains the definition of the Color class,
 *      which is used for color representation in the raytracer project.
 */
#pragma once

#include "Define.hpp"

/**
 * @class Color
 * @brief A class to represent a color in RGB format.
 */
class Color {
    public:

        /**
         * @brief Default constructor for Color class.
         * Initializes the color to (0, 0, 0).
         * @param r The red component of the color.
         * @param g The green component of the color.
         * @param b The blue component of the color.
         * @note If no parameters are provided, the color is initialized to (0, 0, 0).
         * @note This constructor can be used to create a color with specific RGB values.
         */
        Color(double r = 0, double g = 0, double b = 0);

        /**
         * @brief Addition operator overload.
         * @param other The color to add.
         * @return A new color that is the sum of this color and the other color.
         */
        Color operator+(const Color &other) const;

        /**
         * @brief Addition operator overload.
         * @param other The color to add.
         * @return A reference to this color after adding the other color.
         */
        Color &operator+=(const Color &other);

        /**
         * @brief Subtraction operator overload.
         * @param other The color to subtract.
         * @return A new color that is the difference of this color and the other color.
         */
        Color operator-(const Color &other) const;

        /**
         * @brief Scalar multiplication operator overload.
         * @param scalar The scalar to multiply with.
         * @return A new color that is the product of this color and the scalar.
         */
        Color operator*(double scalar) const;

        /**
         * @brief Scalar multiplication operator overload.
         * @param scalar The scalar to multiply with.
         * @return A reference to this color after multiplying by the scalar.
         */
        Color &operator*=(double scalar);

        Color &operator/=(int divide);

        /**
         * @brief Multiplication operator overload.
         * @param other The color to multiply with.
         * @return A new color that is the product of this color and the scalar.
         */
        Color operator*(const Color &other) const;

        /**
         * @brief Multiplication operator overload.
         * @param other The color to multiply with.
         * @return A reference to this color after multiplying by the other color.
         */
        Color &operator*=(const Color &other);

        /**
         * @brief Scalar division operator overload.
         * @param scalar The scalar to divide by.
         * @return A new color that is the quotient of this color and the scalar.
         */
        Color operator/(double scalar) const;

        /**
         * @brief Apply the color intensity.
         * @param intensity The intensity to apply.
         * @return A new color that is the product of this color and the intensity.
         */
        Color applyIntensity(double intensity) const;

        /**
         * @brief Clamp the color values to be within the range [0, 255].
         * @return A new color with clamped values.
         */
        Color clamp() const;

        /**
         * @brief Get the red component of the color.
         * @return The red component of the color.
         */
        double getR() const;

        /**
         * @brief Get the green component of the color.
         * @return The green component of the color.
         */
        double getG() const;

        /**
         * @brief Get the blue component of the color.
         * @return The blue component of the color.
         */
        double getB() const;

        /**
         * @brief Set the blue component of the color.
         * @return The blue component of the color.
         */
        void setColor(double r, double g, double b);

    private:
        double _r;
        double _g;
        double _b;
};

std::ostream &operator<<(std::ostream &os, const Color &color);