#include <random>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <vector>

#include "Dictionary/dictionary.hpp"
#include "Liangle/li_linear.hpp"
#include "Liangle/li_matrix.hpp"
#include "Liangle/li_vector.hpp"
#include "NNetwork/Neuro.hpp"

#include "Timer/timer.h"
#include "mnist_master/mnist_reader.hpp"

namespace li = liangle;

template <typename T>
class MyVector : public li::Vector<T>
{
public:
    MyVector(std::size_t n) : li::Vector<T>(n) { }
    MyVector(const std::initializer_list<T>& data) : li::Vector<T>(data) { }

    T& operator[] (std::size_t i) { return this->operator()(i); }
    const T& operator[] (std::size_t i) const { return this->operator()(i); }
};

double random_real()
{
    static int min = -1'000;
    static int max = 1'000;

    return static_cast<double>(rand() % (max - min + 1) + min) / 1'000;
}
double random_normal()
{
    static int min = -1'000;
    static int max = 1'000;
    static double pi = 3.14159265;

    double x = static_cast<double>(rand() % (max - min + 1) + min) / 1'000;

    return std::exp(- x * x) / std::sqrt(2 * pi);
}

double sigma(double x) { return 1 / (1 + std::exp(-x)); }
double sigma_derived(double x) { return sigma(x) * (1 - sigma(x)); }

double th(double x) { return std::tanh(x); }
double th_derived(double x) { return 1 - std::pow(tanh(x), 2); }

bool check(
    const li::Vector<double>& y_pred, const li::Vector<double>& y_true, double range)
{
    for(std::size_t i = 0; i < y_pred.size(); ++i)
        if(std::fabs(y_pred(i) - y_true(i)) > range)
            return false;

    return true;
}

li::Matrix<double> initialize_i(
    const std::vector<std::vector<unsigned char>>& data,
    std::size_t batch_size, std::size_t input_size)
{
    li::Matrix<double> input_batch(batch_size, input_size);

    for(std::size_t i = 0; i < batch_size; ++i)
        for(std::size_t j = 0; j < input_size; ++j)
            input_batch(i, j) = static_cast<double>(data[i][j]);

    return input_batch;
}

li::Matrix<double> initialize_o(
    const std::vector<unsigned char>& data,
    std::size_t batch_size, std::size_t output_size)
{
    li::Matrix<double> output_batch(batch_size, output_size);

    for(std::size_t i = 0; i < batch_size; ++i)
        for(std::size_t j = 0; j < output_size; ++j)
            if(data[i] == j)
                output_batch(i, j) = 1;
            else
                output_batch(i, j) = 0;

    return output_batch;
}

void show_image_batch(const li::Matrix<double>& data)
{
    for(std::size_t i = 0; i < data.row(); ++i)
    {
        for(std::size_t j = 0; j < data.col(); ++j)
        {
            if(j % 28 == 0)
                std::cout << '\n';
            std::cout << (data(i, j) != 0.0 ? '#' : '.') << ' ';
        }
        std::cout << '\n';
    }
}

template <class Vector, class Matrix, class Linear, template <typename...> class Collection>
void showInnerStruct(
    const Neuro<Vector, Matrix, Collection, Linear>& neuro)
{
    for(std::size_t i = 0; i < neuro.getInnerWeight().size(); ++i)
        std::cout << "W[" << i << "]: " << neuro.getInnerWeight()[i] << '\n';

    for(std::size_t i = 0; i < neuro.getInnerBias().size(); ++i)
        std::cout << "B[" << i << "]: " << neuro.getInnerBias()[i] << '\n';
}

template <class Vector, class Matrix, class Linear, template <typename...> class Collection>
void testNeuro(
    Neuro<Vector, Matrix, Collection, Linear> neuro,
    const Matrix& in, const Matrix& out)
{
    for(std::size_t i = 0; i < in.row(); ++i)
        std::cout << "<" << i << "> "
            << neuro.feedforward(Linear::template get<Vector>(in, i)) << " : "
                << Linear::template get<Vector>(out, i) << '\n';
}

void test9()
{
    using NeuralFeedForward
         = Neuro<li::Vector<double>, li::Matrix<double>, Dictionary, li::Linear>;

    NeuralFeedForward network = {4, 4, 5, 4, 3};

    network.initializeInnerStruct([] {
        static int within = 1000;
        return static_cast<double>(rand() % (2 * within + 1) - within) / within;
    });

    network.setActivationFunction(th, th_derived);

    li::Matrix<double> train_in_set
    {
        {1, 0, 1, 1},
        {1, 1, 1, 0},
        {1, 1, 0, 1},
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {0, 0, 1, 1},
    };
    li::Matrix<double> train_out_set
    {
        {1, 0, 0},
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 1},
        {0, 1, 0},
        {1, 0, 0}
    };

    std::cout << std::fixed << std::setprecision(6);

    std::cout << "Before train\n";
    testNeuro(network, train_in_set, train_out_set);
    Timer t;
    network.trainBatch(train_in_set, train_out_set, 0.5, 1'000);
    network.trainMiniBatch(train_in_set, train_out_set, 0.5, 1'000, 2);
    network.trainBatch(train_in_set, train_out_set, 0.1, 10'000);
    std::cout << t.elapsed() << '\n';
    std::cout << "After train\n";
    testNeuro(network, train_in_set, train_out_set);
    std::cout << "Accuracy: " << network.accuracy(train_in_set, train_out_set, 0.1) << '\n';
    std::cout << "Loss: " << network.loss(train_in_set, train_out_set) << '\n';
}

void test13()
{
//  Some preparing:
    using NeuralFeedForward
         = Neuro<li::Vector<double>, li::Matrix<double>, Dictionary, li::Linear>;

    auto dataset =
        mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>("C:/mnist_data/");

    std::size_t train_batch_size = 1'000;
    std::size_t test_batch_size = 1'000;
    std::size_t input_size = 784;
    std::size_t out_size = 10;

    NeuralFeedForward network = { input_size, 500, 300, 100, out_size };
    network.initializeInnerStruct(random_real);
    network.setActivationFunction(sigma, sigma_derived);

//  Train batch initialize:
    li::Matrix<double> train_in = initialize_i(dataset.training_images, train_batch_size, input_size);
    li::Matrix<double> train_out = initialize_o(dataset.training_labels, train_batch_size, out_size);

//  Test batch initialize:
    li::Matrix<double> test_in = initialize_i(dataset.test_images, test_batch_size, input_size);
    li::Matrix<double> test_out = initialize_o(dataset.test_labels, test_batch_size, out_size);

//  Show image:
   //show_image_batch(train_in);

//  Train network:
    std::cout << "start train:\n";
    //network.trainMiniBatch(train_in, train_out, 0.5, 1'000, 500);
    network.trainStochastic(train_in, train_out, 0.5, 1'000);
    //network.trainBatch(train_in, train_out, 0.5, 1'000);

//  Testing:
    li::Vector<double> test_i;
    li::Vector<double> test_o;

//  Test train_batch
    std::cout << "NNetwork tarin accuracy: " << network.accuracy(train_in, train_out) << '\n';
    std::cout << "NNetwork train loss: " << network.loss(train_in, train_out) << '\n';
    //testNeuro(network, train_in, train_out);

//  Test test_batch
    std::cout << "NNetwork test accuracy: " << network.accuracy(test_in, test_out, 0.1) << '\n';
    std::cout << "NNetwork test loss: " << network.loss(test_in, test_out) << '\n';
    //testNeuro(network, test_in, test_out);
}


int main()
{
    srand(static_cast<unsigned>(time(0)));

    std::cout << std::fixed << std::setprecision(6);
    //std::cout.setf(std::ios::showpos);

    test9();

    return 0;
}

/*
li::Vector<double>& test15(li::Vector<double>& vector)
{
    vector.modify(sigma);
    vector(0) = 0.0;

    return vector;
}

void test14()
{
    li::Vector<double> A = {1, 2, 3};
    li::Vector<double> B = {1, 2};

    MyVector<double> C1 = {1, 2, 3};
    MyVector<double> C2 = {1, 2};

    li::Matrix<double> M = {{1, 0}, {0, -1}, {2, 1}};
    li::Matrix<double> W = {{0, 1, -1}, {-1, -1, 0}, {0, 1, 0}};

    std::cout << li::Lineary::dot(A, M) << '\n';
    std::cout << li::Lineary::dot_t(A, W) << '\n';

    std::cout << A << '\n';
    std::cout << B << '\n';

    std::cout << li::Lineary::tensordot<li::Matrix<double>>(C1, C2) << '\n';
    std::cout << li::Lineary::tensordot<li::Matrix<double>>(A, B) << '\n';
    // [[2, 4, 6],
    //  [3, 6, 9]]
    //
    // [[2, 3],
    //  [4, 6],
    //  [6, 9]]
}

void test7()
{
    std::cout << std::fixed << std::setprecision(6);
// Creating Neural Network
    NNetwork network = {2, 3, 3, 2};
    network.initializeInnerStruct(random_normal);
    network.setActivationFunction(sigma, sigma_derived);

// Train set (in/out)
    Matrix input_train_set
    {
        {-2, -1},  // Алиса
        {23, 6},   // Боб
        {10, 4},   // Чарли
        {-15, -6} // Диана
    };

    Matrix output_train_set
    {
        {1, 0}, // Алиса
        {0, 1}, // Боб
        {0, 1}, // Чарли
        {1, 0}  // Диана
    };

// Train split set
    Vector alisa = {-2, -1};
    Vector bob = {23, 6};
    Vector charli = {10, 4};
    Vector diana = {-15, -6};

// Test split set
    Vector emily = {-7, -3};
    Vector frank = {21, 5};
    Vector test = {180 - 145, 75 - 66};

// Full processing
    std::cout << "Network struct before train\n";
    network.showInnerStruct();
    std::cout << "Train set before train\n";
    std::cout << "Alisa: " << network.feedforward(alisa) << '\n';
    std::cout << "Bob: " << network.feedforward(bob) << '\n';
    std::cout << "Charli: " << network.feedforward(charli) << '\n';
    std::cout << "Diana: " << network.feedforward(diana) << '\n';
    std::cout << "Test set before train\n";
    std::cout << "Emily: " << network.feedforward(emily) << '\n';
    std::cout << "Frank: " << network.feedforward(frank) << '\n';
    std::cout << "Test: " << network.feedforward(test) << '\n';

    Timer t;
    network.trainStochastic(input_train_set, output_train_set, 0.15, 10000);
    std::cout << t.elapsed() << '\n';

    std::cout << "\nNetwork struct after train\n";
    network.showInnerStruct();
    std::cout << "Train set after train\n";
    std::cout << "Alisa: " << network.feedforward(alisa) << '\n';
    std::cout << "Bob: " << network.feedforward(bob) << '\n';
    std::cout << "Charli: " << network.feedforward(charli) << '\n';
    std::cout << "Diana: " << network.feedforward(diana) << '\n';
    std::cout << "Test set after train\n";
    std::cout << "Emily: " << network.feedforward(emily) << '\n';
    std::cout << "Frank: " << network.feedforward(frank) << '\n';
    std::cout << "Test: " << network.feedforward(test) << '\n';

    std::cout << "NNetwork accuracy: " << network.accuracy(input_train_set, output_train_set, 0.05) << "\n";
    std::cout << "NNetwork loss: " << network.loss(input_train_set, output_train_set) << "\n";
}
void test9()
{
    NNetwork network = {4, 4, 5, 4, 3};

    network.initializeInnerStruct(random_normal);
    network.setActivationFunction(th, th_derived);

    Matrix train_in_set
    {
        {1, 0, 1, 1},
        {1, 1, 1, 0},
        {1, 1, 0, 1},
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {0, 0, 1, 1},
    };
    Matrix train_out_set
    {
        {1, 0, 0},
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 1},
        {0, 1, 0},
        {1, 0, 0}
    };

    std::cout << std::fixed << std::setprecision(6);

    std::cout << "Before train\n";
    network.test(train_in_set, train_out_set);
    Timer t;
    network.trainBatch(train_in_set, train_out_set, 0.5, 10000);
    std::cout << t.elapsed() << '\n';
    std::cout << "After train\n";
    network.test(train_in_set, train_out_set);
    std::cout << "Accuracy: " << network.accuracy(train_in_set, train_out_set, 0.5) << '\n';
    std::cout << "Loss: " << network.loss(train_in_set, train_out_set) << '\n';
}

void test11()
{
    std::cout << std::fixed << std::setprecision(3);

    auto dataset =
    mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>(
        "C:/Users/Maksim/Documents/Trixy/mnist_data/");

    std::size_t train_size = 100;
    std::size_t input_size = dataset.training_images.begin()->size();
    std::size_t out_size = 10;

    Matrix train_in(train_size, input_size);

    for(std::size_t i = 0; i < train_size; ++i)
    {
        for(std::size_t j = 0; j < input_size; ++j)
        {
            train_in(i, j) = static_cast<double>(dataset.training_images[i][j]);
        }
    }

    Matrix train_out(train_size, out_size);
    for(std::size_t i = 0; i < train_size; ++i)
    {
        for(std::size_t j = 0; j < out_size; ++j)
        {
            if(dataset.training_labels[i] == j)
                train_out(i, j) = 1;
            else
                train_out(i, j) = 0;
        }
    }

    NNetwork network = { input_size, 500, 300, out_size };
    network.initializeInnerStruct(random_real);
    network.setActivationFunction(sigma, sigma_derived);

    std::cout << "start train:\n";
    network.trainStochastic(train_in, train_out, 0.01, 1000);
    std::cout << "start test:\n";

    Vector test_in;
    Vector test_out;

    for(std::size_t i = 0; i < train_size; ++i)
    {
        test_in = network.feedforward(train_in(i));
        test_out = train_out(i);
        std::cout << "<" << i << "> " << test_in << " : " << test_out << " : ";
        if (check(test_in, test_out, 0.1))
        {
            std::cout << '+';
        }
        std::cout << '\n';
    }

    std::cout << "NNetwork accuracy: " << network.accuracy(train_in, train_out, 0.1) << "\n";
    std::cout << "NNetwork loss: " << network.loss(train_in, train_out) << "\n";
}

void test12()
{
    auto dataset =
    mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>(
        "C:/Users/Maksim/Documents/Trixy/mnist_data/");

    std::size_t train_size = 100;
    std::size_t input_size = dataset.training_images.begin()->size();
    std::size_t out_size = 10;

    Matrix train_in(train_size, input_size);

    for(std::size_t i = 0; i < train_size; ++i)
        for(std::size_t j = 0; j < input_size; ++j)
            train_in(i, j) = static_cast<double>(dataset.training_images[i][j]);

    Matrix train_out(train_size, out_size);

    for(std::size_t i = 0; i < train_size; ++i)
        for(std::size_t j = 0; j < out_size; ++j)
            if(dataset.training_labels[i] == j)
                train_out(i, j) = 1;
            else
                train_out(i, j) = 0;

    NNetwork network = { input_size, 500, 300, out_size };
    network.initializeInnerStruct(random_real);
    network.setActivationFunction(sigma, sigma_derived);

    for(int l = 0; l < 10; ++l)
    {
        Timer t1;
        network.feedforward(train_in);
        std::cout << t1.elapsed() << '\n';

        Timer t2;
        for(std::size_t i = 0; i < train_in.row(); ++i)
            network.feedforward(train_in(i));
        std::cout << t2.elapsed() << '\n';

        std::cout << l << '\n';
    }
}

void showInnerStruct(const NNetwork& nnetwork)
{
    for(std::size_t i = 0; i < nnetwork.getInnerWeight().size(); ++i)
        std::cout << "W[" << i << "]: " << nnetwork.getInnerWeight()[i] << '\n';
    for(std::size_t i = 0; i < nnetwork.getInnerBias().size(); ++i)
        std::cout << "B[" << i << "]: " << nnetwork.getInnerBias()[i] << '\n';
}

void test7()
{
    std::cout << std::fixed << std::setprecision(8);
// Creating Neural Network
    NNetwork network = {2, 2, 2};
    network.initializeInnerStruct(random_real);
    network.setActivationFunction(th, th_derived);

// Train set (in/out)
    Matrix input_train_set
    {
        {-2, -1},  // Алиса
        {23, 6},   // Боб
        {10, 4},   // Чарли
        {-15, -6} // Диана
    };

    Matrix output_train_set
    {
        {1, 0}, // Алиса
        {0, 1}, // Боб
        {0, 1}, // Чарли
        {1, 0}  // Диана
    };

// Train split set
    Vector alisa = {-2, -1};
    Vector bob = {23, 6};
    Vector charli = {10, 4};
    Vector diana = {-15, -6};

// Test split set
    Vector emily = {-7, -3};
    Vector frank = {21, 5};
    Vector test = {180 - 145, 75 - 66};

// Full processing
    std::cout << "Network struct before train\n";
    network.showInnerStruct();
    std::cout << "Train set before train\n";
    std::cout << "Alisa: " << network.feedforward(alisa) << '\n';
    std::cout << "Bob: " << network.feedforward(bob) << '\n';
    std::cout << "Charli: " << network.feedforward(charli) << '\n';
    std::cout << "Diana: " << network.feedforward(diana) << '\n';
    std::cout << "Test set before train\n";
    std::cout << "Emily: " << network.feedforward(emily) << '\n';
    std::cout << "Frank: " << network.feedforward(frank) << '\n';
    std::cout << "Test: " << network.feedforward(test) << '\n';

    Timer t;
    network.train(input_train_set, output_train_set, 0.5, 1000);
    std::cout << t.elapsed() << '\n';

    std::cout << "\nNetwork struct after train\n";
    network.showInnerStruct();
    std::cout << "Train set after train\n";
    std::cout << "Alisa: " << network.feedforward(alisa) << '\n';
    std::cout << "Bob: " << network.feedforward(bob) << '\n';
    std::cout << "Charli: " << network.feedforward(charli) << '\n';
    std::cout << "Diana: " << network.feedforward(diana) << '\n';
    std::cout << "Test set after train\n";
    std::cout << "Emily: " << network.feedforward(emily) << '\n';
    std::cout << "Frank: " << network.feedforward(frank) << '\n';
    std::cout << "Test: " << network.feedforward(test) << '\n';
}

void test8()
{
    NNetwork network = {4, 3, 3};

    network.initializeInnerStruct(random_normal);
    network.setActivationFunction(sigma, sigma_derived);

    Matrix train_in_set
    {
        {1, 0, 1, 1},
        {1, 1, 1, 0},
        {1, 1, 0, 1},
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {0, 0, 1, 1},
    };
    Matrix train_out_set
    {
        {1, 0, 0},
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 1},
        {0, 1, 0},
        {1, 0, 0}
    };

    std::cout << std::fixed << std::setprecision(6);

    std::cout << "Before train\n";
    network.test(train_in_set, train_out_set);

    Timer t;
    network.train(train_in_set, train_out_set, 0.5, 10000);
    std::cout << t.elapsed() << '\n';

    std::cout << "After train\n";
    network.test(train_in_set, train_out_set);

    network.showInnerStruct();
}

void test9()
{
    NNetwork network = {4, 4, 5, 4, 3};

    network.initializeInnerStruct(random_normal);
    network.setActivationFunction(th, th_derived);

    Matrix train_in_set
    {
        {1, 0, 1, 1},
        {1, 1, 1, 0},
        {1, 1, 0, 1},
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {0, 0, 1, 1},
    };
    Matrix train_out_set
    {
        {1, 0, 0},
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 1},
        {0, 1, 0},
        {1, 0, 0}
    };

    std::cout << std::fixed << std::setprecision(6);

    std::cout << "Before train\n";
    network.test(train_in_set, train_out_set);
    Timer t;
    network.train(train_in_set, train_out_set, 0.5, 10000);
    std::cout << t.elapsed() << '\n';
    std::cout << "After train\n";
    network.test(train_in_set, train_out_set);
    std::cout << "Accuracy: " << network.accuracy(train_in_set, train_out_set, 0.5) << '\n';
    std::cout << "Loss: " << network.loss(train_in_set, train_out_set) << '\n';
}

void test10()
{
    std::cout << std::fixed << std::setprecision(6);
// Creating Neural Network
    NNetwork network = {2, 2, 2};
    network.initializeInnerStruct(random_real);
    network.setActivationFunction(th, th_derived);

// Train set (in/out)
    Matrix input_train_set
    {
        {-2, -1},
        {23, 6},
        {10, 4},
        {-15, -6}
    };

    Matrix output_train_set
    {
        {1, 0},
        {0, 1},
        {0, 1},
        {1, 0}
    };

// Full processing
    std::cout << "Network struct before train\n";
    network.showInnerStruct();
    network.test(input_train_set, output_train_set);
    std::cout << '\n';

    Timer t;
    network.train(input_train_set, output_train_set, 0.5, 1000);
    std::cout << t.elapsed() << '\n';

    std::cout << "\nNetwork struct after train\n";
    network.showInnerStruct();
    network.test(input_train_set, output_train_set);
    std::cout << '\n';
}
*/
