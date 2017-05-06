/*
 * TODO
 * change enabled to false when you create Table()
 * change enabled of button when you create or load game to active
 * add slot to quit button
 * add slot to hint button
 *
*/

#include "table.h"
#include "ui_table.h"
#include "core.h"
#include "classes.h"

extern session_t currentSession;


Table::Table(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Table)
{

    this->grid = new QGridLayout(this);

    QPushButton *new_game_b     = new QPushButton("New Game");
    QPushButton *load_game_b    = new QPushButton("Load Game");
    QPushButton *save_game_b    = new QPushButton("Save Game");
    QPushButton *undo_b         = new QPushButton("Undo");
    QPushButton *hint_b         = new QPushButton("Hint");
    QPushButton *quit_game_b    = new QPushButton("Quit Game");

    this->grid->addWidget(new_game_b,     0,0,1,1);
    connect(new_game_b, SIGNAL (released()), this, SLOT (create_game_slot()));

    this->grid->addWidget(load_game_b,    0,1,1,1);
    connect(load_game_b, SIGNAL (released()), this, SLOT (load_game_slot()));

    this->grid->addWidget(save_game_b,    0,2,1,1);
    connect(save_game_b, SIGNAL (released()), this, SLOT (save_game_slot()));

    this->grid->addWidget(undo_b,         0,3,1,1);
    connect(undo_b, SIGNAL (released()), this, SLOT (undo_slot()));

    this->grid->addWidget(hint_b,         0,4,1,1);
    connect(hint_b, SIGNAL (released()), this, SLOT (hint_slot()));

    this->grid->addWidget(quit_game_b,    0,5,1,1);
    connect(quit_game_b, SIGNAL (released()), this, SLOT (quit_game_slot()));

    QSpacerItem *spacer = new QSpacerItem(1, 2, QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->grid->addItem(spacer, 2, 0, 1, 8);
    spacer = new QSpacerItem(1, 2, QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->grid->addItem(spacer, 0, 6, 2, 1);

    game_board *g_board = new game_board(this);
    g_board->setObjectName("game_board");

    this->grid->addWidget(g_board, 1, 0, 1, 8);

    this->setLayout(this->grid);
    ui->setupUi(this);
}

Table::~Table()
{
    // FIXME clear vecotors
    delete ui;
}


int Table::update()
{
    game_board *g = this->findChild<game_board*>("game_board");
    if(g == nullptr){
        qDebug() << "alsjdh";
        return 1;
    }

    int curr_game = currentSession.currentGame;
    Game *game = currentSession.slot[curr_game];

    //clear decks

    for(int i = 0; i < 13; i++)
    {
        qDebug() << "Cleaning deck: " << i;
        while(this->decks_ui[i].size() > 0)
        {
            this->decks_ui[i].pop_back();
        }
    }
    // update decks
    int k = 0;
    for(int i = 0; i < 13; i++, k++)
    {
        int j = 4;
        for(auto card = game->decks[i]->cards.begin();
            card != game->decks[i]->cards.end();
            card++, j++)
        {
            this->decks_ui[i].push_back(this->get_card(*card));
//            this->grid->addWidget(this->get_card(*card), j,k,1,1);
        }
        qDebug() << i << " : " << this->decks_ui[i].length();
    }

    g->update(this->decks_ui);
    g->repaint();
    return 0;
}

int Table::draw_table()
{
    qDebug() << "Draw table func";
    QGridLayout *game_board = this->findChild<QGridLayout*>("game_board");

    if(game_board == nullptr){
        qDebug() << "returnujem";
        return 1;
    }
    // Remove all widgets on table
    for(int idx = 0; idx < game_board->count(); ++idx)
    {
        QLayoutItem *item = game_board->itemAt(idx);
        delete item->widget();
    }

    delete game_board;
    game_board = new QGridLayout();

    qDebug() << "blabla";

    // Create all cards
    for(int i = 0; i < 13; i++)
    {
        qDebug() << "deck" << i << "\n";
        QGridLayout *deck = new QGridLayout();
        int j = 0;
        for(auto label = decks_ui[i].begin();
            label != decks_ui[i].end();
            ++label, ++j)
        {
            deck->addWidget(*label, j, 0, 1, 1);
        }

        if(i < 4)
            game_board->addItem(deck, i + 3, 0, 1, 1);
        else if( i > 4 && i < 10)
            game_board->addItem(deck, i - 4, 1, 1, 1);
        else
            game_board->addItem(deck, i-11, 0, 1, 1);
    }

    this->grid->addItem(game_board, 1, 0, 1, 8);
    ui->setupUi(this);
    
    return 0;
}

QLabel *Table::get_card(Card &c)
{
    // FIXME only prototype
    // TODO fix QLabel to card object with background

    std::string name = "";

    c.visible ? name.append("V") : name.append("N");
    name.append(std::to_string(static_cast<int>(c.color)));
    name.append(std::to_string(c.number));

    QLabel *label = new QLabel(name.data());

    if(label == nullptr)
    {
        qDebug() << "operator `new` didn't allocate QLabel in function `table::get_card`\n";
        //TODO clean up and exit
    }
    return label;
}

void Table::create_game_slot(void)
{
    // TODO add show game
    session_id = currentSession.isSpace();
    createGame(&currentSession);
    qDebug() << "currentGame: " << currentSession.currentGame << "\n";
    this->update();
    this->repaint();
    qApp->processEvents();

}

void Table::load_game_slot(void)
{
    // TODO add show game
    QString filename;
    filename = QFileDialog::getOpenFileName(this,
        tr("Load Game"), QDir::homePath(), tr("Save Files (*)"));
    if(filename == "")
    {
        return;
    }
    std::string a = filename.toStdString();
    load_game(a, &currentSession);
    qDebug() << "Loading game from: " << currentSession.currentGame << "\n";
    this->update();
}

void Table::save_game_slot(void)
{
    if(session_id < 0)
    {
        QMessageBox::information(
            this,
            tr("Klondike"),
            tr("You have to [start/load] game to save it.") );
        return;
    }
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               QDir::homePath()+"/untitled.klndk",
                               tr("Save game files (*.klndk)"));
    if(fileName == "")
    {
        return;
    }
    qDebug() << "Saving game to: " << fileName;

    std::string tmp = fileName.toStdString();
    save(tmp, *currentSession.slot[session_id]);

    return;
}

void Table::hint_slot()
{
    Move *storeMove = currentSession.slot[currentSession.currentGame]->hint();
    std::string text = "Move from:";
    text.append(std::to_string(storeMove->from));
    text.append(" to: ");
    text.append(std::to_string(storeMove->to));
    QMessageBox::information(
        this,
        tr("Klondike"),
        tr(text.data()));
    return;
}

void Table::undo_slot()
{
    if(this->session_id < 0){
        qDebug() << "UNDO ERROR U FAG!";
        return;
    }
    currentSession.slot[this->session_id]->history = undo(currentSession.slot[this->session_id]->history);
}

void Table::quit_game_slot()
{
    qDebug() << "session_id: " << session_id;
    if(this->session_id < 0){
        qDebug() << "QUIT ERROR U FAG!";
        return;
    }
    currentSession.openSlot[this->session_id] = false;
    delete currentSession.slot[this->session_id];
}
