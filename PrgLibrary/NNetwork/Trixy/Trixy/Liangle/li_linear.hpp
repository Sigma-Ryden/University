#ifndef LI_LINEAR_H
#define LI_LINEAR_H

#include <cstddef>

namespace liangle
{

class Linear
{
public:
    template <template <typename...> class Matrix, template <typename...> class Vector, typename... Args>
    static Vector<Args...> dot(const Vector<Args...>& vector, const Matrix<Args...>& matrix);

    template <template <typename...> class Matrix, template <typename...> class Vector, typename... Args>
    static Vector<Args...> dot_t(const Vector<Args...>& vector, const Matrix<Args...>& matrix);

    template <template <typename...> class Matrix, template <typename...> class Vector, typename... Args>
    static Matrix<Args...> join(const Matrix<Args...>& matrix, const Vector<Args...>& vector);

    template <class Matrix, template <typename...> class Vector, typename... Args>
    static Matrix tensordot(const Vector<Args...>& a, const Vector<Args...>& b);

    template <class Vector, template <typename...> class Matrix, typename... Args>
    static Vector get(const Matrix<Args...>& matrix, std::size_t n_row);

    template <template <typename...> class Matrix, class Function, typename... Args>
    static void fill_matrix(Matrix<Args...>& matrix, Function generator);

    template <template <typename...> class Vector, class Function, typename... Args>
    static void fill_vector(Vector<Args...>& vector, Function generator);

    template <template <typename...> class Matrix, class Function, typename... Args>
    static Matrix<Args...> apply_to_matrix(const Matrix<Args...>& matrix, Function function);

    template <template <typename...> class Vector, class Function, typename... Args>
    static Vector<Args...> apply_to_vector(const Vector<Args...>& vector, Function function);

    template <template <typename...> class Matrix, class Function, typename... Args>
    static Matrix<Args...>& modify_matrix(Matrix<Args...>& matrix, Function function);

    template <template <typename...> class Vector, class Function, typename... Args>
    static Vector<Args...>& modify_vector(Vector<Args...>& vector, Function function);
};

template <template <typename...> class Matrix, template <typename...> class Vector, typename... Args>
Vector<Args...> Linear::dot(const Vector<Args...>& vector, const Matrix<Args...>& matrix)
{
    Vector<Args...> new_vector(matrix.col());
    double result = 0.0;

    for(std::size_t i = 0; i < matrix.col(); ++i)
    {
        for(std::size_t j = 0; j <  matrix.row(); ++j)
            result += vector(j) * matrix(j, i);

        new_vector(i) = result;
        result = 0.0;
    }

    return new_vector;
}

template <template <typename...> class Matrix, template <typename...> class Vector, typename... Args>
Vector<Args...> Linear::dot_t(const Vector<Args...>& vector, const Matrix<Args...>& matrix)
{
    Vector<Args...> new_vector(matrix.row());
    double result = 0.0;

    for(std::size_t i = 0; i < matrix.row(); ++i)
    {
        for(std::size_t j = 0; j <  matrix.col(); ++j)
            result += vector(j) * matrix(i, j);

        new_vector(i) = result;
        result = 0.0;
    }

    return new_vector;
}

template <template <typename...> class Matrix, template <typename...> class Vector, typename... Args>
Matrix<Args...> Linear::join(const Matrix<Args...>& matrix, const Vector<Args...>& vector)
{
    Matrix<Args...> new_matrix(matrix.row(), matrix.col());

    for(std::size_t i = 0; i < matrix.row(); ++i)
        for(std::size_t j = 0; j < matrix.col(); ++j)
            new_matrix(i, j) = vector(j) * matrix(i, j);

    return new_matrix;
}

template <class Matrix, template <typename...> class Vector, typename... Args>
Matrix Linear::tensordot(const Vector<Args...>& a, const Vector<Args...>& b)
{
    Matrix new_matrix(b.size(), a.size());

    for(std::size_t i = 0; i < b.size(); ++i)
        for(std::size_t j = 0; j < a.size(); ++j)
            new_matrix(i, j) = a(j) * b(i);

    return new_matrix;
}

template <class Vector, template <typename...> class Matrix, typename... Args>
Vector Linear::get(const Matrix<Args...>& matrix, std::size_t n_row)
{
    Vector new_vector(matrix.col());

    for(std::size_t i = 0; i < matrix.col(); ++i)
        new_vector(i) = matrix(n_row, i);

    return new_vector;
}

template <template <typename...> class Matrix, class Function, typename... Args>
void Linear::fill_matrix(Matrix<Args...>& matrix, Function generator)
{
    for(std::size_t i = 0; i < matrix.row(); ++i)
        for(std::size_t j = 0; j < matrix.col(); ++j)
            matrix(i, j) = generator();
}

template <template <typename...> class Vector, class Function, typename... Args>
void Linear::fill_vector(Vector<Args...>& vector, Function generator)
{
    for(std::size_t i = 0; i < vector.size(); ++i)
        vector(i) = generator();
}

template <template <typename...> class Matrix, class Function, typename... Args>
Matrix<Args...> Linear::apply_to_matrix(const Matrix<Args...>& matrix, Function function)
{
    Matrix<Args...> new_matrix(matrix.row(), matrix.col());

    for(std::size_t i = 0; i < matrix.row(); ++i)
        for(std::size_t j = 0; j < matrix.col(); ++j)
            new_matrix(i, j) = function(matrix(i, j));

    return new_matrix;
}

template <template <typename...> class Vector, class Function, typename... Args>
Vector<Args...> Linear::apply_to_vector(const Vector<Args...>& vector, Function function)
{
    Vector<Args...> new_vector(vector.size());

    for(std::size_t i = 0; i < vector.size(); ++i)
        new_vector(i) = function(vector(i));

    return new_vector;
}

template <template <typename...> class Matrix, class Function, typename... Args>
Matrix<Args...>& Linear::modify_matrix(Matrix<Args...>& matrix, Function function)
{
    for(std::size_t i = 0; i < matrix.row(); ++i)
        for(std::size_t j = 0; j < matrix.col(); ++j)
            matrix(i, j) = function(matrix(i, j));

    return matrix;
}

template <template <typename...> class Vector, class Function, typename... Args>
Vector<Args...>& Linear::modify_vector(Vector<Args...>& vector, Function function)
{
    for(std::size_t i = 0; i < vector.size(); ++i)
            vector(i) = function(vector(i));

    return vector;
}

}
#endif // LI_LINEAR_H
