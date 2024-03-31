#include "matrix.h"
#include "vector.h"

Matrix::Matrix() : data(nullptr), M(0), N(0)
{
}

Matrix::~Matrix()
{
    if(data != nullptr)
    {
        for(std::size_t i = 0; i < M; ++i)
            delete[] data[i];
        delete[] data;
    }
}

Matrix::Matrix(std::size_t m, std::size_t n) : data(new double* [m]), M(m), N(n)
{
    for(std::size_t i = 0; i < M; ++i)
        data[i] = new double[N];
}

Matrix::Matrix(const Matrix& matrix)
    : data(new double* [matrix.M]), M(matrix.M), N(matrix.N)
{
    for(std::size_t i = 0; i < M; ++i)
        data[i] = new double[N];

    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            data[i][j] = matrix.data[i][j];
}

Matrix::Matrix(Matrix&& matrix) : data(matrix.data), M(matrix.M), N(matrix.N)
{
    matrix.data = nullptr;
}

Matrix::Matrix(const std::initializer_list<Vector>& list)
    : data(new double* [list.size()]), M(list.size()), N(list.begin()->size())
{
    for(std::size_t i = 0; i < M; ++i)
        data[i] = new double[N];

    std::size_t i = 0;
    for(const auto& row: list)
    {
        for(std::size_t j = 0; j < N; ++j)
            data[i][j] = row(j);
        ++i;
    }
}

Matrix& Matrix::operator= (const Matrix& matrix)
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

    data = new double* [M];
    for(std::size_t i = 0; i < M; ++i)
        data[i] = new double[N];

    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            data[i][j] = matrix.data[i][j];

    return *this;
}

Matrix& Matrix::operator= (Matrix&& matrix)
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

Matrix& Matrix::operator= (const std::initializer_list<Vector>& list)
{
    if(data != nullptr)
    {
        for(std::size_t i = 0; i < M; ++i)
            delete[] data[i];
        delete[] data;
    }

    M = list.size();
    N = list.begin()->size();

    data = new double* [M];
    for(std::size_t i = 0; i < M; ++i)
        data[i] = new double[N];

    std::size_t i = 0;
    for(const auto& row: list)
    {
        for(std::size_t j = 0; j < N; ++j)
            data[i][j] = row(j);
        ++i;
    }

    return *this;
}

std::size_t Matrix::row() const { return M; }
std::size_t Matrix::col() const { return N; }

Matrix& Matrix::reshape(std::size_t m, std::size_t n)
{
    if(data != nullptr)
    {
        for(std::size_t i = 0; i < M; ++i)
            delete[] data[i];
        delete[] data;
    }

    M = m;
    N = n;
    data = new double* [M];
    for(std::size_t i = 0; i < M; ++i)
        data[i] = new double[N];

    return *this;
}

Matrix& Matrix::fill(double (*generator)())
{
    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            data[i][j] = generator();

    return *this;
}
Matrix& Matrix::fill(double value)
{
    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            data[i][j] = value;

    return *this;
}

Matrix Matrix::produce(double (*function)(double)) const
{
    Matrix new_matrix(M, N);
    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            new_matrix.data[i][j] = function(data[i][j]);

    return new_matrix;
}
Matrix& Matrix::modify(double (*function)(double))
{
    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            data[i][j] = function(data[i][j]);

    return *this;
}

double& Matrix::operator() (std::size_t i, std::size_t j)
{
    return data[i][j];
}
const double& Matrix::operator() (std::size_t i, std::size_t j) const
{
    return data[i][j];
}
Vector Matrix::operator() (std::size_t n) const
{
    Vector new_vector(N);

    for(std::size_t i = 0; i < N; ++i)
        new_vector(i) = data[n][i];

    return new_vector;
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
                result += data[i][r] * matrix.data[r][j];

            new_matrix.data[i][j] = result;
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
            result += data[i][j] * vector(j);

        new_vector(i) = result;
        result = 0.0;
    }

    return new_vector;
}
Matrix Matrix::join(const Matrix& matrix) const
{
    Matrix new_matrix(M, N);

    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            new_matrix.data[i][j] = data[i][j] * matrix.data[i][j];

    return new_matrix;
}
Matrix Matrix::join(const Vector& vector) const
{
    Matrix new_matrix(M, N);

    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            new_matrix.data[i][j] = data[i][j] * vector(j);

    return new_matrix;
}
Matrix Matrix::join_T(const Vector& vector) const
{
    Matrix new_matrix(M, N);

    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            new_matrix.data[i][j] = data[i][j] * vector(i);

    return new_matrix;
}
Matrix Matrix::T() const
{
    Matrix matrix_T(N, M);

    for(std::size_t i = 0; i < N; ++i)
        for(std::size_t j = 0; j < M; ++j)
            matrix_T.data[i][j] = data[j][i];

    return matrix_T;
}

Matrix& Matrix::put(std::size_t row_position, const Vector& vector)
{
    for(std::size_t i = 0; i < N; ++i)
        data[row_position][i] = vector(i);

    return *this;
}

Matrix Matrix::operator+ (const Matrix& matrix) const
{
    Matrix new_matrix(M, N);

    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            new_matrix.data[i][j] = data[i][j] + matrix.data[i][j];

    return new_matrix;
}
Matrix Matrix::operator- (const Matrix& matrix) const
{
    Matrix new_matrix(M, N);

    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            new_matrix.data[i][j] = data[i][j] - matrix.data[i][j];

    return new_matrix;
}
Matrix& Matrix::operator+= (const Matrix& matrix)
{
    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            data[i][j] += matrix.data[i][j];

    return *this;
}
Matrix& Matrix::operator-= (const Matrix& matrix)
{
    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            data[i][j] -= matrix.data[i][j];

    return *this;
}
Matrix& Matrix::operator- ()
{
    for(std::size_t i = 0; i < M; ++i)
        for(std::size_t j = 0; j < N; ++j)
            data[i][j] = -data[i][j];

    return *this;
}

Matrix operator* (const Matrix& matrix, double val)
{
    Matrix new_matrix(matrix.M, matrix.N);

    for(std::size_t i = 0; i < matrix.M; ++i)
        for(std::size_t j = 0; j < matrix.N; ++j)
            new_matrix.data[i][j] = val * matrix(i, j);

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
    {
        out << '[';
        for(std::size_t j = 0; j < matrix.N - 1; ++j)
            out << matrix(i, j) << ", ";

        out << matrix(i, matrix.N - 1) << "], ";
    }
    out << matrix(matrix.M - 1) << ']';

    return out;
}
