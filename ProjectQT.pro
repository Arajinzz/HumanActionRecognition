#-------------------------------------------------
#
# Project created by QtCreator 2018-03-25T15:41:47
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectQT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    videoanalysis.cpp \
    imageanalysis.cpp \
    recognize.cpp \
    classifier.cpp \
    mouvementclass.cpp \
    crossvalidation.cpp \
    newrecognizeui.cpp \
    addmouvv2.cpp \
    settings.cpp \
    modechooser.cpp

HEADERS += \
        mainwindow.h \
    videoanalysis.h \
    imageanalysis.h \
    recognize.h \
    classifier.h \
    mouvementclass.h \
    crossvalidation.h \
    newrecognizeui.h \
    addmouvv2.h \
    settings.h \
    modechooser.h

FORMS += \
        mainwindow.ui \
    newrecognizeui.ui \
    modechooser.ui

INCLUDEPATH += C:\Users\Arajin\Desktop\ProjetFE\Opencv\build\include

LIBS += -LC:\Users\Arajin\Desktop\ProjetFE\Opencv\build\x64\vc14\lib\
        -lopencv_world331 \
        -lopencv_world331d

RESOURCES += \
    style.qrc
