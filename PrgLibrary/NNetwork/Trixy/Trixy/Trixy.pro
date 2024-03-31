TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS +=  -fopenmp

QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

SOURCES += \
        main.cpp

HEADERS += \
        Liangle/li_linear.hpp \
        Liangle/li_matrix.hpp \
        Liangle/li_vector.hpp \
        NNetwork/neuro.hpp \
        Timer/timer.h \
        Dictionary/dictionary.hpp \
        mnist_master/mnist_reader.hpp \
        mnist_master/mnist_reader_common.hpp \
        mnist_master/mnist_reader_less.hpp \
        mnist_master/mnist_utils.hpp
