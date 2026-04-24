/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ObjParser
*/

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include "Point.hpp"
#include "IPrimitive.hpp"
#include "AMaterial.hpp"

/**
 * @class ObjParser
 * @brief A class to parse .obj files and create shapes for the raytracer.
 */
class ObjParser {
    public:
        /**
         * @brief Parse a .obj file and create a list of primitives.
         * @param filepath The path to the .obj file.
         * @return A vector of shared pointers to IPrimitive objects.
         */
        static std::vector<std::shared_ptr<IPrimitive>> parse(const std::string &filepath);

        /**
         * @brief Load materials from a .mtl file.
         * @param mtlFilePath The path to the .mtl file.
         * @return A map of material names to AMaterial objects.
         */
        static std::unordered_map<std::string, AMaterial> loadMaterials(const std::string &mtlFilePath);

        /**
         * @brief Parse a material line from a .mtl file.
         * @param line The line to parse.
         * @param material The material to update.
         * @return The updated material.
         */
        static std::unordered_map<std::string, Color> parseMaterial(const std::string &line);

    private:
        static Math::Point parseVertex(const std::string &line);
        static std::vector<int> parseFace(const std::string &line);
};
