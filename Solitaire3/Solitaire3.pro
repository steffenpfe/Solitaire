#-------------------------------------------------
#
# Project created by QtCreator 2018-05-17T17:17:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Solitaire3
TEMPLATE = app


SOURCES += main.cpp \
    card.cpp \
    deck.cpp \
    game.cpp \
    stack.cpp \
    button.cpp

HEADERS  += \
    card.h \
    deck.h \
    game.h \
    stack.h \
    button.h

RESOURCES += \
    res.qrc
