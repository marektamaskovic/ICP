/********************************************************************************
** Form generated from reading UI file 'game_board.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_BOARD_H
#define UI_GAME_BOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_game_board
{
public:

    void setupUi(QWidget *game_board)
    {
        if (game_board->objectName().isEmpty())
            game_board->setObjectName(QStringLiteral("game_board"));
        game_board->resize(400, 300);

        retranslateUi(game_board);

        QMetaObject::connectSlotsByName(game_board);
    } // setupUi

    void retranslateUi(QWidget *game_board)
    {
        game_board->setWindowTitle(QApplication::translate("game_board", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class game_board: public Ui_game_board {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_BOARD_H
