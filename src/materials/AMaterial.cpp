/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** AMaterial
*/

#include "AMaterial.hpp"

AMaterial::AMaterial(const std::string &name, float ambient, float diffuse, float specular, float shininess)
: _name(name), _ka(ambient), _kd(diffuse), _ks(specular), _shininess(shininess)
{
}

const std::string &AMaterial::getName() const
{
    return _name;
}

float AMaterial::getAmbient() const
{
    return _ka;
}

float AMaterial::getDiffuse() const
{
    return _kd;
}

float AMaterial::getSpecular() const
{
    return _ks;
}

float AMaterial::getShininess() const
{
    return _shininess;
}

void AMaterial::loadFromMtlLine(const std::string &line)
{
    std::istringstream iss(line);
    std::string key;
    iss >> key;

    if (key == "Kd") {
        double r, g, b;
        iss >> r >> g >> b;
        _diffuseColor = Color(r * 255, g * 255, b * 255);
    } else if (key == "Ks") {
        double r, g, b;
        iss >> r >> g >> b;
        _specularColor = Color(r * 255, g * 255, b * 255);
    } else if (key == "Ns") {
        float shininess;
        iss >> shininess;
        _shininess = shininess;
    }
}

const Color &AMaterial::getDiffuseColor() const { return _diffuseColor; }
const Color &AMaterial::getSpecularColor() const { return _specularColor; }
void AMaterial::setDiffuseColor(const Color &color) { _diffuseColor = color; }
void AMaterial::setSpecularColor(const Color &color) { _specularColor = color; }
void AMaterial::setShininess(float shininess) { _shininess = shininess; }

Color AMaterial::getColorAt(const Math::Point &) const
{
    return _diffuseColor;
}

float AMaterial::getTransparency() const {
    return _transparency;
}

float AMaterial::getRefractionIndex() const {
    return _refractionIndex;
}

void AMaterial::setTransparency(float transparency) {
    _transparency = transparency;
}

void AMaterial::setRefractionIndex(float refractionIndex) {
    _refractionIndex = refractionIndex;
}
