#include "nnetwork.h"

NNetwork::NNetwork(const std::initializer_list<std::size_t>& inner)
    : W(inner.size() - 1), B(inner.size() - 1), N(inner.size() - 1)
{
    std::size_t i = 0;
    for(auto n = inner.begin() + 1; n != inner.end(); ++n)
    {
        W[i] = Matrix(*(n - 1), *n);
        B[i] = Vector(*n);
        ++i;
    }
}

void NNetwork::initializeInnerStruct(double (*generator)())
{
    for(std::size_t i = 0; i < N; ++i)
    {
        W[i].fill(generator);
        B[i].fill(generator);
    }
}
void NNetwork::setActivationFunction(double (*function)(double), double (*function_derived)(double))
{
    F = function;
    DF = function_derived;
}

Vector NNetwork::feedforward(const Vector& vector) const
{
    Vector temp = vector;
    for(std::size_t i = 0; i < N; ++i)
        temp = (W[i].T_dot(temp) + B[i]).produce(F);

    return temp;
}

void NNetwork::train(const Matrix& in, const Matrix& out, double learn_rate, std::size_t epoch_rate)
{
    Dictionary<Vector> H(N + 1);
    Dictionary<Vector> S(N);
    Dictionary<Vector> DH(N);
    Dictionary<Matrix> DW(N);
    Dictionary<Vector> DB(N);

    Vector Y_loss;
    Vector theta;

    Matrix pred_out(out.row(), out.col());

    std::size_t within = in.row();
    std::size_t sample;

    for(std::size_t epoch = 1; epoch <= epoch_rate; ++epoch)
    {
        sample = rand() % within;

        H[0] = in(sample);
        for(std::size_t i = 0; i < N; ++i)
        {
            S[i] = W[i].T_dot(H[i]) + B[i];
            H[i + 1] = S[i].produce(F);
            DH[i] = S[i].produce(DF);
        }

        Y_loss = H[N] - out(sample);

        for(std::size_t i = 0; i < N; ++i)
        {
            theta = Y_loss;
            if(i == N - 1)
            {
                DW[i] = H[i].tensordot_T(DH[i]).join_T(theta);
                DB[i] = DH[i].join(theta);
            }
            else
            {
                for(std::size_t n = N - 1; n > i + 1; --n)
                    theta = theta.T_dot( W[n].T_join(DH[n]) );

                theta = W[i + 1].dot( DH[i + 1].join(theta) );

                DW[i] = H[i].tensordot_T(DH[i]).join_T(theta);
                DB[i] = DH[i].join(theta);
            }
        }

        for(std::size_t i = 0; i < N; ++i)
        {

            W[i] -= learn_rate * DW[i];
            B[i] -= learn_rate * DB[i];
        }

        if(epoch % 100 == 0)
        {
            //double current_loss_rate = loss(in, out);
            //std::cout << "Epoch " << epoch << " loss: " << current_loss_rate << '\n';

            std::cout << "Epoch " << epoch << '\n';
        }
    }
}

void NNetwork::test(const Matrix& in, const Matrix& out) const
{
    for(std::size_t i = 0; i < in.row(); ++i)
        std::cout << "<" << i << "> "
            << feedforward(in(i)) << " : " << out(i) << '\n';
}

void NNetwork::showInnerStruct() const
{
    for(std::size_t i = 0; i < N; ++i)
        std::cout << "W[" << i << "]: " << W[i] << '\n';
    for(std::size_t i = 0; i < N; ++i)
        std::cout << "B[" << i << "]: " << B[i] << '\n';
}

double NNetwork::accuracy(const Matrix& in, const Matrix& out, double range_rate) const
{
    Matrix pred_out(out.row(), out.col());
    for(std::size_t i = 0; i < out.row(); ++i)
        pred_out.put(i, feedforward(in(i)));

    double count = 0;
    bool check = false;
    for(std::size_t i = 0; i < out.row(); ++i)
    {
        check = true;
        for(std::size_t j = 0; j < out.col(); ++j)
        {
            if(std::fabs(pred_out(i, j) - out(i, j)) > range_rate)
            {
                check = false;
                break;
            }
        }
        if(check)
        {
            ++count;
        }
    }
    return count / in.row();
}
double NNetwork::loss(const Matrix& in, const Matrix& out) const
{
    Matrix pred_out(out.row(), out.col());
    for(std::size_t i = 0; i < out.row(); ++i)
        pred_out.put(i, feedforward(in(i)));

    return mean(pred_out, out);
}

double NNetwork::mean(const Matrix& y_true, const Matrix& y_pred)
{
    double result = 0.0;

    for (std::size_t i = 0; i < y_true.row(); ++i)
        for(std::size_t j = 0; j < y_true.col(); ++j)
            result += std::pow(y_true(i, j) - y_pred(i, j), 2);

    return result / y_true.row();
}
