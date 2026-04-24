/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cursor
*/

#pragma once
#include "Define.hpp"

enum CursorType {
    TRANSLATE,
    ROTATE
};

class Cursor {
    public:
        Cursor(std::pair<double, double> percentageStartLine, std::pair<double, double> percentageFinishLine,
            int width, int height, const sf::Font& font, std::string cursorTitleText);
        ~Cursor();

        /**
         * @brief Initialise all the text of the cursor
         * @param font The font for all the text of the cursor
         * @param _startLine position of the starting line of the cursor
         * @param _finishLine position of the finish line of the cursor
         * @param cursorTitleText The title of the cursor
         */
        void initText(const sf::Font& font, sf::Vector2f _startLine,
            sf::Vector2f _finishLine, std::string cursorTitleText);

        /**
         * @brief Initialise the shape of the cursor
         * @param _startLine position of the starting line of the cursor
         * @param _finishLine position of the finish line of the cursor
         */
        void initShape(sf::Vector2f _startLine, sf::Vector2f _finishLine);

        /**
         * @brief get the Text of the cursor
         * @return the Text of the cursor
         */
        sf::Text getText() const;

        /**
         * @brief get the title text of the cursor
         * @return the title text of the cursor
         */
        sf::Text getCursorTitleText() const;

        /**
         * @brief get the rectangle shape of the cursor
         * @return the rectangle shape of the cursor
         */
        sf::RectangleShape getRectangle() const;

        /**
         * @brief get the cursor line of the cursor
         * @return the array of vertex reprensenting the cursor line of the cursor
         */
        std::array<sf::Vertex, 2> getCursorLine() const;

        /**
         * @brief get the position of the cursor
         * @return the position of the cursor
         */
        int getPosCursor() const;

        /**
         * @brief check if the cursor is selected
         * @return true or false :)
         */
        bool isCursorSelected() const;

        /**
         * @brief set if the cursors is selected of not
         * @param cursorSelected boolean to switch mode
         */
        void setCursorSelected(const bool cursorSelect);

        /**
         * @brief move the cursor position by an offset
         * @param offset value to move the cursor
         */
        void moveCursor(const int offset);

        /**
         * @brief set the text of the cursors
         * @param cursorsText text to set
         * @note it's mainly remind the user by how many pixel he moves the scene
         * @note it use the position of the cursor
         */
        void setCursorText(const std::string cursorsText);

        /**
         * @brief move the rectangle shape along the cursor axis
         * @param offset vector to move the rectangle
         */
        void moveRectangleShape(const sf::Vector2f offset);

        /**
         * @brief if the cursor is selected, update all the value to it
         * @param mousePos current position of the mouse to compare with the previous
         * @param prevMoussPos previous position of the mouse
         * @param eventKey tell the program to move to a direction
         * @return the update position of the mouse
         */
        sf::Vector2i updateCursor(sf::Vector2i mousePos, sf::Vector2i prevMousePos, int& eventKey);

        /**
         * @brief Check if the cursor as been selected by the user using the mouse
         * button
         * @param prevMousPos Previous position of the mouse
         */
        void mouseClickedOnCursor(sf::Vector2i &prevMousPos);

        /**
         * @brief getter for the type of the cursor
         */
        CursorType getType() const;

    protected:
    private:
        std::array<sf::Vertex, 2> _cursorLine;
        sf::RectangleShape _cursorShape;
        sf::Text _cursorText;
        sf::Text _cursorTitleText;
        int _posCursor;
        bool _isCursorSelected;
        CursorType _type;

        std::map<std::string, std::pair<sf::Keyboard::Key, sf::Keyboard::Key>> _keyToPressed;
};
