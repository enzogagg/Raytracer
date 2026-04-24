/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ChessboardMaterial
*/

#pragma once

#include "AMaterial.hpp"
#include "Color.hpp"
#include "Define.hpp"

/**
 * @class ChessboardMaterial
 * @brief Une classe pour représenter un matériau avec un pattern d'échiquier procédural
 */
class ChessboardMaterial : public AMaterial {
    public:
        /**
         * @brief Constructeur par défaut de la classe ChessboardMaterial
         */
        ChessboardMaterial();

        /**
         * @brief Constructeur de la classe ChessboardMaterial
         * @param color1 Première couleur de l'échiquier
         * @param color2 Deuxième couleur de l'échiquier
         * @param scale Taille des cases (scale de la texture)
         */
        ChessboardMaterial(const Color &color1, const Color &color2, double scale = 1.0);

        /**
         * @brief Déstructeur par défaut
         */
        ~ChessboardMaterial() override = default;

        /**
         * @brief Calcule la couleur du matériau à un point donné selon un pattern d'échiquier
         * @param point Point d'intersection où calculer la couleur
         * @return Couleur à ce point
         */
        Color getColorAt(const Math::Point &point) const;

    private:
        Color _color1;
        Color _color2;
        double _scale;
};
