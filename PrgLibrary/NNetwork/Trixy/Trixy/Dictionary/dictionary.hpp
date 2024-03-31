#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <cstddef>
#include <memory>

template <typename T>
class Dictionary
{
private:
    std::unique_ptr<T[]> data;
    std::size_t N;

public:
    Dictionary();
    Dictionary(std::size_t N);
    Dictionary(const Dictionary<T>&);
    Dictionary(Dictionary<T>&&);
    Dictionary<T>& operator= (const Dictionary<T>&);
    Dictionary<T>& operator= (Dictionary<T>&&);

    std::size_t size() const;

    T& operator[] (std::size_t i);
    const T& operator[] (std::size_t i) const;
};

template <typename T>
Dictionary<T>::Dictionary() : data(nullptr), N(0)
{
}

template <typename T>
Dictionary<T>::Dictionary(std::size_t n) : data(new T [n]), N(n)
{
}

template <typename T>
Dictionary<T>::Dictionary(const Dictionary<T>& dictionary)
    : data(new T[dictionary.N]), N(dictionary.N)
{
    for(std::size_t i = 0; i < N; ++i)
        data[i] = dictionary[i];
}

template <typename T>
Dictionary<T>::Dictionary(Dictionary<T>&& dictionary)
{
    N = dictionary.N;
    data.reset(dictionary.data.release());
}

template <typename T>
Dictionary<T>& Dictionary<T>::operator= (const Dictionary<T>& dictionary)
{
    if(this == &dictionary)
        return *this;

    N = dictionary.N;
    data.reset(new T[N]);

    for(std::size_t i = 0; i < N; ++i)
        data[i] = dictionary.data[i];

    return *this;
}

template <typename T>
Dictionary<T>& Dictionary<T>::operator= (Dictionary<T>&& dictionary)
{
    if(this == &dictionary)
        return *this;

    N = dictionary.N;
    data.reset(dictionary.data.release());

    return *this;
}

template <typename T>
std::size_t Dictionary<T>::size() const
{
    return N;
}

template <typename T>
T& Dictionary<T>::operator[] (std::size_t i)
{
    return data[i];
}
template <typename T>
const T& Dictionary<T>::operator[] (std::size_t i) const
{
    return data[i];
}

#endif // DICTIONARY_HPP
