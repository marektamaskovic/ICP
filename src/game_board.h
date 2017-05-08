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
#include <QMimeData>
#include <QDrag>

#include "table.h"
#include "core.h"
#include "classes.h"

namespace Ui {
class game_board;
}

/**
 * @brief      Class for game board. This class includes all cards shown on table.
 * @see Table
 */
class game_board : public QWidget
{
    Q_OBJECT

public:
    explicit game_board(QWidget *parent = 0);   ///< game_board constructor
    ~game_board();                              ///< game_board destructor

    /**
     * @brief      Update game_board after moving card.
     *
     * @param      QVector<QPushButton *>  vector of all cards.
     *
     * @return     If successful returns 0 else non-zero value.
     */
    int update(QVector<QPushButton *> *);

    /**
     * @brief      Push card to next_move and if right conditions are met, then it moves specified card.
     *
     * @return     if successful returns 0 else non-zero value.
     */
    int q_move_card();

    /**
     * @brief      Find card in deck
     *
     * @param      s     Card name e.g. "2S" or "11D".
     *
     * @return     If successful, return string where is stored deck index in which is card located. Otherwise is returned value "not-found".
     */
    std::string find_card_in_deck(QString &s);

    QGridLayout *grid = nullptr;                ///< Grid layout where are cards stored
    int id;                                     ///< Id of game_board
    static int a;                               ///< Number of existing game_boards in specific moment
    QVector<QString> next_move;                 ///< Here are stored information about next move

private:
    /**
     * Ui specifier;
     */
    Ui::game_board *ui;

public slots:
    /**
     * @brief      Sends a card.
     */
    void send_card();
    /**
     * @brief      Moves card from stack deck to waste deck
     */
    void waste_card();
};


#endif // GAME_BOARD_H
