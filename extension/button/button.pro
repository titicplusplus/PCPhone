######################################################################
# Automatically generated by qmake (3.1) Mon Jun 7 20:25:33 2021
######################################################################

TEMPLATE = app
TARGET = ui_linux
INCLUDEPATH += .
LIBS += -lstdc++fs -g
# RESOURCES += ressources.qrc


# QMAKE_CC = gcc-7
# QMAKE_CXX = g++-7

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += uiqt.hpp
SOURCES += ui.cpp uiqt.cpp
QT += widgets network 

