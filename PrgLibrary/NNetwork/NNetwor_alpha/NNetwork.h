#ifndef NNETWORK_H
#define NNETWORK_H

#include "Matrix.h"
#include "Vector.h"

class NNetwork
{
private:
    double (*f_act)(double);
    double (*f_act_deriv)(double);

    Matrix W_ab;
    Matrix W_bc;
    Vector B_b;
    Vector B_c;

public:
    NNetwork(int, int, int);

    void initializeInnerStruct(double (*generator)());
    void setActivationFunction(double (*func)(double), double (*func_deriv)(double));

    Vector feedforward(const Vector&) const;
    double mean(const Matrix&, const Matrix&) const;

    void train(const Matrix& in, const Matrix& out, double learn_rate, double loss_rate);

    void show() const;
};

#endif // NNETWORK_H
