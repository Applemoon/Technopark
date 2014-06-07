TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.c

QMAKE_CC= gcc -std=c99 -Wall -Werror -Wextra
