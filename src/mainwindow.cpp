#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "table.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QGridLayout *grid = new QGridLayout();
    grid->setEnabled(true);
    Table *t = new Table(nullptr);
    grid->addWidget(t, 0, 0, 1, 1);
    Table *tt = new Table(nullptr);
    grid->addWidget(tt, 0, 1, 1, 1);
    Table *ttt = new Table(this);
    grid->addWidget(ttt, 1, 0, 1, 1);
    Table *tttt = new Table(this);
    grid->addWidget(tttt, 1, 1, 1, 1);

    QWidget *window = new QWidget();
    window->setLayout(grid);

    // Set QWidget as the central layout of the main window
    this->setObjectName("main_window");
    this->setWindowTitle("Klondike");
    this->setStyleSheet("#main_window{background-image:url(':/t/img/pool_table/pool_table.png')}");
    setCentralWidget(window);
}

MainWindow::~MainWindow()
{
    delete ui;
}
