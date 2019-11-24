#include "matrix.h"

Matrix::Matrix()
{
    _data.resize(4);
    for (auto &row: _data) {
        row.resize(4);
    }
}

void Matrix::fillMatrixWZeros()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            set(i, j, 0.);
        }
    }
}

double Matrix::get(size_t i, size_t j) const
{
    return _data[i][j];
}

void Matrix::set(size_t i, size_t j, double value)
{
    _data[i][j] = value;
}


