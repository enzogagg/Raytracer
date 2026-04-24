/*
** EPITECH PROJECT, 2025
** Sans titre(Espace de travail)
** File description:
** Gui
*/

/**
 * @file Gui.cpp
 * @brief GUI class implementation file.
 * @details This file contains the implementation of the GUI class,
 *      which is used to manage the graphical user interface in the raytracer project.
 * @note The GUI class is responsible for rendering the scene in SFML and handling user interactions.
 */
#include "Gui.hpp"


/**
 * @brief Default constructor for Gui class.
 * Initializes the GUI with default settings.
 * @note This constructor can be used to create a GUI with default values.
 */
Gui::Gui(int width, int height)
    : _width(width), _height(height), _isOpen(false)
{
    _font.loadFromFile(FONT);
    _fastWidth = _width * FAST_RENDER_RATIO;
    _fastHeight = _height * FAST_RENDER_RATIO;
    _window.create(sf::VideoMode(width, height), "Raytracer");
    _window.setFramerateLimit(60);
    for (int i = 0; i < _width * _height; ++i)
        _pixelsRender.push_back(Color(0, 0, 0));
    for (int i = 0; i < static_cast<int>(_width * FAST_RENDER_RATIO) * static_cast<int>(_height * FAST_RENDER_RATIO); ++i)
        _pixelsFastRender.push_back(Color(0, 0, 0));

    _renderImage.create(_width, _height);
    _renderTexture.loadFromImage(_renderImage);
    _renderSprite = sf::Sprite(_renderTexture);

    _fastRenderImage.create(_fastWidth, _fastHeight);
    _fastRenderTexture.loadFromImage(_fastRenderImage);
    _fastRenderSprite = sf::Sprite(_fastRenderTexture);
    _fastRenderSprite.setPosition(0, 0);
    _translateX = std::make_shared<Cursor>(std::pair<float, float>({ 85.f, 5.f }), std::pair<float, float>({ 95.f, 5.f }), _width, _height, this->_font, TRANSLATE_X);
    _translateY = std::make_shared<Cursor>(std::pair<float, float>({ 85.f, 15.f }), std::pair<float, float>({ 95.f, 15.f }), _width, _height, this->_font, TRANSLATE_Y);
    _translateZ = std::make_shared<Cursor>(std::pair<float, float>({ 85.f, 25.f }), std::pair<float, float>({ 95.f, 25.f }), _width, _height, this->_font, TRANSLATE_Z);
    _rotateX = std::make_shared<Cursor>(std::pair<float, float>({ 85.f, 35.f }), std::pair<float, float>({ 95.f, 35.f }), _width, _height, this->_font, ROTATE_X);
    _rotateY = std::make_shared<Cursor>(std::pair<float, float>({ 85.f, 45.f }), std::pair<float, float>({ 95.f, 45.f }), _width, _height, this->_font, ROTATE_Y);
    _rotateZ = std::make_shared<Cursor>(std::pair<float, float>({ 85.f, 55.f }), std::pair<float, float>({ 95.f, 55.f }), _width, _height, this->_font, ROTATE_Z);
    _transfomationCursors.push_back(_translateX);
    _transfomationCursors.push_back(_translateY);
    _transfomationCursors.push_back(_translateZ);
    _transfomationCursors.push_back(_rotateX);
    _transfomationCursors.push_back(_rotateY);
    _transfomationCursors.push_back(_rotateZ);
    _prevMousPos = sf::Mouse::getPosition();
    return;
}

/**
 * @brief Destructor for Gui class.
 * Cleans up resources used by the GUI.
 * @note This destructor is called when the GUI object is destroyed.
 */
Gui::~Gui()
{
    _window.close();
    return;
}

/**
 * @brief Handles user input in the GUI.
 * Processes events such as keyboard and mouse input.
 */
void Gui::handleInput(int& eventKey)
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) {
            _window.close();
            _isOpen = false;
        }
        if (_event.type == sf::Event::KeyPressed) {
            if (_event.key.code == sf::Keyboard::S)
                eventKey = _event.key.code;
            eventKey = _event.key.code;
        }
        if (_event.type == sf::Event::KeyReleased)
            eventKey = -1;
        if (_event.type == sf::Event::MouseButtonPressed) {
            for (auto &cursor: _transfomationCursors)
                cursor->mouseClickedOnCursor(_prevMousPos);
        }
        if (_event.type == sf::Event::MouseButtonReleased) {
            for (auto &cursor: _transfomationCursors)
                if (cursor->isCursorSelected() == true)
                    cursor->setCursorSelected(false);
        }
    }

    for (auto &cursor: _transfomationCursors)
        _prevMousPos = cursor->updateCursor(sf::Mouse::getPosition(), _prevMousPos, eventKey);
}

/**
 * @brief Updates the scene in the GUI.
 * Updates the scene based on user input and other factors.
 */
void Gui::updateScene(std::vector<Color> &pixelsRender, std::vector<Color> &pixelsFastRender)
{
    _pixelsRender = pixelsRender;
    _pixelsFastRender = pixelsFastRender;
    return;
}

/**
 * @brief Creates the image from the pixels.
 * @param image The image to create.
 * @param pixels The pixels to use for the image.
 * @param width The width of the image.
 * @param height The height of the image.
 * @note This function is used to create the image from the pixels.
 */
void Gui::createImage(sf::Image &image, const std::vector<Color> &pixels, int width, int height)
{
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const Color &color = pixels[y * width + x];
            sf::Color sf_color(
                static_cast<sf::Uint8>(color.getR()),
                static_cast<sf::Uint8>(color.getG()),
                static_cast<sf::Uint8>(color.getB())
            );
            image.setPixel(x, y, sf_color);
        }
    }
}

/**
 * @brief Renders the scene in the GUI.
 * Draws the scene to the window.
 */
void Gui::renderScene(int& eventKey)
{
    while (_window.isOpen()) {
        renderFrame(eventKey);
    }
}

/**
 * @brief Renders a single frame in the GUI.
 * Draws the scene to the window for one frame.
 */
void Gui::renderFrame(int& eventKey)
{
    if (!_window.isOpen())
        return;
    handleInput(eventKey);
    _window.clear(sf::Color::Black);

    createImage(_renderImage, _pixelsRender, _width, _height);
    _renderTexture.update(_renderImage);

    createImage(_fastRenderImage, _pixelsFastRender, _fastWidth, _fastHeight);
    _fastRenderTexture.update(_fastRenderImage);

    sf::RectangleShape border(sf::Vector2f(_fastWidth, _fastHeight));
    border.setPosition(0, 0);
    border.setOutlineThickness(2);
    border.setOutlineColor(sf::Color::White);
    border.setFillColor(sf::Color::Transparent);

    _window.draw(_renderSprite);
    _window.draw(border);
    _window.draw(_fastRenderSprite);
    for (auto &cursor: _transfomationCursors) {
        if (cursor.get()->getType() == CursorType::TRANSLATE)
            cursor->setCursorText(std::to_string(cursor->getPosCursor()) + "px");
        else
            cursor->setCursorText(std::to_string(cursor->getPosCursor()) + "deg");
        _window.draw(cursor->getCursorLine().data(), cursor->getCursorLine().size(), sf::PrimitiveType::Lines);
        _window.draw(cursor->getRectangle());
        _window.draw(cursor->getText());
        _window.draw(cursor->getCursorTitleText());
    }
    _window.display();
}

/**
 * @brief Checks if the window is open.
 * @return True if the window is open, false otherwise.
 */
bool Gui::isOpen() const
{
    if (_window.isOpen())
        return true;
    return false;
}
