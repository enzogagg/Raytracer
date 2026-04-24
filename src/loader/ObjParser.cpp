/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ObjParser
*/

#include "ObjParser.hpp"
#include "Face.hpp"
#include <unordered_map>
#include <sstream>
#include <filesystem>

std::unordered_map<std::string, Color> ObjParser::parseMaterial(const std::string &line)
{
    static std::unordered_map<std::string, Color> materials;
    static std::string currentMaterial;

    std::istringstream iss(line);
    std::string prefix;
    iss >> prefix;

    if (prefix == "newmtl") {
        iss >> currentMaterial;
        materials[currentMaterial] = Color(255, 255, 255);
    } else if (prefix == "Kd") {
        double r, g, b;
        iss >> r >> g >> b;
        if (!currentMaterial.empty()) {
            materials[currentMaterial] = Color(static_cast<int>(r * 255), static_cast<int>(g * 255), static_cast<int>(b * 255));
        }
    }
    return materials;
}

std::vector<std::shared_ptr<IPrimitive>> ObjParser::parse(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open .obj file: " + filepath);
    }

    std::vector<Math::Point> vertices;
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    std::unordered_map<std::string, Color> materials;
    std::string currentMaterial;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            vertices.push_back(parseVertex(line));
        } else if (prefix == "mtllib") {
            std::string mtlFile;
            iss >> mtlFile;
            std::filesystem::path objPath(filepath);
            std::filesystem::path mtlPath = objPath.parent_path() / mtlFile;
            std::ifstream mtlFileStream(mtlPath);
            if (mtlFileStream.is_open()) {
                std::string mtlLine;
                while (std::getline(mtlFileStream, mtlLine)) {
                    materials = parseMaterial(mtlLine);
                }
            }
        } else if (prefix == "usemtl") {
            iss >> currentMaterial;
        } else if (prefix == "f") {
            auto face = parseFace(line);
            if (face.size() >= 3) {
                for (size_t i = 1; i < face.size() - 1; ++i) {
                    auto primitive = std::make_shared<Face>(
                        vertices[face[0] - 1],
                        vertices[face[i] - 1],
                        vertices[face[i + 1] - 1],
                        materials[currentMaterial]
                    );
                    primitives.push_back(primitive);
                }
            }
        }
    }
    return primitives;
}

Math::Point ObjParser::parseVertex(const std::string &line)
{
    std::istringstream iss(line);
    std::string prefix;
    double x, y, z;
    iss >> prefix >> x >> y >> z;
    return Math::Point(x, y, z);
}

std::vector<int> ObjParser::parseFace(const std::string &line)
{
    std::istringstream iss(line);
    std::string prefix;
    iss >> prefix;

    std::vector<int> indices;
    std::string vertex;
    while (iss >> vertex) {
        size_t pos = vertex.find('/');
        if (pos != std::string::npos) {
            vertex = vertex.substr(0, pos);
        }
        indices.push_back(std::stoi(vertex));
    }

    return indices;
}
