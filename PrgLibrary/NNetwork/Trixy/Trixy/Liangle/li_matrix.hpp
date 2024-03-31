#ifndef LI_MATRIX_HPP
#define LI_MATRIX_HPP

#include <initializer_list>
#include <iostream>
#include <cstddef>

namespace liangle
{

template <typename Type> class Vector;

template <typename Type>
class Matrix
{
private:
    Type** data;
    std::size_t M;
    std::size_t N;

public:
    Matrix();
    ~Matrix();
    Matrix(std::size_t m, std::size_t n);
    Matrix(const Matrix&);
    Matrix(Matrix&&);
    Matrix(const std::initializer_list<Vector<Type>>&);

    Matrix& operator= (const Matrix&);
    Matrix& operator= (Matrix&&);
    Matrix& operator= (const std::initializer_list<Vector<Type>>&);

    std::size_t row() const;
    std::size_t col() const;
    Matrix& resize(std::size_t m, std::size_t n);

    Matrix& fill(Type (*generator)());
    Matrix& fill(Type value);

    Matrix apply(Type (*function)(Type)) const;
    Matrix& modify(Type (*function)(Type));

    Type& operator() (std::size_t i, std::size_t j);
    const Type& operator() (std::size_t i, std::size_t j) const;

    Matrix dot(const Matrix&) const;
    Matrix join(const Matrix&) const;
    Matrix join(Type value) const;
    Matrix transpose() const;

    Matrix operator+ (const Matrix&) const;
    Matrix operator- (const Matrix&) const;
    Matrix& operator+= (const Matrix&);
    Matrix& operator-= (const Matrix&);

    template<typename T>
    friend std::ostream& operator<< (std::ostream&, const Matrix<T>&); // deprecated
};

template <typename Type>
Matrix<Type>::Matrix() : data(nullptr), M(0), N(0)
{
}

template <typename Type>
Matrix<Type>::~Matrix()
{
    if(data != nullptr)
    {
        for(std::size_t i = 0; i < M; ++i)
            delete[] data[i];
        delete[] data;
    }
}

template <typename Type>
Matrix<Type>::Matrix(std::size_t m, std::size_t n) : data(new Type* [m]), M(m), N(n)
{
    for(std::size_t i = 0; i < M; ++i)
        data[i] = new Type[N];
}

template <typename Type>
Matrix<Type>::Matrix(const Matrix& matrix)
    : data(new Type* [matrix.M]), M(matrix.M), N(matrix.N)
{
    for(std::size_t i = 0; i < M; ++i)
        data[i] = new Type[N];

    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            data[i][j] = matrix.data[i][j];
}

template <typename Type>
Matrix<Type>::Matrix(Matrix&& matrix) : data(matrix.data), M(matrix.M), N(matrix.N)
{
    matrix.data = nullptr;
}

template <typename Type>
Matrix<Type>::Matrix(const std::initializer_list<Vector<Type>>& list)
    : data(new Type* [list.size()]), M(list.size()), N(list.begin()->size())
{
    for(std::size_t i = 0; i < M; ++i)
        data[i] = new Type[N];

    std::size_t i = 0;
    for(const auto& row: list)
    {
        for(std::size_t j = 0; j < N; ++j)
            data[i][j] = row(j);
        ++i;
    }
}

template <typename Type>
Matrix<Type>& Matrix<Type>::operator= (const Matrix& matrix)
{
    if(this == &matrix)
        return *this;

    if(data != nullptr)
    {
        for(std::size_t i = 0; i < M; ++i)
            delete[] data[i];
        delete[] data;
    }

    M = matrix.M;
    N = matrix.N;

    data = new Type* [M];
    for(std::size_t i = 0; i < M; ++i)
        data[i] = new Type[N];

    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            data[i][j] = matrix.data[i][j];

    return *this;
}

template <typename Type>
Matrix<Type>& Matrix<Type>::operator= (Matrix&& matrix)
{
    if(this == &matrix)
        return *this;

    if(data != nullptr)
    {
        for(std::size_t i = 0; i < M; ++i)
            delete[] data[i];
        delete[] data;
    }

    data = matrix.data;
    M = matrix.M;
    N = matrix.N;

    matrix.data = nullptr;

    return *this;
}

template <typename Type>
Matrix<Type>& Matrix<Type>::operator= (const std::initializer_list<Vector<Type>>& list)
{
    if(data != nullptr)
    {
        for(std::size_t i = 0; i < M; ++i)
            delete[] data[i];
        delete[] data;
    }

    M = list.size();
    N = list.begin()->size();

    data = new Type* [M];
    for(std::size_t i = 0; i < M; ++i)
        data[i] = new Type[N];

    std::size_t i = 0;
    for(const auto& row: list)
    {
        for(std::size_t j = 0; j < N; ++j)
            data[i][j] = row(j);
        ++i;
    }

    return *this;
}

template <typename Type>
std::size_t Matrix<Type>::row() const
{
    return M;
}

template <typename Type>
std::size_t Matrix<Type>::col() const
{
    return N;
}

template <typename Type>
Matrix<Type>& Matrix<Type>::resize(std::size_t m, std::size_t n)
{
    if(data != nullptr)
    {
        for(std::size_t i = 0; i < M; ++i)
            delete[] data[i];
        delete[] data;
    }

    M = m;
    N = n;
    data = new Type* [M];
    for(std::size_t i = 0; i < M; ++i)
        data[i] = new Type[N];

    return *this;
}

template <typename Type>
Matrix<Type>& Matrix<Type>::fill(Type (*generator)())
{
    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            data[i][j] = generator();

    return *this;
}

template <typename Type>
Matrix<Type>& Matrix<Type>::fill(Type value)
{
    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            data[i][j] = value;

    return *this;
}

template <typename Type>
Matrix<Type> Matrix<Type>::apply(Type (*function)(Type)) const
{
    Matrix new_matrix(M, N);

    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            new_matrix.data[i][j] = function(data[i][j]);

    return new_matrix;
}

template <typename Type>
Matrix<Type>& Matrix<Type>::modify(Type (*function)(Type))
{
    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            data[i][j] = function(data[i][j]);

    return *this;
}

template <typename Type>
Type& Matrix<Type>::operator() (std::size_t i, std::size_t j)
{
    return data[i][j];
}

template <typename Type>
const Type& Matrix<Type>::operator() (std::size_t i, std::size_t j) const
{
    return data[i][j];
}

template <typename Type>
Matrix<Type> Matrix<Type>::dot(const Matrix& matrix) const
{
    Matrix new_matrix(M, matrix.N);
    Type result = 0.0;

    for(std::size_t i = 0; i < M; ++i)
    {
        for(std::size_t j = 0; j <  matrix.N; ++j)
        {
            for(std::size_t r = 0; r < N; ++r)
                result += data[i][r] * matrix.data[r][j];

            new_matrix.data[i][j] = result;
            result = 0.0;
        }
    }

    return new_matrix;
}

template <typename Type>
Matrix<Type> Matrix<Type>::join(const Matrix& matrix) const
{
    Matrix new_matrix(M, N);

    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            new_matrix.data[i][j] = data[i][j] * matrix.data[i][j];

    return new_matrix;
}

template <typename Type>
Matrix<Type> Matrix<Type>::join(Type value) const
{
    Matrix<Type> new_matrix(M, N);

    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            new_matrix.data[i][j] = data[i][j] * value;

    return new_matrix;
}

template <typename Type>
Matrix<Type> Matrix<Type>::transpose() const
{
    Matrix new_matrix(N, M);

    for(std::size_t i = 0; i < N; ++i)
        for(std::size_t j = 0; j < M; ++j)
            new_matrix.data[i][j] = data[j][i];

    return new_matrix;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator+ (const Matrix& matrix) const
{
    Matrix new_matrix(M, N);

    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            new_matrix.data[i][j] = data[i][j] + matrix.data[i][j];

    return new_matrix;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator- (const Matrix& matrix) const
{
    Matrix new_matrix(M, N);

    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            new_matrix.data[i][j] = data[i][j] - matrix.data[i][j];

    return new_matrix;
}

template <typename Type>
Matrix<Type>& Matrix<Type>::operator+= (const Matrix& matrix)
{
    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            data[i][j] += matrix.data[i][j];

    return *this;
}

template <typename Type>
Matrix<Type>& Matrix<Type>::operator-= (const Matrix& matrix)
{
    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            data[i][j] -= matrix.data[i][j];

    return *this;
}

template <typename Type>
std::ostream& operator<< (std::ostream& out, const Matrix<Type>& matrix)
{
    out << '[';
    for(std::size_t i = 0; i < matrix.M - 1; ++i)
    {
        out << '[';
        for(std::size_t j = 0; j < matrix.N - 1; ++j)
            out << matrix(i, j) << ", ";

        out << matrix(i, matrix.N - 1) << "], ";
    }

    out << '[';
    for(std::size_t j = 0; j < matrix.N - 1; ++j)
        out << matrix(matrix.M - 1, j) << ", ";

    out << matrix(matrix.M - 1, matrix.N - 1) << "]]";

    return out;
}

}
#endif // LI_MATRIX_HPP
