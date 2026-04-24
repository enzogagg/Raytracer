/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cursor
*/

#include "Cursor.hpp"

Cursor::Cursor(std::pair<double, double> percentageStartLine, std::pair<double, double> percentageFinishLine,
    int width, int height, const sf::Font& font, std::string cursorTitleText)
{
    _posCursor = 0;
    _isCursorSelected = false;
    sf::Vector2f _startLine = {
        static_cast<float>(static_cast<double>(width) * percentageStartLine.first / 100),
        static_cast<float>(static_cast<double>(height) * percentageStartLine.second / 100)
    };
    sf::Vector2f _finishLine = {
        static_cast<float>(static_cast<double>(width) * percentageFinishLine.first / 100),
        static_cast<float>(static_cast<double>(height) * percentageFinishLine.second / 100)
    };
    initShape(_startLine, _finishLine);
    initText(font, _startLine, _finishLine, cursorTitleText);
    _keyToPressed[TRANSLATE_X] = std::pair<sf::Keyboard::Key, sf::Keyboard::Key>({ sf::Keyboard::Right, sf::Keyboard::Left });
    _keyToPressed[TRANSLATE_Y] = std::pair<sf::Keyboard::Key, sf::Keyboard::Key>({ sf::Keyboard::Up, sf::Keyboard::Down });
    _keyToPressed[TRANSLATE_Z] = std::pair<sf::Keyboard::Key, sf::Keyboard::Key>({ sf::Keyboard::I, sf::Keyboard::O });
    _keyToPressed[ROTATE_X] = std::pair<sf::Keyboard::Key, sf::Keyboard::Key>({ sf::Keyboard::X, sf::Keyboard::X });
    _keyToPressed[ROTATE_Y] = std::pair<sf::Keyboard::Key, sf::Keyboard::Key>({ sf::Keyboard::Y, sf::Keyboard::Y });
    _keyToPressed[ROTATE_Z] = std::pair<sf::Keyboard::Key, sf::Keyboard::Key>({ sf::Keyboard::Z, sf::Keyboard::Z });
}

/**
 * @brief Initialise all the text of the cursor
 * @param font The font for all the text of the cursor
 * @param _startLine position of the starting line of the cursor
 * @param _finishLine position of the finish line of the cursor
 * @param cursorTitleText The title of the cursor
 */
void Cursor::initText(const sf::Font& font, sf::Vector2f _startLine,
        sf::Vector2f _finishLine, std::string cursorTitleText)
{
    _cursorText.setPosition({_finishLine.x + 15, _finishLine.y - 12});
    _cursorText.setFont(font);
    _cursorText.setCharacterSize(24);
    _cursorText.setFillColor(sf::Color::White);
    _cursorText.setStyle(sf::Text::Bold);
    if (cursorTitleText == TRANSLATE_X || cursorTitleText == TRANSLATE_Y ||
        cursorTitleText == TRANSLATE_Z) {
        _cursorText.setString(std::to_string(_posCursor) + "px");
        _type = CursorType::TRANSLATE;
    } else {
        _cursorText.setString(std::to_string(_posCursor) + "deg");
        _type = CursorType::ROTATE;
    }
    _cursorTitleText.setPosition({_startLine.x, _startLine.y + 12});
    _cursorTitleText.setFont(font);
    _cursorTitleText.setCharacterSize(24);
    _cursorTitleText.setFillColor(sf::Color::White);
    _cursorTitleText.setStyle(sf::Text::Bold);
    _cursorTitleText.setString(cursorTitleText);
}

/**
 * @brief Initialise the shape of the cursor
 * @param _startLine position of the starting line of the cursor
 * @param _finishLine position of the finish line of the cursor
 */
void Cursor::initShape(sf::Vector2f _startLine, sf::Vector2f _finishLine)
{

    _cursorLine = {
        sf::Vertex{ _startLine },
        sf::Vertex{ _finishLine }
    };
    _cursorShape = sf::RectangleShape({20.f, 20.f});
    sf::Vector2f CursorTranslatXorigin = {
        _cursorShape.getGlobalBounds().left + _cursorShape.getGlobalBounds().width / 2.f,
        _cursorShape.getGlobalBounds().top + _cursorShape.getGlobalBounds().height / 2.f,
    };
    _cursorShape.setOrigin(CursorTranslatXorigin);
    _cursorShape.setPosition(
        _startLine.x + ((_finishLine.x - _startLine.x) / 2),
        _startLine.y + ((_finishLine.y - _startLine.y) / 2)
    );
    _cursorShape.setFillColor(sf::Color::Red);
    _cursorShape.setOutlineColor(sf::Color::Red);
}

Cursor::~Cursor()
{
}

/**
 * @brief get the Text of the cursor
 * @return the Text of the cursor
 */
sf::Text Cursor::getText() const
{
    return _cursorText;
}

/**
 * @brief get the title text of the cursor
 * @return the title text of the cursor
 */
sf::Text Cursor::getCursorTitleText() const
{
    return _cursorTitleText;
}

/**
 * @brief get the rectangle shape of the cursor
 * @return the rectangle shape of the cursor
 */
sf::RectangleShape Cursor::getRectangle() const
{
    return _cursorShape;
}

/**
 * @brief get the cursor line of the cursor
 * @return the array of vertex reprensenting the cursor line of the cursor
 */
std::array<sf::Vertex, 2> Cursor::getCursorLine() const
{
    return _cursorLine;
}

/**
 * @brief get the position of the cursor
 * @return the position of the cursor
 */
int Cursor::getPosCursor() const
{
    return _posCursor;
}

/**
 * @brief check if the cursor is selected
 * @return true or false :)
 */
bool Cursor::isCursorSelected() const
{
    return _isCursorSelected;
}

/**
 * @brief set if the cursors is selected of not
 * @param cursorSelected boolean to switch mode
 */
void Cursor::setCursorSelected(const bool cursorSelect)
{
    _isCursorSelected = cursorSelect;
}

/**
 * @brief move the cursor position by an offset
 * @param offset value to move the cursor
 */
void Cursor::moveCursor(const int offset)
{
    _posCursor += offset;
}

/**
 * @brief set the text of the cursors
 * @param cursorsText text to set
 * @note it's mainly remind the user by how many pixel he moves the scene
 * @note it use the position of the cursor
 */
void Cursor::setCursorText(const std::string cursorsText)
{
    _cursorText.setString(cursorsText);
}

/**
 * @brief move the rectangle shape along the cursor axis
 * @param offset pair to move the rectangle to
 */
void Cursor::moveRectangleShape(const sf::Vector2f offset)
{
    _cursorShape.move(offset);
}

/**
 * @brief getter for the type of the cursor
 */
CursorType Cursor::getType() const
{
    return _type;
}

/**
 * @brief if the cursor is selected, update all the value to it
 * @param mousePos current position of the mouse to compare with the previous
 * @param prevMoussPos previous position of the mouse
 * @param eventKey tell the program to move to a direction
 * @return the update position of the mouse
 */
sf::Vector2i Cursor::updateCursor(sf::Vector2i mousePos, sf::Vector2i prevMousePos, int& eventKey)
{
    if (_isCursorSelected) {
        sf::FloatRect posCursorTranslatX = _cursorShape.getGlobalBounds();
        float offsetX = static_cast<float>(mousePos.x - prevMousePos.x);
        if (mousePos.x < prevMousePos.x) {
            eventKey = _keyToPressed[_cursorTitleText.getString()].first;
            if (posCursorTranslatX.left > _cursorLine.front().position.x) {
                _cursorShape.move({ offsetX, 0.f });
                _posCursor += (static_cast<int>(offsetX));
            }
        }
        if (mousePos.x > prevMousePos.x) {
            eventKey = _keyToPressed[_cursorTitleText.getString()].second;
            float maxWidth = _cursorLine.front().position.x +
                (_cursorLine.back().position.x - _cursorLine.front().position.x);
            if ((posCursorTranslatX.left + posCursorTranslatX.width / 2) < maxWidth) {
                _cursorShape.move({ offsetX, 0.f });
                _posCursor += (static_cast<int>(offsetX));
            }
        }
        prevMousePos = mousePos;
    }
    return prevMousePos;
}

/**
 * @brief Check if the cursor as been selected by the user using the mouse
 * button
 * @param prevMousPos Previous position of the mouse
 */
void Cursor::mouseClickedOnCursor(sf::Vector2i &prevMousPos)
{
    sf::FloatRect posCursor = _cursorShape.getGlobalBounds();
    if (sf::Mouse::getPosition().x > posCursor.left &&
        sf::Mouse::getPosition().x < (posCursor.left + posCursor.width) &&
        (sf::Mouse::getPosition().y - 35) > posCursor.top &&
        (sf::Mouse::getPosition().y - 35) < (posCursor.top + posCursor.height)) {
        _isCursorSelected = true;
        prevMousPos = sf::Mouse::getPosition();
    }
}
