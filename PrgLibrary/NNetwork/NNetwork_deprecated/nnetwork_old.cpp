#include "nnetwork_old.h"

NNetwork_old::NNetwork_old(int a, int b, int c)
    : W_ab(a, b), W_bc(b, c), B_b(b), B_c(c)
{
}

void NNetwork_old::initializeInnerStruct(double (*generator)())
{
    W_ab.fill(generator);
    W_bc.fill(generator);
    B_b.fill(generator);
    B_c.fill(generator);
}
void NNetwork_old::setActivationFunction(double (*func)(double), double (*func_deriv)(double))
{
    f_act = func;
    f_act_deriv = func_deriv;
}

Vector NNetwork_old::feedforward(const Vector& in) const
{
    Vector H_b((W_ab.T_dot(in) + B_b).produce(f_act));
    Vector H_c((W_bc.T_dot(H_b) + B_c).produce(f_act));

    return H_c;
}

void NNetwork_old::train(const Matrix& in, const Matrix& out, double learn_rate, double loss_rate)
{
    Vector H_a;
    Vector H_b;
    Vector H_c;
    Vector Y_c;
    Vector S_b;
    Vector S_c;

    Vector DH_b;
    Vector DH_c;
    Matrix DW_ab;
    Matrix DW_bc;
    Vector DB_b;
    Vector DB_c;

    Matrix pred_out(in.row_size(), in.col_size());

    int min = 0;
    int max = in.row_size() - 1;
    int sample = 0;
    double loss = 1.0;

    for(int epoch = 0; loss > loss_rate; ++epoch)
    {
        sample = rand() % (max - min + 1) + min;

        H_a = in(sample);
        S_b = W_ab.T_dot(H_a) + B_b;
        H_b = S_b.produce(f_act);
        S_c = W_bc.T_dot(H_b) + B_c;
        H_c = S_c.produce(f_act);
        Y_c = H_c - out(sample);

        DH_b = S_b.produce(f_act_deriv);
        DH_c = S_c.produce(f_act_deriv);

        DW_ab = H_a.tensordot_T(DH_b).join_T(W_bc.dot(DH_c.join(Y_c)));
        DW_bc = H_b.tensordot_T(DH_c).join_T(Y_c);
        DB_b = DH_b.join(W_bc.dot(DH_c.join(Y_c)));
        DB_c = DH_c.join(Y_c);

        W_ab -= learn_rate * DW_ab;
        W_bc -= learn_rate * DW_bc;
        B_b -= learn_rate * DB_b;
        B_c -= learn_rate * DB_c;

        for(std::size_t i = 0; i < in.row_size(); ++i)
            pred_out.put(i, feedforward(in(i)));

        loss = mean(out, pred_out);

        //if(epoch % 1000 == 0) std::cout << "Epoch " << epoch << " loss: " << loss << '\n';
    }
}

double NNetwork_old::mean(const Matrix& y_true, const Matrix& y_pred) const
{
    double result = 0.0;

    for (std::size_t i = 0; i < y_true.row_size(); ++i)
        for(std::size_t j = 0; j < y_true.col_size(); ++j)
            result += std::pow(y_true(i, j) - y_pred(i, j), 2);

    return result / y_true.row_size();
}

void NNetwork_old::show() const
{
    std::cout << "W_ab: " << W_ab << "\nW_bc:" << W_bc
     << "\nB_b: " << B_b << "\nB_c: " << B_c << '\n';
}
