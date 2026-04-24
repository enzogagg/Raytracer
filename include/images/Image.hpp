/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Image
*/

/**
 * @file Image.hpp
 * @brief Image class header file.
 * @details This file contains the definition of the Image class,
 *      which is used to manage images in the raytracer project.
 * @note The Image class is responsible for generation and saving images.
 */
#pragma once

#include "Color.hpp"
#include "Define.hpp"

/**
 * @class Image
 * @brief A class to represent an image in the raytracer project.
 */
class Image {
    public:
        /**
         * @brief Default constructor for Image class.
         * Initializes the image with default settings.
         * @note This constructor can be used to create an image with default values.
         */
        Image(int width, int height, std::vector<Color> &pixels);

        /**
         * @brief Destructor for Image class.
         * Cleans up resources used by the image.
         * @note This destructor is called when the image object is destroyed.
         */
        ~Image();

        /**
         * @brief Create the dir and the file name.
         * @param filename The name of the file to save the image to.
         * @note This function creates a directory for screenshots
         *      and generates a unique file name.
         * @return The path to the created file.
         */
        std::filesystem::path createDirAndFileName(const std::string &filename);

        /**
         * @brief Save the image to a file.
         * @param filename The name of the file to save the image to.
         */
        void save(const std::string &filename);

    private:
        int _width;
        int _height;
        std::vector<Color> &_pixels;
};
