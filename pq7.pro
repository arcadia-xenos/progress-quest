#-------------------------------------------------
#
# Project created by QtCreator 2012-09-16T01:09:58
#
#-------------------------------------------------

QT       += core gui

TARGET = pq7
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    entity.cpp \
    pq7_config.cpp \
    c_spell.cpp \
    c_item.cpp \
    c_monster.cpp

HEADERS  += mainwindow.h \
    entity.h \
    pq7_config.h \
    c_spell.h \
    c_item.h \
    c_monster.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    README
