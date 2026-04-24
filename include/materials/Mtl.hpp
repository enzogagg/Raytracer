/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Mtl
*/

#include "AMaterial.hpp"

#ifndef MTL_HPP_
#define MTL_HPP_

class Mtl : public AMaterial {
    public:
        /**
         * @brief Construct a new Mtl object.
         */
        Mtl(const std::string &name, float ambient, float diffuse, float specular, float shininess)
            : AMaterial(name, ambient, diffuse, specular, shininess) {}

        /**
         * @brief Destroy the Mtl object.
         */
        ~Mtl() override = default;
};

#endif /* !MTL_HPP_ */
