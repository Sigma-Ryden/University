#ifndef NNETWORK_H
#define NNETWORK_H

#include <cstddef>
#include <cmath>
#include <iostream>
#include <initializer_list>
#include "Liangle/liangle.h"
#include "Dictionary/dictionary.hpp"

class NNetwork
{
private:
    double (*F)(double);
    double (*DF)(double);

    Dictionary<Matrix> W;
    Dictionary<Vector> B;

    std::size_t N;

public:
    NNetwork(const std::initializer_list<std::size_t>& inner);

    void initializeInnerStruct(double (*generator)());
    void setActivationFunction(double (*function)(double), double (*function_derived)(double));

    const Dictionary<Matrix>& getInnerWeight() const { return W; }
    const Dictionary<Vector>& getInnerBias() const { return B; }

    Vector feedforward(const Vector&) const;

    void train(const Matrix& in, const Matrix& out, double learn_rate, std::size_t epoch_rate);

    void test(const Matrix& in, const Matrix& out) const; //

    void showInnerStruct() const; //

    double accuracy(const Matrix& in, const Matrix& out, double range_rate) const; //repair
    double loss(const Matrix& in, const Matrix& out) const; //repair

private:
    static double mean(const Matrix&, const Matrix&);
};

#endif // NNETWORK_H
