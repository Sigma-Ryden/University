#ifndef LI_VECTOR_HPP
#define LI_VECTOR_HPP

#include <initializer_list>
#include <iostream>
#include <cstddef>

namespace liangle
{

template <typename Type>
class Vector
{
private:
    Type* data;
    std::size_t N;

public:
    Vector();
    ~Vector();
    Vector(std::size_t n);
    Vector(const Vector&);
    Vector(Vector&&);
    Vector(const std::initializer_list<Type>&);

    Vector& operator= (const Vector&);
    Vector& operator= (Vector&&);
    Vector& operator= (const std::initializer_list<Type>&);

    std::size_t size() const;
    Vector& resize(std::size_t n);

    Type& operator() (std::size_t i);
    const Type& operator() (std::size_t i) const;

    Vector& fill(Type (*generator)());
    Vector& fill(Type value);

    Vector apply(Type (*function)(Type)) const;
    Vector& modify(Type (*function)(Type));

    Type dot(const Vector&) const;
    Vector join(const Vector&) const;
    Vector join(Type value) const;

    Vector operator+ (const Vector&) const;
    Vector operator- (const Vector&) const;
    Vector& operator+= (const Vector&);
    Vector& operator-= (const Vector&);

    template<typename T>
    friend std::ostream& operator<< (std::ostream&, const Vector<T>&); // deprecated
};

template <typename Type>
Vector<Type>::Vector() : data(nullptr), N(0)
{
}

template <typename Type>
Vector<Type>::~Vector()
{
    delete[] data;
}

template <typename Type>
Vector<Type>::Vector(std::size_t n) : data(new Type[n]), N(n)
{
}

template <typename Type>
Vector<Type>::Vector(const Vector& vector) : data(new Type[vector.N]), N(vector.N)
{
    for(std::size_t i = 0; i < N; ++i)
        data[i] = vector.data[i];
}

template <typename Type>
Vector<Type>::Vector(Vector&& vector) : data(vector.data), N(vector.N)
{
    vector.data = nullptr;
}

template <typename Type>
Vector<Type>::Vector(const std::initializer_list<Type>& list)
    : data(new Type[list.size()]), N(list.size())
{
    std::size_t i = 0;
    for(const auto& arg: list)
    {
        data[i] = arg;
        ++i;
    }
}

template <typename Type>
Vector<Type>& Vector<Type>::operator= (const Vector& vector)
{
    if(this == &vector)
        return *this;

    delete[] data;

    N = vector.N;
    data = new Type[N];

    for(std::size_t i = 0; i < N; ++i)
        data[i] = vector.data[i];

    return *this;
}

template <typename Type>
Vector<Type>& Vector<Type>::operator= (Vector&& vector)
{
    if(this == &vector)
        return *this;

    delete[] data;

    N = vector.N;
    data = vector.data;

    vector.data = nullptr;

    return *this;
}

template <typename Type>
Vector<Type>& Vector<Type>::operator= (const std::initializer_list<Type>& list)
{
    delete[] data;

    N = list.size();
    data = new Type[N];

    std::size_t i = 0;
    for(const auto& arg: list)
    {
        data[i] = arg;
        ++i;
    }

    return *this;
}

template <typename Type>
std::size_t Vector<Type>::size() const { return N; }

template <typename Type>
Vector<Type>& Vector<Type>::resize(std::size_t n)
{
    delete[] data;

    N = n;
    data = new Type[N];

    return *this;
}

template <typename Type>
Type& Vector<Type>::operator() (std::size_t i) { return data[i]; }

template <typename Type>
const Type& Vector<Type>::operator() (std::size_t i) const { return data[i]; }

template <typename Type>
Vector<Type>& Vector<Type>::fill(Type (*generator)())
{
    for(std::size_t i = 0; i < N; ++i)
        data[i] = generator();

    return *this;
}

template <typename Type>
Vector<Type>& Vector<Type>::fill(Type value)
{
    for(std::size_t i = 0; i < N; ++i)
        data[i] = value;

    return *this;
}

template <typename Type>
Vector<Type> Vector<Type>::apply(Type (*function)(Type)) const
{
    Vector new_vector(N);

    for(std::size_t i = 0; i < N; ++i)
        new_vector.data[i] = function(data[i]);

    return new_vector;
}

template <typename Type>
Vector<Type>& Vector<Type>::modify(Type (*function)(Type))
{
    for(std::size_t i = 0; i < N; ++i)
        data[i] = function(data[i]);

    return *this;
}

template <typename Type>
Type Vector<Type>::dot(const Vector& vector) const
{
    double result = 0.0;

    for(std::size_t i = 0; i < N; ++i)
        result += data[i] * vector(i);

    return result;
}

template <typename Type>
Vector<Type> Vector<Type>::join(const Vector& vector) const
{
    Vector new_vector(N);

    for(std::size_t i = 0; i < N; ++i)
        new_vector(i) = data[i] * vector.data[i];

    return new_vector;
}

template <typename Type>
Vector<Type> Vector<Type>::join(Type value) const
{
    Vector new_vector(N);

    for(std::size_t i = 0; i < N; ++i)
        new_vector(i) = data[i] * value;

    return new_vector;
}

template <typename Type>
Vector<Type> Vector<Type>::operator+ (const Vector& vector) const
{
    Vector new_vector(N);

    for(std::size_t i = 0; i  < N; ++i)
        new_vector(i) = data[i] + vector.data[i];

    return new_vector;
}

template <typename Type>
Vector<Type> Vector<Type>::operator- (const Vector& vector) const
{
    Vector new_vector(N);

    for(std::size_t i = 0; i  < N; ++i)
        new_vector(i) = data[i] - vector.data[i];

    return new_vector;
}

template <typename Type>
Vector<Type>& Vector<Type>::operator+= (const Vector& vector)
{
    for(std::size_t i = 0; i  < N; ++i)
        data[i] += vector.data[i];

    return *this;
}

template <typename Type>
Vector<Type>& Vector<Type>::operator-= (const Vector& vector)
{
     for(std::size_t i = 0; i  < N; ++i)
        data[i] -= vector.data[i];

    return *this;
}

template <typename Type>
std::ostream& operator<< (std::ostream& out, const Vector<Type>& vector)
{
    out << '[';
    for(std::size_t i = 0; i < vector.N - 1; ++i)
        out << vector(i) << ", ";

    out << vector(vector.N - 1) << ']';

    return out;
}

}
#endif // LI_VECTOR_HPP
