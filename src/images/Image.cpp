/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Image
*/

/**
 * @file Image.cpp
 * @brief Image class implementation.
 * @details This file contains the implementation of the Image class,
 *      which is used to represent an image in the raytracer project.
 * @note The Image class is used to store pixel data and save the image to a file.
 */
#include "Image.hpp"

/**
 * @brief Default constructor for Image class.
 * Initializes the image with default settings.
 * @param width The width of the image.
 * @param height The height of the image.
 * @param pixels The vector of pixels to use for the image.
 */
Image::Image(int width, int height, std::vector<Color> &pixels)
    : _width(width), _height(height), _pixels(pixels)
{
    return;
}

/**
 * @brief Destructor for Image class.
 * Cleans up resources used by the image.
 * @note This destructor is called when the image object is destroyed.
 */
Image::~Image()
{
    return;
}

/**
 * @brief Create the directory and the file name.
 * @param filename The name of the file to save the image to.
 * @note This function creates a directory for screenshots and generates a unique file name.
 * @return The path to the created file.
 */
std::filesystem::path Image::createDirAndFileName(const std::string &filename)
{
    std::filesystem::path screenshotsDir = "./screenshots";
    if (!std::filesystem::exists(screenshotsDir)) {
        std::filesystem::create_directory(screenshotsDir);
    }
    std::ostringstream initialFilename;
    initialFilename << filename << "_" << std::setw(3) << std::setfill('0') << 0 << ".ppm";
    std::filesystem::path filePath = screenshotsDir / initialFilename.str();
    int counter = 1;
    while (std::filesystem::exists(filePath)) {
        std::ostringstream newFilename;
        newFilename << filename << "_" << std::setw(3) << std::setfill('0') << counter << ".ppm";
        filePath = screenshotsDir / newFilename.str();
        counter++;
    }
    return filePath;
}

/**
 * @brief Save the image to a file.
 * @param filename The name of the file to save the image to.
 * @note This function saves the image to a file in PNG format.
 */
void Image::save(const std::string &filename)
{
    std::filesystem::path filePath = createDirAndFileName(filename);
    std::ofstream file(filePath, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + filePath.string());
    }
    file << "P3\n" << _width << " " << _height << "\n255\n";
    for (const auto &pixel : _pixels) {
        file << static_cast<int>(pixel.getR()) << " "
             << static_cast<int>(pixel.getG()) << " "
             << static_cast<int>(pixel.getB()) << "\n";
        }

     file.close();
}