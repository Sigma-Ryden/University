TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS +=  -fopenmp

SOURCES += \
        Liangle/li_matrix.cpp \
        main.cpp \
        Liangle/vector.cpp \
        NNetwork/nnetwork.cpp

HEADERS += \
        Liangle/li_matrix.h \
        Liangle/liangle.h \
        Timer/timer.h \
        Liangle/vector.h \
        Dictionary/dictionary.hpp \
        NNetwork/nnetwork.h \
        mnist_master/mnist_reader.hpp \
        mnist_master/mnist_reader_common.hpp \
        mnist_master/mnist_reader_less.hpp \
        mnist_master/mnist_utils.hpp
