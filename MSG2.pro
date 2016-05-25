#-------------------------------------------------
#
# Project created by QtCreator 2016-05-05T10:23:23
#
#-------------------------------------------------

QT       += core gui

TARGET = MSG2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    io.cpp \
    model/image.cpp \
    latlong.cpp \
    views/MyWidgets/mylabel.cpp \
    controllers/imagecontroller.cpp \
    views/canaldisplay.cpp \
    views/MyWidgets/reddotlabel.cpp \
    views/MyWidgets/coordinatewidget.cpp \
    views/MyWidgets/locationwidget.cpp \
    views/MyWidgets/latlonwidget.cpp \
    views/multicanaldisplay.cpp \
    views/MyWidgets/imagesselectwidget.cpp \
    controllers/multicanalcontroller.cpp \
    views/decoupeimage.cpp \
    views/MyWidgets/labeldecoupe.cpp \
    views/unicanaldisplay.cpp \
    views/MyWidgets/scrollreddotlabel.cpp \
    db.cpp \
    views/MyWidgets/communeselection.cpp \
    model/decoupage.cpp \
    views/dbimagesview.cpp \
    views/dbdecoupageview.cpp \
    controllers/calcul.cpp

HEADERS  += mainwindow.h \
    io.h \
    model/image.h \
    latlong.h \
    views/MyWidgets/mylabel.h \
    controllers/imagecontroller.h \
    views/canaldisplay.h \
    views/MyWidgets/reddotlabel.h \
    views/MyWidgets/coordinatewidget.h \
    views/MyWidgets/latlonwidget.h \
    views/MyWidgets/locationwidget.h \
    views/multicanaldisplay.h \
    views/MyWidgets/imagesselectwidget.h \
    controllers/multicanalcontroller.h \
    views/decoupeimage.h \
    views/MyWidgets/labeldecoupe.h \
    views/unicanaldisplay.h \
    views/MyWidgets/scrollreddotlabel.h \
    db.h \
    views/MyWidgets/communeselection.h \
    model/decoupage.h \
    views/dbimagesview.h \
    views/dbdecoupageview.h \
    controllers/calcul.h

FORMS    += mainwindow.ui

INCLUDEPATH += model/ \
    controllers \
    views \
    views/MyWidgets

QT +=sql
QT += core gui declarative
