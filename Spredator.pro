#-------------------------------------------------
#
# Project created by QtCreator 2017-10-27T16:22:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Spredator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        view.cpp \
    model.cpp \
    drawingwidget.cpp \
    createnewsprite.cpp
HEADERS  += view.h \
    model.h \
    drawingwidget.h \
    createnewsprite.h

FORMS    += view.ui \
    createnewsprite.ui

RESOURCES += \
    images.qrc

INCLUDEPATH += "$$PWD/MagickLibraries_DLL/include"

# $$PWD/MagickLibraries_DLL/CORE_RL_Magick++.dll -lQt5Widgetsd -lQt5Guid -lQt5Cored
LIBS += "$$PWD/MagickLibraries_DLL/CORE_RL_Magick++_.lib"
