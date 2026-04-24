/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Gui
*/

/**
 * @file Gui.hpp
 * @brief GUI class header file.
 * @details This file contains the definition of the GUI class,
 *      which is used to manage the graphical user interface in the raytracer project.
 * @note The GUI class is responsible for rendering the scene in SFML and handling user interactions.
 */
#pragma once

#include "Color.hpp"
#include "Define.hpp"
#include "Camera.hpp"
#include "Cursor.hpp"

class Gui {
    public:

        /**
         * @brief Default constructor for Gui class.
         * Initializes the GUI with default settings.
         * @note This constructor can be used to create a GUI with default values.
         */
        Gui() = default;

        /**
         * @brief Constructor for Gui class.
         * @param width The width of the window.
         * @param height The height of the window.
         * Initializes the GUI with default settings.
         */
        Gui(int width, int height);

        /**
         * @brief Destructor for Gui class.
         * Cleans up resources used by the GUI.
         */
        ~Gui();

        /**
         * @brief Handles user input in the GUI.
         * Processes events such as keyboard and mouse input.
         */
        void handleInput(int& eventKey);

        /**
         * @brief Updates the scene in the GUI.
         * Updates the scene based on the rendered pixels
         */
        void updateScene(std::vector<Color> &pixelsRender, std::vector<Color> &pixelsFastRender);

        /**
         * @brief Creates the image from the pixels.
         * @param image The image to create.
         * @param pixels The pixels to use for the image.
         * @param width The width of the image.
         * @param height The height of the image.
         * @note This function is used to create the image from the pixels.
         */
        void createImage(sf::Image &image, const std::vector<Color> &pixels, int width, int height);

        /**
         * @brief Renders the scene in the GUI.
         * Draws the scene to the window.
         */
        void renderScene(int& eventKey);

        /**
         * @brief Renders a single frame in the GUI.
         * Draws the scene to the window for one frame.
         */
        void renderFrame(int& eventKey);

        /**
         * @brief Checks if the window is open.
         * @return True if the window is open, false otherwise.
         */
        bool isOpen() const;

    private:

        int _width;
        int _height;
        int _fastWidth;
        int _fastHeight;

        bool _isOpen;
        sf::RenderWindow _window;
        sf::Event _event;

        std::vector<Color> _pixelsRender;
        std::vector<Color> _pixelsFastRender;

        sf::Image _renderImage;
        sf::Texture _renderTexture;
        sf::Sprite _renderSprite;
        sf::Image _fastRenderImage;
        sf::Texture _fastRenderTexture;
        sf::Sprite _fastRenderSprite;

        sf::Vector2i _prevMousPos;
        sf::Font _font;

        // TRANSFORMATION
        std::vector<std::shared_ptr<Cursor>> _transfomationCursors;
        std::shared_ptr<Cursor> _translateX;
        std::shared_ptr<Cursor> _translateY;
        std::shared_ptr<Cursor> _translateZ;
        std::shared_ptr<Cursor> _rotateX;
        std::shared_ptr<Cursor> _rotateY;
        std::shared_ptr<Cursor> _rotateZ;
};
