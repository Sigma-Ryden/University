#include <random>
#include <ctime>
#include <iostream>
#include <iomanip>
#include "Liangle/liangle.h"
#include "NNetwork/nnetwork.h"
#include "Timer/timer.h"
#include "mnist_master/mnist_reader.hpp"

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
double th_derived(double x) { return 1 - std::pow(th(x), 2); }


bool check(const Vector& y_pred, const Vector& y_true, double range)
{
    for(std::size_t i = 0; i < y_pred.size(); ++i)
        if(std::fabs(y_pred(i) - y_true(i)) > range)
            return false;

    return true;
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
    network.train(input_train_set, output_train_set, 0.15, 10000);
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
    network.trainBatch(train_in, train_out, 0.01, 100);
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

int main()
{
    srand(static_cast<unsigned>(time(0)));
    //std::cout.setf(std::ios::showpos);

    test9();

    return 0;
}

/*
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
