#ifndef TABLE_H
#define TABLE_H

#include <QWidget>
#include <QApplication>
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

#include "core.h"
#include "classes.h"
#include "save.h"
#include "game_board.h"

// FIXME to card;
typedef QVector<QLabel*> deck_ui_t;

namespace Ui {
    class Table;
}

class Table : public QWidget
{
    Q_OBJECT

public:
    // TODO if is game present => not allow creating new one
    explicit Table(QWidget *parent);
    ~Table();
    int update();
    int show();
    int send();

    /*
     * 0-3 - pileau decks
     * 4-10 - foundation decks
     * 11 - waste
     * 12 - stack
     */
    deck_ui_t decks_ui[13];
    int session_id = -1;
private:
    QLabel *get_card(Card&);
    Ui::Table *ui;
    QGridLayout *grid;
    int draw_table(void);
public slots:
    void create_game_slot(void);
    void load_game_slot(void);
    void save_game_slot(void);
    void hint_slot(void);
    void undo_slot(void);
    void quit_game_slot(void);
};

#endif // TABLE_H
