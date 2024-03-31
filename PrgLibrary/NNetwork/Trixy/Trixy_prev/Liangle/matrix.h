#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <initializer_list>
#include <iostream>

class Vector;

class Matrix
{
private:
    double** data;
    std::size_t M;
    std::size_t N;

public:
    Matrix();
    ~Matrix();
    Matrix(std::size_t m, std::size_t n);
    Matrix(const Matrix&);
    Matrix(Matrix&&);
    Matrix(const std::initializer_list<Vector>&);

    Matrix& operator= (const Matrix&);
    Matrix& operator= (Matrix&&);
    Matrix& operator= (const std::initializer_list<Vector>&);

    std::size_t row() const;
    std::size_t col() const;
    Matrix& reshape(std::size_t m, std::size_t n);

    Matrix& fill(double (*generator)());
    Matrix produce(double (*function)(double)) const;
    Matrix& modify(double (*function)(double));

    double& operator() (std::size_t i, std::size_t j);
    const double& operator() (std::size_t i, std::size_t j) const;
    Vector operator() (std::size_t i) const;

    Matrix dot(const Matrix&) const;
    Vector dot_T(const Vector&) const;//
    Matrix join(const Matrix&) const;
    Matrix join(const Vector&) const;//
    Matrix join_T(const Vector&) const;//
    Matrix T() const;

    Matrix& put(std::size_t row_position, const Vector&);//

    Matrix operator+ (const Matrix&) const;
    Matrix operator- (const Matrix&) const;
    Matrix& operator+= (const Matrix&);
    Matrix& operator-= (const Matrix&);
    Matrix& operator- ();

    friend Matrix operator* (const Matrix&, double val);
    friend Matrix operator* (double val, const Matrix&);
    friend std::ostream& operator<< (std::ostream&, const Matrix&);
};

#endif // MATRIX_H
