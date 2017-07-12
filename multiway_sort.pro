TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
	mydatabase.cpp \
	person.cpp \
	utils.cpp

HEADERS += mydatabase.h \
	person.h \
	utils.h

CONFIG += c++11

LIBS += -pthread

QMAKE_CXXFLAGS += -O3
