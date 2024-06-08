//
// Created by Jason Fedorowich on 2024-03-12.
//

#ifndef ODINMATH_MATRIX_H
#define ODINMATH_MATRIX_H

#include "odinmath.h"

namespace OdinMath {

    template<int ROW_SIZE, int COL_SIZE, typename real>
    class Matrix {
    protected:
        real mat[ROW_SIZE][COL_SIZE];
    public:

        Matrix() = default;

        explicit Matrix(real matrix[ROW_SIZE][COL_SIZE]) {
            for (int i = 0; i < ROW_SIZE; i++) {
                for (int j = 0; j < COL_SIZE; j++) {
                    mat[i][j] = matrix[i][j];
                }
            }
        }

        virtual ~Matrix() = default;

        virtual real &operator()(int row, int col);

        virtual const real &operator()(int row, int col) const;

        virtual real *operator[](int row);

        virtual bool operator==(const Matrix<ROW_SIZE, COL_SIZE, real> &lhs) const;

        virtual real *getRow(int r) {
            if (r < 0) throw InvalidArgument("Row must be greater than 0");
            if (r >= ROW_SIZE) throw InvalidArgument("Row cannot be greater than ROW_SIZE");
            return mat[r];
        }

        virtual real *getCol(int c) {
            if (c < 0) throw InvalidArgument("Col must be greater than 0");
            if (c >= COL_SIZE) throw InvalidArgument("Col cannot be greater that COL_SIZE");
            real col[ROW_SIZE];
            for (int i = 0; i < ROW_SIZE; i++) {
                col[i] = mat[i][c];
            }
            return col;
        }


        struct Iterator {

            Matrix<ROW_SIZE, COL_SIZE, real> *matrix;
            int row;

            explicit Iterator(Matrix<ROW_SIZE, COL_SIZE, real> *matrix) : matrix(matrix), row(0) {}

            Iterator(const Iterator &it) { *this = it; }

            Iterator(Matrix<ROW_SIZE, COL_SIZE, real> *matrix, int row) : matrix(matrix), row(row) {}

            Iterator &operator++() {
                ++row;
                return *this;
            }

            Vector<COL_SIZE, real> operator*() { return Vector<COL_SIZE, real>(this->matrix->getRow(row)); }

            friend bool operator==(const Iterator &a, const Iterator &b) { return a.row == b.row; }

            friend bool operator!=(const Iterator &a, const Iterator &b) { return a.row != b.row; }

            Iterator &operator=(const Iterator &it) {
                if (this != &it) {
                    this->matrix = it.matrix;
                    this->row = it.row;
                }
                return *this;
            }

            virtual ~Iterator() = default;
        };

        Iterator begin() { return Iterator(this); }

        Iterator end() { return Iterator(this, ROW_SIZE); }
    };

    template<int ROW_SIZE, int COL_SIZE, typename real>
    bool Matrix<ROW_SIZE, COL_SIZE, real>::operator==(const Matrix<ROW_SIZE, COL_SIZE, real> &lhs) const {
        for (int i = 0; i < ROW_SIZE; i++) {
            for (int j = 0; j < COL_SIZE; j++) {
                if (this->mat[i][j] != lhs(i, j)) return false;
            }
        }
        return true;
    }

    template<int ROW_SIZE, int COL_SIZE, typename real>
    real *Matrix<ROW_SIZE, COL_SIZE, real>::operator[](int row) {
        if (row >= ROW_SIZE || row < 0)
            throw InvalidArgument("Invalid argument passed to index");
        return mat[row];
    }

    template<int ROW_SIZE, int COL_SIZE, typename real>
    const real &Matrix<ROW_SIZE, COL_SIZE, real>::operator()(int row, int col) const {
        if (row < 0 || row >= ROW_SIZE || col < 0 || col >= COL_SIZE)
            throw InvalidArgument("Invalid argument passed to index");
        return mat[row][col];
    }

    template<int ROW_SIZE, int COL_SIZE, typename real>
    real &Matrix<ROW_SIZE, COL_SIZE, real>::operator()(int row, int col) {
        if (row < 0 || row >= ROW_SIZE || col < 0 || col >= COL_SIZE)
            throw InvalidArgument("Invalid argument passed to index");
        return mat[row][col];
    }
};


#endif //ODINMATH_MATRIX_H
