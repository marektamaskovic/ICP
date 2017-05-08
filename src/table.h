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
typedef QVector<QPushButton*> deck_ui_t;

namespace Ui {
    class Table;
}

/**
 * @brief      Table class includes all needed components for one game. That includes all buttons, game board with cards and other hidden objects.
 */
class Table : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief      Constructor
     *
     * @param      parent  The parent
     * @param[in]  r       row where this table is located in main window grid
     * @param[in]  c       column where this table is located in main window grid
     */
    explicit Table(QWidget *parent, int r, int c);

    /**
     * @brief      Destroys the object.
     */
    ~Table();

    /**
     * @brief      redraw table
     *
     * @return     If successful returns 0 otherwise non-zero value;
     */
    int update();

    /**
     * row where this table is located in main window grid
     */
    int row;

    /**
     * column where this table is located in main window grid
     */
    int column;

    /**
     * @see deck
     * All decks in game
     * 11   = stack
     * 12   = waste
     * 0-3  = pileau
     * 4-10 = foundation
     */
    deck_ui_t decks_ui[13];

    /**
     * session id
     */
    int session_id = -1;

private:
    /**
     * @brief      Gets the card.
     *
     * @param      Card&
     *
     * @return     The card as QPushButton.
     */
    QPushButton *get_card(Card&);

    /**
     * @brief      Gets the card name.
     *
     * @param      Card*
     *
     * @return     The card name.
     */
    std::string get_card_name(Card*);
    
    /**
     * Ui specifier
     */
    Ui::Table *ui;

    /**
     * Layout for this object.
     */
    QGridLayout *grid;

public slots:

    /**
     * @brief      Creates a game slot.
     */
    void create_game_slot(void);

    /**
     * @brief      Loads a game slot.
     */
    void load_game_slot(void);

    /**
     * @brief      Saves a game slot.
     */
    void save_game_slot(void);

    /**
     * @brief      Hint slot.
     */
    void hint_slot(void);

    /**
     * @brief      Undo slot.
     */
    void undo_slot(void);
};

#endif // TABLE_H
