/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Main
*/

/**
 * @file Main.cpp
 * @brief Main file for the raytracer project.
 */
#include "Core.hpp"
#include "Define.hpp"
#include "Exception.hpp"

/**
 * @brief Display the help message.
 * @return 0 on success.
 */
int help()
{
    std::cout << "USAGE: ";
    std::cout << "./raytracer <SCENE_FILE>" << std::endl;
    std::cout << "\tSCENE_FILE:";
    std::cout << "scene configuration" << std::endl;
    return 0;
}

/**
 * @brief Main function.
 * @param ac Number of arguments.
 * @param av Array of arguments.
 * @return 0 on success.
 * @return 84 on failure.
 * @note This function is the entry point of the program.
 */
int main(int ac, char **av)
{
    try {
        if (ac != 2)
            throw RaytracerException("Invalid number of arguments, try ./raytracer -help for more information");
        if (strcmp(av[1], "-help") == 0)
            return help();

        Core core;
        core.init(av[1]);
        core.loop();
    }
    catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}
