TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS +=  -fopenmp

SOURCES += \
        main.cpp \
        Liangle/vector.cpp \
        Liangle/matrix.cpp \
        NNetwork/nnetwork.cpp

HEADERS += \
        Liangle/liangle.h \
        Timer/timer.h \
        Liangle/vector.h \
        Liangle/matrix.h \
        Dictionary/dictionary.hpp \
        NNetwork/nnetwork.h \
        mnist_master/mnist_reader.hpp \
        mnist_master/mnist_reader_common.hpp \
        mnist_master/mnist_reader_less.hpp \
        mnist_master/mnist_utils.hpp
