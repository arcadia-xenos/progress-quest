#-------------------------------------------------
#
# Project created by QtCreator 2012-09-16T01:09:58
#
#-------------------------------------------------

#LIBS += -ljsoncpp
#LIBS += "C:/Users/Eddie/Downloads/jsoncpp/libs/mingw/libjson_mingw_libmt.a"
LIBS += "C:/Users/Eddie/Downloads/jsoncpp/libs/mingw/libjson_mingw_libmt.a"
INCLUDEPATH += "C:/Users/Eddie/Downloads/"


QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pq7
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    entity.cpp \
    pq7_config.cpp \
    c_spell.cpp \
    c_item.cpp \
    c_monster.cpp \
    c_world.cpp \
    dialog_opening.cpp \
    dialog_charsheet.cpp

HEADERS  += mainwindow.h \
    entity.h \
    pq7_config.h \
    c_spell.h \
    c_item.h \
    c_monster.h \
    c_world.h \
    dialog_opening.h \
    dialog_charsheet.h

FORMS    += mainwindow.ui \
    dialog_opening.ui \
    dialog_charsheet.ui

OTHER_FILES += \
    README

