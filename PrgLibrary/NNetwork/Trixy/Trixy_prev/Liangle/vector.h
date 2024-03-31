#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <iostream>

class Matrix;

class Vector
{
private:
    double* data;
    std::size_t N;

public:
    Vector();
    ~Vector();
    Vector(std::size_t n);
    Vector(const Vector&);
    Vector(Vector&&);
    Vector(const std::initializer_list<double>&);

    Vector& operator= (const Vector&);
    Vector& operator= (Vector&&);
    Vector& operator= (const std::initializer_list<double>&);

    std::size_t size() const;
    Vector& resize(std::size_t n);

    double& operator() (std::size_t i);
    const double& operator() (std::size_t i) const;

    void fill(double (*generator)());
    Vector produce(double (*function)(double)) const;
    Vector& modify(double (*function)(double));

    Vector dot(const Matrix&) const;//
    Vector dot_T(const Matrix&) const;//
    double dot_T(const Vector&) const;
    Vector join(const Vector&) const;
    Matrix join(const Matrix&) const;//
    Matrix tensordot_T(const Vector&) const;//

    Vector operator+ (const Vector&) const;
    Vector operator- (const Vector&) const;
    Vector& operator+= (const Vector&);
    Vector& operator-= (const Vector&);
    Vector& operator- ();

    friend Vector operator* (const Vector&, double);
    friend Vector operator* (double, const Vector&);
    friend std::ostream& operator<< (std::ostream&, const Vector&);
};

#endif // VECTOR_H
