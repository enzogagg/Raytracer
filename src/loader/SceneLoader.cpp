/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** SceneLoader
*/

/**
 * @file SceneLoader.cpp
 * @brief SceneLoader class implementation.
 * @details This file contains the implementation of the SceneLoader class,
 *      which is used to load scenes from a configuration file in the raytracer project.
 * @note The SceneLoader class is responsible for parsing the scene configuration file
 *      and creating the necessary objects for rendering.
 */

#include "SceneLoader.hpp"
#include "ObjParser.hpp"

/**
 * @brief Load a scene from a file.
 * @param filename The name of the file to load the scene from.
 * @return A pointer to the loaded Scene object.
 */
Scene SceneLoader::parseSceneFile(const std::string &filename)
{
    libconfig::Config configFile;
    Scene scene;

    try {
        configFile.readFile(filename.c_str());
        const libconfig::Setting &root = configFile.getRoot();

        if (root.exists("camera")) {
            try {
                parseSceneCamera(root["camera"], scene);
            } catch (const std::exception &e) {
                std::cerr << "Error parsing camera: " << e.what() << std::endl;
                return scene; // Retourne une scène vide ou partielle
            }
        } else {
            std::cerr << "Camera section is missing in the configuration file." << std::endl;
            return scene;
        }
        if (root.exists("primitive")) {
            try {
                parseScenePrimitive(root["primitive"], scene);
            } catch (const std::exception &e) {
                std::cerr << "Error parsing primitives: " << e.what() << std::endl;
            }
        }
        if (root.exists("light")) {
            try {
                parseSceneLight(root["light"], scene);
            } catch (const std::exception &e) {
                std::cerr << "Error parsing lights: " << e.what() << std::endl;
            }
        }
    } catch (const libconfig::ParseException &e) {
        std::cerr << "Parse error at " << e.getFile() << ":" << e.getLine()
                  << " - " << e.getError() << std::endl;
    } catch (const libconfig::SettingException &e) {
        std::cerr << "Setting error: " << e.getPath() << " - " << e.what() << std::endl;
    } catch (const libconfig::FileIOException &e) {
        std::cerr << "I/O error while reading file: " << filename << " - " << e.what() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while parsing the scene file." << std::endl;
    }
    return scene;
}

/**
 * @brief Parse the scene file and create the camera.
 * @param file The file to parse.
 * @param scene The scene object to fill.
 */
void SceneLoader::parseSceneCamera(const libconfig::Setting &file,
    Scene &scene)
{
    int width = 0, height = 0;
    if (file.exists("resolution")) {
        const libconfig::Setting &resolution = file["resolution"];
        resolution.lookupValue("width", width);
        resolution.lookupValue("height", height);
    }

    auto getdoubleOrInt = [](const libconfig::Setting &s) -> double {
        if (s.getType() == libconfig::Setting::TypeFloat)
            return static_cast<double>(s);
        if (s.getType() == libconfig::Setting::TypeInt)
            return static_cast<double>(static_cast<int>(s));
        throw std::runtime_error("Value is not a number");
    };

    Math::Vector position;
    if (file.exists("position")) {
        const libconfig::Setting &pos = file["position"];
        if (pos.exists("x") && pos.exists("y") && pos.exists("z")) {
            position = Math::Vector(
                getdoubleOrInt(pos["x"]),
                getdoubleOrInt(pos["y"]),
                getdoubleOrInt(pos["z"])
            );
        } else {
            throw SceneException("Invalid or missing position values in the configuration file.");
        }
    } else {
        throw SceneException("Position not found in the configuration file.");
    }

    Math::Vector rotation;
    if (file.exists("rotation")) {
        const libconfig::Setting &rot = file["rotation"];
        if (rot.exists("x") && rot.exists("y") && rot.exists("z")) {
            rotation = Math::Vector(
                getdoubleOrInt(rot["x"]),
                getdoubleOrInt(rot["y"]),
                getdoubleOrInt(rot["z"])
            );
        } else {
            throw SceneException("Invalid or missing rotation values in the configuration file.");
        }
    } else {
        throw SceneException("Rotation not found in the configuration file.");
    }

    double fov = 0.0f;
    if (file.exists("fieldOfView")) {
        const libconfig::Setting &fovSetting = file["fieldOfView"];
        fov = fovSetting.isNumber() ? fovSetting : static_cast<double>(fovSetting);
    } else {
        throw SceneException("Field of view (fieldOfView) not found in the configuration file.");
    }

    Camera camera(position, rotation, fov, width, height);
    scene.addCamera(camera);
}

/**
 * @brief Parse the scene file and create the primitive.
 * @param file The file to parse.
 * @param scene The scene object to fill.
 */
void SceneLoader::parseScenePrimitive(const libconfig::Setting &file,
    Scene &scene)
{
    for (int i = 0; i < file.getLength(); ++i) {
        const libconfig::Setting &group = file[i];
        std::string key = group.getName();

        for (int j = 0; j < group.getLength(); ++j) {
            const libconfig::Setting &primitiveSetting = group[j];

            try {
                if (key == "obj") {
                    std::string filepath;
                    if (!primitiveSetting.lookupValue("path", filepath)) {
                        throw std::runtime_error("Missing 'path' field for .obj primitive.");
                    }
                    auto primitives = ObjParser::parse(filepath);
                    for (const auto &primitive : primitives) {
                        if (primitive) {
                            scene.addPrimitive(primitive);
                        } else {
                            std::cerr << "[SceneLoader] Ignored null primitive from OBJ parsing." << std::endl;
                        }
                    }
                } else {
                    auto primitive = PluginsManager::createPrimitive(key, primitiveSetting);
                    if (primitive) {
                        scene.addPrimitive(primitive);
                    } else {
                        std::cerr << "[SceneLoader] Ignored null primitive for type '" << key << "'." << std::endl;
                    }
                }
            } catch (const std::runtime_error &e) {
                std::cerr << "Error creating primitive of type '" << key
                << "': " << e.what() << std::endl;
            }
        }
    }
}

/**
 * @brief Parse the scene file and create the light.
 * @param file The file to parse.
 * @param scene The scene object to fill.
 */
void SceneLoader::parseSceneLight(const libconfig::Setting &file, Scene &scene)
{
    // if (file.exists("ambient")) {
    //     auto ambient = PluginsManager::createLight("ambient", file["ambient"]);
    //     if (ambient) {
    //         scene.addLight(ambient);
    //     } else {
    //         std::cerr << "[SceneLoader] Ignored null light for type 'ambient'." << std::endl;
    //     }
    // }

    if (file.exists("diffuse")) {
        double diffuse = 0.0f;
        const libconfig::Setting &diffuseSetting = file["diffuse"];
        if (diffuseSetting.getType() == libconfig::Setting::TypeFloat) {
            diffuse = static_cast<double>(diffuseSetting);
        } else if (diffuseSetting.getType() == libconfig::Setting::TypeInt) {
            diffuse = static_cast<double>(static_cast<int>(diffuseSetting));
        } else {
            throw SceneException("Invalid diffuse light value in the configuration file.");
        }
        scene.setDiffuse(diffuse);
    }

    for (int i = 0; i < file.getLength(); ++i) {
        const libconfig::Setting &group = file[i];
        std::string key = group.getName();

        if (key == "diffuse") // || key == "ambient")
            continue;

        for (int j = 0; j < group.getLength(); ++j) {
            const libconfig::Setting &lightSetting = group[j];
            try {
                auto light = PluginsManager::createLight(key, lightSetting);
                if (light) {
                    scene.addLight(light);
                } else {
                    std::cerr << "[SceneLoader] Ignored null light for type '" << key << "'." << std::endl;
                }
            } catch (const std::exception &e) {
                std::cerr << "Error creating light of type '" << key
                << "': " << e.what() << std::endl;
            }
        }
    }
}
