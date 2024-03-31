//
// Created by Jason Fedorowich on 2024-03-12.
//

#ifndef ODINMATH_MATRIX_H
#define ODINMATH_MATRIX_H

#include "odinmath.h"

namespace OdinMath{

    template<int ROW_SIZE, int COL_SIZE, typename real>
    class Matrix{
    protected:
        real mat[ROW_SIZE][COL_SIZE];
    public:
        virtual real& operator()(int row, int col);
        virtual const real& operator()(int row, int col) const;

        virtual real* getRow(int r){
            if(r < 0) throw InvalidArgument("Row must be greater than 0");
            if(r >= ROW_SIZE) throw InvalidArgument("Row cannot be greater than ROW_SIZE");
            return mat[r];
        }
        virtual real* getCol(int c){
            if(c < 0) throw InvalidArgument("Col must be greater than 0");
            if(c >= COL_SIZE) throw InvalidArgument("Col cannot be greater that COL_SIZE");
            real col[ROW_SIZE];
            for(int i = 0; i < ROW_SIZE; i++){
                col[i] = mat[i][c];
            }
            return col;
        }

        virtual ~Matrix() = default;

    };

    template<int ROW_SIZE, int COL_SIZE, typename real>
    const real &Matrix<ROW_SIZE, COL_SIZE, real>::operator()(int row, int col) const {
        if(row < 0 || row >= ROW_SIZE || col < 0 || col >= COL_SIZE) throw InvalidArgument("Invalid argument passed to index");
        return mat[row][col];
    }

    template<int ROW_SIZE, int COL_SIZE, typename real>
    real &Matrix<ROW_SIZE, COL_SIZE, real>::operator()(int row, int col) {
        if(row < 0 || row >= ROW_SIZE || col < 0 || col >= COL_SIZE) throw InvalidArgument("Invalid argument passed to index");
        return mat[row][col];
    }

}


#endif //ODINMATH_MATRIX_H
