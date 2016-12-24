QT += widgets
QT += core
QT -= gui

CONFIG += c++11

TARGET = TextPad
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    textedit.cpp

HEADERS += \
    textedit.h

RESOURCES = images.qrc
