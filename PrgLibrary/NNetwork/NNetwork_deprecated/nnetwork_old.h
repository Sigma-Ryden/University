#ifndef NNETWORK_OLD_H
#define NNETWORK_OLD_H

#include <cmath>
#include <initializer_list>
#include "matrix.h"
#include "vector.h"

class NNetwork_old
{
private:
    double (*f_act)(double);
    double (*f_act_deriv)(double);

    Matrix W_ab;
    Matrix W_bc;
    Vector B_b;
    Vector B_c;

public:
    NNetwork_old(int, int, int);

    void initializeInnerStruct(double (*generator)());
    void setActivationFunction(double (*func)(double), double (*func_deriv)(double));

    Vector feedforward(const Vector&) const;
    double mean(const Matrix&, const Matrix&) const;

    void train(const Matrix& in, const Matrix& out, double learn_rate, double loss_rate);

    void show() const;
};

#endif // NNETWORK_OLD_H
