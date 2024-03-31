#include "vector.h"
#include "matrix.h"

Vector::Vector() : data(nullptr), N(0)
{
}
Vector::~Vector()
{
    delete[] data;
}
Vector::Vector(std::size_t n) : data(new double[n]), N(n)
{
}
Vector::Vector(const Vector& vector) : data(new double[vector.N]), N(vector.N)
{
    for(std::size_t i = 0; i < N; ++i)
        data[i] = vector.data[i];
}
Vector::Vector(Vector&& vector) : data(vector.data), N(vector.N)
{
    vector.data = nullptr;
}
Vector::Vector(const std::initializer_list<double>& list)
    : data(new double[list.size()]), N(list.size())
{
    std::size_t i = 0;
    for(const auto& arg: list)
    {
        data[i] = arg;
        ++i;
    }
}

Vector& Vector::operator= (const Vector& vector)
{
    if(this == &vector)
        return *this;

    delete[] data;

    N = vector.N;
    data = new double[N];

    for(std::size_t i = 0; i < N; ++i)
        data[i] = vector.data[i];

    return *this;
}
Vector& Vector::operator= (Vector&& vector)
{
    if(this == &vector)
        return *this;

    delete[] data;

    N = vector.N;
    data = vector.data;

    vector.data = nullptr;

    return *this;
}
Vector& Vector::operator= (const std::initializer_list<double>& list)
{
    delete[] data;

    N = list.size();
    data = new double[N];

    std::size_t i = 0;
    for(const auto& arg: list)
    {
        data[i] = arg;
        ++i;
    }

    return *this;
}

std::size_t Vector::size() const { return N; }

double& Vector::operator() (std::size_t i) { return data[i]; }
const double& Vector::operator() (std::size_t i) const { return data[i]; }

void Vector::fill(double (*generator)())
{
    for(std::size_t i = 0; i < N; ++i)
        data[i] = generator();
}
Vector Vector::produce(double (*function)(double)) const
{
    Vector new_vector(N);
    for(std::size_t i = 0; i < N; ++i)
        new_vector.data[i] = function(data[i]);

    return new_vector;
}
Vector& Vector::modify(double (*function)(double))
{
    for(std::size_t i = 0; i < N; ++i)
        data[i] = function(data[i]);

    return *this;
}

Vector Vector::T_dot(const Matrix& matrix) const
{
    Vector new_vector(matrix.col());
    double result = 0.0;

    for(std::size_t i = 0; i < matrix.col(); ++i)
    {
        for(std::size_t j = 0; j <  matrix.row(); ++j)
        {
            result += data[j] * matrix(j, i);
        }
        new_vector(i) = result;
        result = 0.0;
    }

    return new_vector;
}
double Vector::T_dot(const Vector& vector) const
{
    double result = 0.0;

    for(std::size_t i = 0; i < N; ++i)
        result += data[i] * vector(i);

    return result;
}
Vector Vector::join(const Vector& vector) const
{
    Vector new_vector(N);

    for(std::size_t i = 0; i < N; ++i)
        new_vector(i) = data[i] * vector.data[i];

    return new_vector;
}
Matrix Vector::join(const Matrix& matrix) const
{
    Matrix new_matrix(matrix.row(), matrix.col());

    for(std::size_t i = 0; i < matrix.row(); ++i)
        for(std::size_t j = 0; j < matrix.col(); ++j)
            new_matrix(i, j) = data[i] * matrix(i, j);

    return new_matrix;
}
Matrix Vector::tensordot_T(const Vector& vector) const
{
    Matrix new_matrix(N, vector.N);

    for(std::size_t i = 0; i < N; ++i)
        for(std::size_t j = 0; j < vector.N; ++j)
            new_matrix(i, j) = data[i] * vector.data[j];

    return new_matrix;
}

Vector Vector::operator+ (const Vector& vector) const
{
    Vector new_vector(N);

    for(std::size_t i = 0; i  < N; ++i)
        new_vector(i) = data[i] + vector.data[i];

    return new_vector;
}
Vector Vector::operator- (const Vector& vector) const
{
    Vector new_vector(N);

    for(std::size_t i = 0; i  < N; ++i)
        new_vector(i) = data[i] - vector.data[i];

    return new_vector;
}
Vector& Vector::operator+= (const Vector& vector)
{
    for(std::size_t i = 0; i  < N; ++i)
        data[i] += vector.data[i];

    return *this;
}
Vector& Vector::operator-= (const Vector& vector)
{
     for(std::size_t i = 0; i  < N; ++i)
        data[i] -= vector.data[i];

    return *this;
}
Vector& Vector::operator- ()
{
    for(std::size_t i = 0; i  < N; ++i)
        data[i] = -data[i];

    return *this;
}

Vector operator* (const Vector& vector, double k)
{
    Vector new_vector(vector.N);

    for(std::size_t i = 0; i < vector.N; ++i)
        new_vector.data[i] = vector.data[i] * k;

    return new_vector;
}
Vector operator* (double k, const Vector& vector)
{
    return vector * k;
}
std::ostream& operator<< (std::ostream& out, const Vector& vector)
{
    out << '[';
    for(std::size_t i = 0; i < vector.N - 1; ++i)
        out << vector(i) << ", ";

    out << vector(vector.N - 1) << ']';

    return out;
}
