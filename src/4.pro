#-------------------------------------------------
#
# Project created by QtCreator 2017-05-04T08:46:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = hra2017
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
        mainwindow.cpp \
    classes.cpp \
    core.cpp \
    save.cpp \
    table.cpp \
    game_board.cpp 

HEADERS  += mainwindow.h \
    classes.h \
    color.h \
    core.h \
    json.hpp \
    save.h \
    table.h \
    game_board.h 

FORMS    += mainwindow.ui \
    ui/klondike.ui \
    table.ui \
    game_board.ui 

DISTFILES += \
    hra2017 \
    hra2017-cli \
    img/cards/C1.gif \
    img/cards/C10.gif \
    img/cards/C11.gif \
    img/cards/C12.gif \
    img/cards/C13.gif \
    img/cards/C2.gif \
    img/cards/C3.gif \
    img/cards/C4.gif \
    img/cards/C5.gif \
    img/cards/C6.gif \
    img/cards/C7.gif \
    img/cards/C8.gif \
    img/cards/C9.gif \
    img/cards/D1.gif \
    img/cards/D10.gif \
    img/cards/D11.gif \
    img/cards/D12.gif \
    img/cards/D13.gif \
    img/cards/D2.gif \
    img/cards/D3.gif \
    img/cards/D4.gif \
    img/cards/D5.gif \
    img/cards/D6.gif \
    img/cards/D7.gif \
    img/cards/D8.gif \
    img/cards/D9.gif \
    img/cards/H1.gif \
    img/cards/H10.gif \
    img/cards/H11.gif \
    img/cards/H12.gif \
    img/cards/H13.gif \
    img/cards/H2.gif \
    img/cards/H3.gif \
    img/cards/H4.gif \
    img/cards/H5.gif \
    img/cards/H6.gif \
    img/cards/H7.gif \
    img/cards/H8.gif \
    img/cards/H9.gif \
    img/cards/Joker_02.gif \
    img/cards/S1.gif \
    img/cards/S10.gif \
    img/cards/S11.gif \
    img/cards/S12.gif \
    img/cards/S13.gif \
    img/cards/S2.gif \
    img/cards/S3.gif \
    img/cards/S4.gif \
    img/cards/S5.gif \
    img/cards/S6.gif \
    img/cards/S7.gif \
    img/cards/S8.gif \
    img/cards/S9.gif \
    img/cards/B.png \
    img/cards/Joker_01.png \
    img/pool_table/pool_table.png \
    img/pool_table/pool_table_@2X.png \
    img/roughcloth/roughcloth.png \
    img/roughcloth/roughcloth_@2X.png \
    doxyfile \

RESOURCES += \
    resources.qrc 
