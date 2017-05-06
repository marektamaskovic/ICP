#-------------------------------------------------
#
# Project created by QtCreator 2017-05-04T08:46:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 4
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


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/classes.cpp \
    src/core.cpp \
    src/save.cpp \
    src/table.cpp \
    src/game_board.cpp

HEADERS  += src/mainwindow.h \
    src/classes.h \
    src/color.h \
    src/core.h \
    src/json.hpp \
    src/save.h \
    src/table.h \
    src/game_board.h

FORMS    += src/mainwindow.ui \
    src/ui/klondike.ui \
    src/table.ui \
    src/game_board.ui

DISTFILES += \
    src/hra2017 \
    src/hra2017-cli \
    src/img/cards/C1.gif \
    src/img/cards/C10.gif \
    src/img/cards/C11.gif \
    src/img/cards/C12.gif \
    src/img/cards/C13.gif \
    src/img/cards/C2.gif \
    src/img/cards/C3.gif \
    src/img/cards/C4.gif \
    src/img/cards/C5.gif \
    src/img/cards/C6.gif \
    src/img/cards/C7.gif \
    src/img/cards/C8.gif \
    src/img/cards/C9.gif \
    src/img/cards/D1.gif \
    src/img/cards/D10.gif \
    src/img/cards/D11.gif \
    src/img/cards/D12.gif \
    src/img/cards/D13.gif \
    src/img/cards/D2.gif \
    src/img/cards/D3.gif \
    src/img/cards/D4.gif \
    src/img/cards/D5.gif \
    src/img/cards/D6.gif \
    src/img/cards/D7.gif \
    src/img/cards/D8.gif \
    src/img/cards/D9.gif \
    src/img/cards/H1.gif \
    src/img/cards/H10.gif \
    src/img/cards/H11.gif \
    src/img/cards/H12.gif \
    src/img/cards/H13.gif \
    src/img/cards/H2.gif \
    src/img/cards/H3.gif \
    src/img/cards/H4.gif \
    src/img/cards/H5.gif \
    src/img/cards/H6.gif \
    src/img/cards/H7.gif \
    src/img/cards/H8.gif \
    src/img/cards/H9.gif \
    src/img/cards/Joker_02.gif \
    src/img/cards/S1.gif \
    src/img/cards/S10.gif \
    src/img/cards/S11.gif \
    src/img/cards/S12.gif \
    src/img/cards/S13.gif \
    src/img/cards/S2.gif \
    src/img/cards/S3.gif \
    src/img/cards/S4.gif \
    src/img/cards/S5.gif \
    src/img/cards/S6.gif \
    src/img/cards/S7.gif \
    src/img/cards/S8.gif \
    src/img/cards/S9.gif \
    src/img/cards/B.png \
    src/img/cards/Joker_01.png \
    src/img/pool_table/pool_table.png \
    src/img/pool_table/pool_table_@2X.png \
    src/img/roughcloth/roughcloth.png \
    src/img/roughcloth/roughcloth_@2X.png \
    src/doxyfile

RESOURCES += \
    src/resources.qrc
