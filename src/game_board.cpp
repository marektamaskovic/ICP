#include "src/game_board.h"
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

int game_board::update(QVector<QLabel *> *list)
{
    qDebug() << "g->update : " << this->id ;
    for(int i = 0; i < 13; i++)
    {
        qDebug() << "deck" << i << "\n";
        int j = 0;
        QWidget *w = new QWidget();
        QGridLayout *g = new QGridLayout(w);
        g->setSpacing(-120);

        for(auto label = list[i].begin();
            label != list[i].end();
            ++label, ++j)
        {
//            std::string s = (*label)->text().toStdString();
//            this->grid->addWidget((*label), j, i, 1, 1);
            if(i == 12){
                g->addWidget(list[i].back(), j, 0, 1, 1);
                break;
            }
            else{
                g->addWidget((*label), j, 0, 1, 1);
                QSpacerItem *s = new QSpacerItem(10, -120, QSizePolicy::Fixed, QSizePolicy::Fixed);
                g->addItem(s, ++j, 0, 1, 1);
            }
        }
        QSpacerItem *s = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding);
        g->addItem(s, j, 0, 1, 1);
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


