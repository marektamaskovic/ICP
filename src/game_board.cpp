#include "src/game_board.h"
#include "ui_game_board.h"

extern session_t currentSession;

int game_board::a = 0;
QVector<QString> NEXT_MOVE;

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
    qDebug() << "g->update : " << this->id ;
    for(int i = 0; i < 13; i++)
    {
        qDebug() << "deck" << i << "\n";
        int j = 0;
        QWidget *w = new QWidget();
        QVBoxLayout *g = new QVBoxLayout(w);
        g->setSpacing(0);


        for(auto label = list[i].begin();
            label != list[i].end();
            ++label, ++j)
        {
            connect(*label, SIGNAL (released()), this, SLOT(send_card()));
            if(i == 12){
                g->addWidget(list[i].back());
                break;
            }
            else{
                g->addWidget((*label));
                QSpacerItem *s = new QSpacerItem(10, -160, QSizePolicy::Fixed, QSizePolicy::Fixed);
                if(++label != list[i].end())
                    g->addItem(s);
                label--;
            }
        }
        if (list[i].size() == 0){
            qDebug() << "foundation-bg: " << i;
            QPushButton *label = new QPushButton();
            std::string style = "background-image: url(:/img/cards/foundation.png);";
            label->setStyleSheet(style.data());
            label->setMaximumWidth(145);
            label->setMinimumSize(145, 202);
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

    this->repaint();


    return 0;
}


void game_board::send_card()
{
    const QString s = reinterpret_cast<QPushButton*>(sender())->text();
    qDebug() << "card_chosesn: " << s;
    NEXT_MOVE.push_back(s);

    if(NEXT_MOVE.size() == 2){
        if(q_move_card() == 0)
            qDebug() << "successfuly moved cards!";
        else
            qDebug() << "can't move this cards!";
    }
}


int q_move_card(){

    return 0;
}


