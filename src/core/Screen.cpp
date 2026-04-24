/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Screen
*/

#include "Screen.hpp"

Screen::Screen()
    : _origin(Math::Point()), _bottom_side(Math::Vector()), _left_side(Math::Vector())
{
}

Screen::Screen(Math::Point origin, Math::Vector bottom_side, Math::Vector left_side)
    : _origin(origin), _bottom_side(bottom_side), _left_side(left_side)
{
}

Screen::~Screen()
{

}

Math::Point Screen::getOrigin() const
{
    return _origin;
}


Math::Point Screen::pointAt(double u, double v)
{
    Math::Vector u_component = _bottom_side * u;
    Math::Vector v_component = _left_side * v;
    return _origin + u_component + v_component;
}

void Screen::translate(Math::Vector translation)
{
    _origin += translation;
}

void Screen::rotate(double angle, std::string axis)
{
    double radiant = angle * M_PI / 180;
    const unsigned int X = 4;
    const unsigned int Y = 1;
    Math::Matrix<X, Y> ori(_origin.pointToMatrix());
    Math::Matrix<X, Y> btm_right(_bottom_side.vectorToMatrix());
    Math::Matrix<X, Y> top_lf(_left_side.vectorToMatrix());

    if (Math::Vector(1, 0, 0) == axis) { // Rotation around the X axis
        double rot_matrix[X][X] = {
            {1, 0, 0, 0},
            {0, std::cos(radiant), -std::sin(radiant), 0},
            {0, std::sinf(radiant), std::cos(radiant), 0},
            {0, 0, 0, 1}
        };
        Math::Matrix<X, X> rot(rot_matrix);

        Math::Matrix<X, Y>new_origin = rot * ori;
        _origin = Math::Point(
            new_origin(0, 0),
            new_origin(1, 0),
            new_origin(2, 0)
        );

        Math::Matrix<X, Y>new_btm_right = rot * btm_right;
        _bottom_side = Math::Vector(
            new_btm_right(0, 0),
            new_btm_right(1, 0),
            new_btm_right(2, 0)
        );

        Math::Matrix<X, Y>new_left_side = rot * top_lf;
        _left_side = Math::Vector(
            new_left_side(0, 0),
            new_left_side(1, 0),
            new_left_side(2, 0)
        );
    } else if (Math::Vector(0, 1, 0) == axis) { // Rotation around the Y axis
        double rot_matrix[X][X] = {
            {std::cos(radiant), 0, std::sin(radiant), 0},
            {0, 1, 0, 0},
            {-std::sin(radiant), 0, std::cos(radiant), 0},
            {0, 0, 0, 1}
        };
        Math::Matrix<X, X> rot(rot_matrix);

        Math::Matrix<X, Y>new_origin = rot * ori;
        _origin = Math::Point(
            new_origin(0, 0),
            new_origin(1, 0),
            new_origin(2, 0)
        );

        Math::Matrix<X, Y>new_btm_right = rot * btm_right;
        _bottom_side = Math::Vector(
            new_btm_right(0, 0),
            new_btm_right(1, 0),
            new_btm_right(2, 0)
        );

        Math::Matrix<X, Y>new_left_side = rot * top_lf;
        _left_side = Math::Vector(
            new_left_side(0, 0),
            new_left_side(1, 0),
            new_left_side(2, 0)
        );
    } else if (Math::Vector(0, 0, 1) == axis) { // Rotation around the Z axis
        double rot_matrix[X][X] = {
            {std::cos(radiant), -std::sin(radiant), 0, 0},
            {std::sin(radiant), std::cos(radiant), 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };
        Math::Matrix<X, X> rot(rot_matrix);

        Math::Matrix<X, Y>new_origin = rot * ori;
        _origin = Math::Point(
            new_origin(0, 0),
            new_origin(1, 0),
            new_origin(2, 0)
        );

        Math::Matrix<X, Y>new_btm_right = rot * btm_right;
        _bottom_side = Math::Vector(
            new_btm_right(0, 0),
            new_btm_right(1, 0),
            new_btm_right(2, 0)
        );

        Math::Matrix<X, Y>new_left_side = rot * top_lf;
        _left_side = Math::Vector(
            new_left_side(0, 0),
            new_left_side(1, 0),
            new_left_side(2, 0)
        );
    }
}

void Screen::shear(double strength)
{
    const unsigned int X = 1;
    const unsigned int Y = 2;
    Math::Matrix<X, Y> ori(_origin.shearToMatrix());
    Math::Matrix<X, Y> btm_right(_bottom_side.shearToMatrix());
    Math::Matrix<X, Y> top_lf(_left_side.shearToMatrix());
    double shearMatrix[Y][Y] = {
        {1, strength},
        {0, 1}
    };
    Math::Matrix<Y, Y> rot(shearMatrix);
    Math::Matrix<X, Y>new_origin = ori * rot;
    _origin = Math::Point(
        new_origin(0, 0),
        new_origin(0, 1),
        _origin.getZ()
    );

    Math::Matrix<X, Y>new_btm_right = btm_right * rot;
    _bottom_side = Math::Vector(
        new_btm_right(0, 0),
        new_btm_right(0, 1),
        _bottom_side.getZ()
    );

    Math::Matrix<X, Y>new_left_side = top_lf * rot;
    _left_side = Math::Vector(
        new_left_side(0, 0),
        new_left_side(0, 1),
        _left_side.getZ()
    );
}
