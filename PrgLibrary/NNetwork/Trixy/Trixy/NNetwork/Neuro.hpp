#ifndef NEURO_HPP
#define NEURO_HPP

#include <initializer_list>
#include <cstddef>
#include <cmath>
#include <iostream>

template <class Vector, class Matrix, template <typename...> class Collection, class Linear>
class Neuro
{
private:
    using Li = Linear;

    Collection<Matrix> W;
    Collection<Vector> B;

    std::size_t N;

    double (*F)(double);
    double (*DF)(double);

public:
    Neuro(const std::initializer_list<std::size_t>& inner);
    Neuro(const Collection<Matrix>& weight, const Collection<Vector>& bias);

    Neuro(const Neuro&) = default;
    Neuro(Neuro&&) = default;
    Neuro& operator= (const Neuro&) = default;
    Neuro& operator= (Neuro&&) = default;

    void initializeInnerStruct(double (*generator)());
    void setActivationFunction(double (*function)(double), double (*function_derived)(double));

    const Collection<Matrix>& getInnerWeight() const;
    const Collection<Vector>& getInnerBias() const;

    Vector feedforward(const Vector&) const;
    Matrix feedforward(const Matrix&) const;

    void trainStochastic(
        const Matrix& in, const Matrix& out, double learn_rate, std::size_t epoch_rate);
    void trainBatch(
        const Matrix& in, const Matrix& out, double learn_rate, std::size_t epoch_rate);
    void trainMiniBatch(
        const Matrix& in, const Matrix& out, double learn_rate,
        std::size_t epoch_rate, std::size_t batch_split); //experimental

    double accuracy(const Matrix& in, const Matrix& out) const; //repair
    double accuracy(const Matrix& in, const Matrix& out, double range_rate) const; //repair
    double loss(const Matrix& in, const Matrix& out) const; //repair
};

template <class Vector, class Matrix, template <typename...> class Collection, class Linear>
Neuro<Vector, Matrix, Collection, Linear>::Neuro(const std::initializer_list<std::size_t>& inner)
    : W(inner.size() - 1), B(inner.size() - 1), N(inner.size() - 1)
{
    auto layer = inner.begin() + 1;
    for(std::size_t i = 0; i < N; ++i)
    {
        W[i] = Matrix(*(layer - 1), *layer);
        B[i] = Vector(*layer);
        ++layer;
    }
}

template <class Vector, class Matrix, template <typename...> class Collection, class Linear>
Neuro<Vector, Matrix, Collection, Linear>::Neuro(
    const Collection<Matrix>& inner_W, const Collection<Vector>& inner_B)
    : W(inner_W), B(inner_B), N(inner_B.size())
{
}

template <class Vector, class Matrix, template <typename...> class Collection, class Linear>
void Neuro<Vector, Matrix, Collection, Linear>::initializeInnerStruct(double (*generator)())
{
    for(std::size_t i = 0; i < N; ++i)
    {
        W[i].fill(generator);
        B[i].fill(generator);
    }
}

template <class Vector, class Matrix, template <typename...> class Collection, class Linear>
void Neuro<Vector, Matrix, Collection, Linear>::setActivationFunction(
    double (*function)(double), double (*function_derived)(double))
{
    F = function;
    DF = function_derived;
}

template <class Vector, class Matrix, template <typename...> class Collection, class Linear>
const Collection<Matrix>& Neuro<Vector, Matrix, Collection, Linear>::getInnerWeight() const
{
    return W;
}

template <class Vector, class Matrix, template <typename...> class Collection, class Linear>
const Collection<Vector>& Neuro<Vector, Matrix, Collection, Linear>::getInnerBias() const
{
    return B;
}

template <class Vector, class Matrix, template <typename...> class Collection, class Linear>
Vector Neuro<Vector, Matrix, Collection, Linear>::feedforward(const Vector& vector) const
{
    Vector y_pred = vector;
    for(std::size_t i = 0; i < N; ++i)
        y_pred = (Li::dot(y_pred, W[i]) + B[i]).apply(F);

    return y_pred;
}

template <class Vector, class Matrix, template <typename...> class Collection, class Linear>
Matrix Neuro<Vector, Matrix, Collection, Linear>::feedforward(const Matrix & in) const
{
    const std::size_t batch_size = in.row();
    const std::size_t output_size = W[N - 1].col();

    Matrix y_pred(batch_size, output_size);
    Vector out;

    for(std::size_t i = 0; i < batch_size; ++i)
    {
        out = feedforward(Li::template get<Vector>(in, i));
        for(std::size_t j = 0; j < out.size(); ++j)
            y_pred(i, j) = out(j);
    }

    return y_pred;
}

template <class Vector, class Matrix, template <typename...> class Collection, class Linear>
void Neuro<Vector, Matrix, Collection, Linear>::trainStochastic(
    const Matrix& in, const Matrix& out, double learn_rate, std::size_t epoch_rate)
{
    Collection<Vector> H(N + 1);
    Collection<Vector> S(N);
    Collection<Vector> DH(N);
    Collection<Matrix> DW(N);
    Collection<Vector> DB(N);

    Matrix pred_out(out.row(), out.col());
    Vector theta;

    std::size_t within = in.row();
    std::size_t sample;

    for(std::size_t epoch = 0; epoch < epoch_rate; ++epoch)
    {
        sample = rand() % within;

        H[0] = Li::template get<Vector>(in, sample);
        for(std::size_t i = 0; i < N; ++i)
        {
            S[i]     = Li::dot(H[i], W[i]) + B[i];
            H[i + 1] = S[i].apply(F);
            DH[i]    = S[i].apply(DF);
        }

        theta = H[N] - Li::template get<Vector>(out, sample);
        for(std::size_t i = N - 1; i > 0; --i)
        {
            DW[i] = Li::join(Li::template tensordot<Matrix>(DH[i], H[i]), theta);
            DB[i] = DH[i].join(theta);

            theta = Li::dot_t(theta, Li::join(W[i], DH[i]));
        }
        DW[0] = Li::join(Li::template tensordot<Matrix>(DH[0], H[0]), theta);
        DB[0] = DH[0].join(theta);

        for(std::size_t i = 0; i < N; ++i)
        {
            W[i] -= DW[i].join(learn_rate);
            B[i] -= DB[i].join(learn_rate);
        }
        //
        if((epoch + 1)% 100 == 0)
        {
            //std::cout << "Epoch " << epoch + 1 << " loss: " << loss(in, out) << '\n';
            std::cout << "Epoch " << epoch + 1 << '\n';
        }
        //
    }
}

template <class Vector, class Matrix, template <typename...> class Collection, class Linear>
void Neuro<Vector, Matrix, Collection, Linear>::trainBatch(
    const Matrix &in, const Matrix &out, double learn_rate, std::size_t epoch_rate)
{
    Collection<Vector> H(N + 1);
    Collection<Vector> S(N);
    Collection<Vector> DH(N);
    Collection<Matrix> DW(N);
    Collection<Vector> DB(N);

    Matrix pred_out(out.row(), out.col());
    Vector theta;

    Collection<Matrix> deltaW(N);
    Collection<Vector> deltaB(N);

    for(std::size_t i = 0; i < N; ++i)
    {
        deltaW[i].resize(W[i].row(), W[i].col());
        deltaB[i].resize(B[i].size());
    }

    learn_rate /= in.row();

    for(std::size_t epoch = 0; epoch < epoch_rate; ++epoch)
    {
        for(std::size_t i = 0; i < N; ++i)
        {
            deltaW[i].fill( [] { return 0.0; });
            deltaB[i].fill( [] { return 0.0; });
        }

        for(std::size_t sample = 0; sample < in.row(); ++sample)
        {
            H[0] = Li::template get<Vector>(in, sample);
            for(std::size_t i = 0; i < N; ++i)
            {
                S[i]     = Li::dot(H[i], W[i]) + B[i];
                H[i + 1] = S[i].apply(F);
                DH[i]    = S[i].apply(DF);
            }

            theta = H[N] - Li::template get<Vector>(out, sample);
            for(std::size_t i = N - 1; i > 0; --i)
            {
                DW[i] = Li::join(Li::template tensordot<Matrix>(DH[i], H[i]), theta);
                DB[i] = DH[i].join(theta);

                theta = Li::dot_t(theta, Li::join(W[i], DH[i]));
            }
            DW[0] = Li::join(Li::template tensordot<Matrix>(DH[0], H[0]), theta);
            DB[0] = DH[0].join(theta);

            for(std::size_t i = 0; i < N; ++i)
            {
                deltaW[i] += DW[i];
                deltaB[i] += DB[i];
            }
        }

        for(std::size_t i = 0; i < N; ++i)
        {
            W[i] -= deltaW[i].join(learn_rate);
            B[i] -= deltaB[i].join(learn_rate);
        }
        /*
        if((epoch + 1)% 100 == 0)
        {
            //std::cout << "Epoch " << epoch + 1 << " loss: " << loss(in, out) << '\n';
            std::cout << "Epoch " << epoch + 1 << '\n';
        }
        */
    }
}

template <class Vector, class Matrix, template <typename...> class Collection, class Linear>
void Neuro<Vector, Matrix, Collection, Linear>::trainMiniBatch(
    const Matrix &in, const Matrix &out, double learn_rate,
    std::size_t epoch_rate, std::size_t mini_batch_size)
{
    Collection<Vector> H(N + 1);
    Collection<Vector> S(N);
    Collection<Vector> DH(N);
    Collection<Matrix> DW(N);
    Collection<Vector> DB(N);

    Matrix pred_out(out.row(), out.col());
    Vector theta;

    Collection<Matrix> deltaW(N);
    Collection<Vector> deltaB(N);

    for(std::size_t i = 0; i < N; ++i)
    {
        deltaW[i].resize(W[i].row(), W[i].col());
        deltaB[i].resize(B[i].size());
    }

    std::size_t sample_begin = 0;
    std::size_t sample_end   = 0;

    learn_rate /= mini_batch_size;

    for(std::size_t epoch = 0; epoch < epoch_rate; ++epoch)
    {
        sample_end += mini_batch_size;

        for(std::size_t i = 0; i < N; ++i)
        {
            deltaW[i].fill( [] { return 0.0; });
            deltaB[i].fill( [] { return 0.0; });
        }

        while(sample_begin < sample_end)
        {
            H[0] = Li::template get<Vector>(in, sample_begin);
            for(std::size_t i = 0; i < N; ++i)
            {
                S[i]     = Li::dot(H[i], W[i]) + B[i];
                H[i + 1] = S[i].apply(F);
                DH[i]    = S[i].apply(DF);
            }

            theta = H[N] - Li::template get<Vector>(out, sample_begin);
            for(std::size_t i = N - 1; i > 0; --i)
            {
                DW[i] = Li::join(Li::template tensordot<Matrix>(DH[i], H[i]), theta);
                DB[i] = DH[i].join(theta);

                theta = Li::dot_t(theta, Li::join(W[i], DH[i]));
            }
            DW[0] = Li::join(Li::template tensordot<Matrix>(DH[0], H[0]), theta);
            DB[0] = DH[0].join(theta);

            for(std::size_t i = 0; i < N; ++i)
            {
                deltaW[i] += DW[i];
                deltaB[i] += DB[i];
            }

            ++sample_begin;
        }

        for(std::size_t i = 0; i < N; ++i)
        {
            W[i] -= deltaW[i].join(learn_rate);
            B[i] -= deltaB[i].join(learn_rate);
        }

        sample_begin %= in.row();
        sample_end   %= in.row();

        /*
        if((epoch + 1)% 100 == 0)
        {
            //std::cout << "Epoch " << epoch + 1 << " loss: " << loss(in, out) << '\n';
            std::cout << "Epoch " << epoch + 1 << '\n';
        }
        */
    }
}

template <class Vector, class Matrix, template <typename...> class Collection, class Linear>
double Neuro<Vector, Matrix, Collection, Linear>::accuracy(
    const Matrix& in, const Matrix& out) const
{
    Matrix pred_out = feedforward(in);
    double count = 0.0;

    std::size_t max_pred_out;
    std::size_t max_out;

    for(std::size_t i = 0; i < pred_out.row(); ++i)
    {
        max_pred_out = 0;
        max_out = 0;

        for(std::size_t j = 0; j < pred_out.col(); ++j)
            if(pred_out(i, max_pred_out)  < pred_out(i, j))
                max_pred_out = j;

        for(std::size_t j = 0; j < out.col(); ++j)
            if(out(i, max_out)  < out(i, j))
                max_out = j;

        if(max_pred_out == max_out)
            ++count;
    }

    return count / in.row();
}

template <class Vector, class Matrix, template <typename...> class Collection, class Linear>
double Neuro<Vector, Matrix, Collection, Linear>::accuracy(
    const Matrix& in, const Matrix& out, double range_rate) const
{
    Matrix pred_out = feedforward(in);
    double count = 0;
    bool answer;

    for(std::size_t i = 0; i < out.row(); ++i)
    {
        answer = true;
        for(std::size_t j = 0; j < out.col(); ++j)
        {
            if(std::fabs(pred_out(i, j) - out(i, j)) > range_rate)
            {
                answer = false;
                break;
            }
        }
        if(answer)
        {
            ++count;
        }
    }
    return count / in.row();
}

template <class Vector, class Matrix, template <typename...> class Collection, class Linear>
double Neuro<Vector, Matrix, Collection, Linear>::loss(const Matrix& in, const Matrix& out) const
{
    Matrix pred = feedforward(in);
    double result = 0.0;

    for (std::size_t i = 0; i < out.row(); ++i)
        for(std::size_t j = 0; j < out.col(); ++j)
            result += std::pow(out(i, j) - pred(i, j), 2);

    return result / out.row();
}

#endif // NEURO_HPP
