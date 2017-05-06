#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QDebug>
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QList>

#include "table.h"

namespace Ui {
class game_board;
}

class game_board : public QWidget
{
    Q_OBJECT

public:
    explicit game_board(QWidget *parent = 0);
    ~game_board();
    QGridLayout *grid = nullptr;
    int update(QVector<QLabel*> *);
    int id;
    static int a;

private:
    Ui::game_board *ui;
};

#endif // GAME_BOARD_H
