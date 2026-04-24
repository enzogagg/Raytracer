/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Matrix
*/

/**
 * @file Matrix.cpp
 * @brief Matrix class implementation.
 * @details This file contains the implementation of the Matrix class
 * @note The Matrix class represents a Matrix and allow us to proceed to multiple
 * calculs.
 */
#pragma once

namespace Math {
    /**
     * @class Matrix
     * @brief A class to use Matrix for calculus
     * @param X X represents the number of lines in the matrix
     * @param Y Y represents the number of columns in the matrix
     */
    template <unsigned int X, unsigned int Y>
    class Matrix {
        public:
            unsigned int _row;
            unsigned int _col;
            double _matrix[X][Y];

            /**
             * @brief Default constructor of the Matrix class
             * @note By default the Matrix is set to 0.0 for each value
             */
            Matrix()
                : _row(X), _col(Y)
            {
                for (unsigned int i = 0; i < X; i++) {
                    for (unsigned int j = 0; j < Y; j++) {
                        _matrix[i][j] = 0.0;
                    }
                }
            };

            /**
             * @brief Constructor of the Matrix class
             * @param matrix the matrix to copy
             */
            Matrix(double matrix[X][Y])
                : _row(X), _col(Y)
            {
                for (unsigned int i = 0; i < X; i++) {
                    for (unsigned int j = 0; j < Y; j++) {
                        _matrix[i][j] = matrix[i][j];
                    }
                }
            }

            /**
             * @brief Default destructor of the Matrix class
             */
            ~Matrix()
            {
            }

            /**
             * @brief Overload of the () operator: allow us to acces the value
             * inside the matrix
             * @param row row represents the row of the matrix you want to access
             * @param col col represents the col of the matrix you want to access
             *
             * @return the value at the row and the col passed as parameter
             */
            double &operator()(unsigned int row, unsigned int col)
            {
                if (row >= X || col >= Y)
                    throw std::out_of_range("Out of range");
                return this->_matrix[row][col];
            };

            /**
             * @brief Overload of the () operator: allow us to acces the value
             * inside the matrix
             * @param row row represents the row of the matrix you want to access
             * @param col col represents the col of the matrix you want to access
             *
             * @return a copy of the value at the row and the col passed as parameter
             */
            const double& operator()(unsigned int row, unsigned int col) const
            {
                if (row >= X || col >= Y)
                    throw std::out_of_range("Out of range");
                return _matrix[row][col];
            }

            /**
             * @brief Overload of the * operator: allow us to multiply two matrices
             * @param m2 the matrix that the current ones will be multiply by 
             *
             * @return an out of range exception if the multiply isn't possible
             * @return the result of the multiplication
             *
             * @note the x and y param represent the row and the cols of the matrix to be multiply
             * @note the X and Y represent the row and the cols of the current matrix
             * @note in the case where Y != x then the multiplication cannot be performed
             */
            template <unsigned int x, unsigned int y>
            Matrix<X, y> operator*(Matrix<x, y> const &m2)
            {
                Matrix<X, y> res;
                if (Y != x) {
                    throw std::out_of_range("Out of range");
                }
                for (unsigned int i = 0; i < this->getRow(); i++) {
                    for (unsigned int j = 0; j < m2.getCol(); j++) {
                        res(i, j) = 0;
                        for (unsigned int k = 0; k < m2.getRow(); k++) {
                            res._matrix[i][j] += this->_matrix[i][k] * m2._matrix[k][j];
                        }
                    }
                }
                return res;
            }

            /**
             * @brief get the number of row in the current matrix
             */
            unsigned int getRow() const {
                return _row;
            };

            /**
             * @brief get the number of columns in the current matrix
             */
            unsigned int getCol() const {
                return _col;
            };
        protected:
        private:
    };
}
