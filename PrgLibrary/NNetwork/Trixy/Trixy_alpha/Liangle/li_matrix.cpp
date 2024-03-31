#include "li_matrix.h"
#include "vector.h"

Matrix::Matrix() : data(nullptr), M(0), N(0)
{
}

Matrix::~Matrix()
{
    delete[] data;
}

Matrix::Matrix(std::size_t m, std::size_t n) : data(new Vector [m]), M(m), N(n)
{
    for (std::size_t i = 0; i < m; ++i)
        data[i] = Vector(n);
}

Matrix::Matrix(const Matrix& matrix)
    : data(new Vector [matrix.M]), M(matrix.M), N(matrix.N)
{
    for(std::size_t i = 0; i < M; ++i)
        data[i] = Vector(N);

    for(std::size_t i = 0; i < M; ++i)
            data[i] = matrix.data[i];
}

Matrix::Matrix(Matrix&& matrix) : data(matrix.data), M(matrix.M), N(matrix.N)
{
    matrix.data = nullptr;
}

Matrix::Matrix(const std::initializer_list<Vector>& list)
    : data(new Vector [list.size()]), M(list.size()), N(list.begin()->size())
{
    for(std::size_t i = 0; i < M; ++i)
        data[i] = Vector(N);

    std::size_t i = 0;
    for(const auto& row: list)
    {
        data[i] = row;
        ++i;
    }
}

Matrix& Matrix::operator= (const Matrix& matrix)
{
    if(this == &matrix)
        return *this;

    delete[] data;

    M = matrix.M;
    N = matrix.N;

    data = new Vector [M];
    for(std::size_t i = 0; i < M; ++i)
        data[i] = Vector(N);

    for(std::size_t i = 0; i < M; ++i)
        data[i] = matrix(i);

    return *this;
}

Matrix& Matrix::operator= (Matrix&& matrix)
{
    if(this == &matrix)
        return *this;

    delete[] data;

    data = matrix.data;
    M = matrix.M;
    N = matrix.N;

    matrix.data = nullptr;

    return *this;
}

Matrix& Matrix::operator= (const std::initializer_list<Vector>& list)
{
    delete[] data;

    M = list.size();
    N = list.begin()->size();

    data = new Vector [M];
    for(std::size_t i = 0; i < M; ++i)
        data[i] = Vector(N);

    std::size_t i = 0;
    for(const auto& row: list)
    {
        data[i] = row;
        ++i;
    }

    return *this;
}

std::size_t Matrix::row() const { return M; }
std::size_t Matrix::col() const { return N; }

Matrix& Matrix::reshape(std::size_t m, std::size_t n)
{
    delete[] data;

    M = m;
    N = n;
    data = new Vector [M];
    for(std::size_t i = 0; i < M; ++i)
        data[i] = Vector(N);

    return *this;
}

Matrix& Matrix::fill(double (*generator)())
{
    for(std::size_t i = 0; i < M; ++i)
        data[i].fill(generator());

    return *this;
}
Matrix& Matrix::fill(double value)
{
    for(std::size_t i = 0; i < M; ++i)
        data[i].fill(value);

    return *this;
}

Matrix Matrix::produce(double (*function)(double)) const
{
    Matrix new_matrix(M, N);
    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            new_matrix(i, j) = function(data[i](j));

    return new_matrix;
}
Matrix& Matrix::modify(double (*function)(double))
{
    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            data[i](j) = function(data[i](j));

    return *this;
}

double& Matrix::operator() (std::size_t i, std::size_t j)
{
    return data[i](j);
}
const double& Matrix::operator() (std::size_t i, std::size_t j) const
{
    return data[i](j);
}
Vector& Matrix::operator() (std::size_t i)
{
    return data[i];
}
const Vector& Matrix::operator() (std::size_t i) const
{
    return data[i];
}

Matrix Matrix::dot(const Matrix& matrix) const
{
    Matrix new_matrix(M, matrix.N);
    double result = 0.0;

    for(std::size_t i = 0; i < M; ++i)
    {
        for(std::size_t j = 0; j <  matrix.N; ++j)
        {
            for(std::size_t r = 0; r < N; ++r)
                result += data[i](r) * matrix(r, j);

            new_matrix(i, j) = result;
            result = 0.0;
        }
    }

    return new_matrix;
}
Vector Matrix::dot_T(const Vector& vector) const
{
    Vector new_vector(M);
    double result = 0.0;

    for(std::size_t i = 0; i < M; ++i)
    {
        for(std::size_t j = 0; j < N; ++j)
            result += data[i](j) * vector(j);

        new_vector(i) = result;
        result = 0.0;
    }

    return new_vector;
}
Matrix Matrix::join(const Matrix& matrix) const
{
    Matrix new_matrix(M, N);

    for(std::size_t i = 0; i < M; ++i)
        new_matrix(i) = data[i].join(matrix(i));

    return new_matrix;
}
Matrix Matrix::join(const Vector& vector) const
{
    Matrix new_matrix(M, N);

    for(std::size_t i = 0; i < M; ++i)
            new_matrix(i) = data[i].join(vector);

    return new_matrix;
}

Matrix Matrix::T() const
{
    Matrix new_matrix(N, M);

    for(std::size_t i = 0; i < N; ++i)
        for(std::size_t j = 0; j < M; ++j)
            new_matrix(i, j) = data[j](i);

    return new_matrix;
}

Matrix Matrix::operator+ (const Matrix& matrix) const
{
    Matrix new_matrix(M, N);

    for(std::size_t i = 0; i < M; ++i)
        new_matrix.data[i] = data[i] + matrix.data[i];

    return new_matrix;
}
Matrix Matrix::operator- (const Matrix& matrix) const
{
    Matrix new_matrix(M, N);

    for(std::size_t i = 0; i < M; ++i)
        new_matrix.data[i] = data[i] - matrix.data[i];

    return new_matrix;
}
Matrix& Matrix::operator+= (const Matrix& matrix)
{
    for(std::size_t i = 0; i < M; ++i)
        data[i] += matrix.data[i];

    return *this;
}
Matrix& Matrix::operator-= (const Matrix& matrix)
{
    for(std::size_t i = 0; i < M; ++i)
        data[i] -= matrix.data[i];

    return *this;
}
Matrix& Matrix::operator- ()
{
    for(std::size_t i = 0; i < M; ++i)
        data[i] = -data[i];

    return *this;
}

Matrix operator* (const Matrix& matrix, double val)
{
    Matrix new_matrix(matrix.M, matrix.N);

    for(std::size_t i = 0; i < matrix.M; ++i)
        new_matrix.data[i] = val * matrix(i);

    return new_matrix;
}
Matrix operator* (double val, const Matrix& matrix)
{
    return matrix * val;
}
std::ostream& operator<< (std::ostream& out, const Matrix& matrix)
{
    out << '[';
    for(std::size_t i = 0; i < matrix.M - 1; ++i)
        std::cout << matrix(i) << ", ";

    out << matrix(matrix.M - 1) << ']';

    return out;
}
