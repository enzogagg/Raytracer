/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Transparent
*/

#include "Transparent.hpp"

Transparent::Transparent() : AMaterial("Transparent", 0.0f, 0.0f, 0.0f, 0.0f)
{
    setTransparency(1.0f); // Transparence totale
    setRefractionIndex(1.5f); // Indice de réfraction par défaut (verre)
}
