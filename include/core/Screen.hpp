/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Screen
*/

#pragma once

#include "Point.hpp"
#include "Vector.hpp"

class Screen {
    public:
        Screen();
        Screen(Math::Point origin, Math::Vector bottom_side, Math::Vector left_side);
        ~Screen();

        Math::Point pointAt(double u, double v);

        void translate(Math::Vector translation);

        void rotate(double angle, std::string axis);

        void shear(double strength);

        Math::Point getOrigin() const;

    protected:
    private:
        Math::Point _origin;
        Math::Vector _bottom_side;
        Math::Vector _left_side;
};
