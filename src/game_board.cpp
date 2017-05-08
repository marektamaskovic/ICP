#include "game_board.h"
#include "ui_game_board.h"


extern session_t currentSession;

int game_board::a = 0;


game_board::game_board(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game_board)
{
    this->setMinimumHeight(100);
    this->setMinimumWidth(100);
    this->setVisible(true);
    this->id = this->a;
    this->a++;
    this->grid = new QGridLayout();
    this->setLayout(grid);
    ui->setupUi(this);

}

game_board::~game_board()
{
    this->a--;
    delete this->grid;
    delete ui;
}

int game_board::update(QVector<QPushButton *> *list)
{
    delete this->grid;
    this->grid = new QGridLayout();
//    qDebug() << "g->update : " << this->id ;
    for(int i = 0; i < 13; i++)
    {
//        qDebug() << "deck" << i << "\n";
        int j = 0;
        QWidget *w = new QWidget();
        w->setStyleSheet("background-image: url(:/t/img/pool_table/pool_table.png);");
        QVBoxLayout *g = new QVBoxLayout(w);
        g->setSpacing(0);


        for(auto label = list[i].begin();
            label != list[i].end();
            ++label, ++j)
        {
            if(i == 12){
                auto label = list[i].back();
                connect(label, SIGNAL (released()), this, SLOT(waste_card()));
                g->addWidget(label);
                break;
            }
            else{
                g->addWidget((*label));
                connect(*label, SIGNAL (released()), this, SLOT(send_card()));
                QSpacerItem *s;
                if( i < 4 || i == 11)
                    s = new QSpacerItem(10, -202, QSizePolicy::Fixed, QSizePolicy::Fixed);
                else
                    s = new QSpacerItem(10, -160, QSizePolicy::Fixed, QSizePolicy::Fixed);
                if(++label != list[i].end())
                    g->addItem(s);
                label--;
            }
        }
        if (list[i].size() == 0){
//            qDebug() << "foundation-bg: " << i;
            QPushButton *label = new QPushButton();
            if(i==12)
                connect(label, SIGNAL (released()), this, SLOT(waste_card()));
            else
                connect(label, SIGNAL (released()), this, SLOT(send_card()));
            std::string style = "font-size: 1pt; border: none; background-image: url(:/img/cards/foundation.png);";
            label->setStyleSheet(style.data());
            label->setMaximumWidth(145);
            label->setMinimumSize(145, 202);
            std::string s = "e" + std::to_string(i);
            label->setText(QString::fromStdString(s));
            g->addWidget(label);
        }
        QSpacerItem *s = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding);
        g->addItem(s);
        w->setLayout(g);
        if(i < 4)
            this->grid->addWidget(w, 0, i + 3, 1, 1);
        else if(i > 3 && i < 11)
            this->grid->addWidget(w, 1, i - 4, 1, 1);
        else if(i == 11)
            this->grid->addWidget(w, 0, 1, 1, 1);
        else
            this->grid->addWidget(w, 0, 0, 1, 1);
    }
    this->setLayout(grid);
    this->repaint();


    return 0;
}


void game_board::send_card()
{
    if(reinterpret_cast<Table*>(parent())->session_id < 0){
        qDebug() << "SEND CARD ERROR U FAG";
        return;
    }
    const QString s = reinterpret_cast<QPushButton*>(sender())->text();
//    qDebug() << "card_chosen: " << s;
    NEXT_MOVE.push_back(s);

    if(NEXT_MOVE.size() == 2){
        if(q_move_card() == 0)
            qDebug() << "successfuly moved cards!";
        else
            qDebug() << "can't move this cards!";
        reinterpret_cast<Table*>(parent())->update();
    }
}

void game_board::waste_card()
{
    if(reinterpret_cast<Table*>(parent())->session_id < 0){
        qDebug() << "WASTE CARD ERROR U FAG";
        return;
    }
//    qDebug() << "waste_card()";
    int curr_id = reinterpret_cast<Table*>(parent())->session_id;
    currentSession.slot[curr_id]->decks[12]->dequeue(currentSession.slot[curr_id]->decks[11]);
    reinterpret_cast<Table*>(parent())->update();
    return;
}


int game_board::q_move_card(){
    command_t *cmd = new command_t;

    std::string deck;
    if(NEXT_MOVE.back()[0] == 'e')
        deck = NEXT_MOVE.back().toStdString().substr(1);
    else
        deck = find_card_in_deck(NEXT_MOVE.back());
    if(deck == "not_found"){
        return 1;
    }

    cmd->type = moveCard_CMD;
    cmd->args.push_back(deck);
    cmd->args.push_back(NEXT_MOVE.front().toStdString());

    moveCardDeco(cmd);
    // update();
    NEXT_MOVE.pop_back();
    NEXT_MOVE.pop_back();
    return 0;
}

std::string game_board::find_card_in_deck(QString &s){

    int game_id = reinterpret_cast<Table*>(parent())->session_id;

    for(int i = 0; i < 13; i++){
        for(unsigned card_ind = 0;
            card_ind != currentSession.slot[game_id]->decks[i]->cards.size();
            card_ind++)
        {
            Card c = currentSession.slot[game_id]->decks[i]->cards[card_ind];
            std::string text = std::to_string(c.number);
            switch(c.color){
            case(Club):
                text.append("C");
                break;
            case(Diamond):
                text.append("D");
                break;
            case(Spade):
                text.append("S");
                break;
            case(Heart):
                text.append("H");
                break;
            }
            if(!std::strcmp(text.c_str(), s.toStdString().c_str())){
                return std::to_string(i);
            }
        }
    }

    return "not_found";
}

void game_board::clean_board()
{
    delete this->grid;
    this->grid = new QGridLayout();
    QWidget *w = new QWidget();
    w->setStyleSheet("background-image: url(:/t/img/pool_table/pool_table.png);");
    QVBoxLayout *g = new QVBoxLayout(w);
    QSpacerItem *s = new QSpacerItem(100, 100, QSizePolicy::Expanding, QSizePolicy::Expanding);
    g->addItem(s);
    this->grid->addWidget(w, 0, 0, 8, 8);
    return;

}


