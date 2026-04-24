/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ChessboardMaterial
*/

#include "Chessboard.hpp"

ChessboardMaterial::ChessboardMaterial()
    : ChessboardMaterial(Color(0, 0, 0), Color(255, 255, 255), 1.0)
{
}

ChessboardMaterial::ChessboardMaterial(const Color &color1, const Color &color2, double scale)
    : AMaterial("chessboard", 0.7, 0.8, 2.0, 0.1), _color1(color1), _color2(color2), _scale(scale)
{
}

Color ChessboardMaterial::getColorAt(const Math::Point &point) const
{
    int x = static_cast<int>(std::floor(point.getX() / _scale));
    int y = static_cast<int>(std::floor(point.getY() / _scale));
    int z = static_cast<int>(std::floor(point.getZ() / _scale));

    if ((x + y + z) % 2 == 0) {
        return _color1;
    } else {
        return _color2;
    }
}
