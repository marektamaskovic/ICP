#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "table.h"
#include "core.h"
#include "classes.h"

extern session_t currentSession;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    grid = new QGridLayout();
    grid->setEnabled(true);
    Table *t = new Table(this, 0, 0);
    grid->addWidget(t, 0, 0, 1, 1);
    Table *tt = new Table(this, 0, 1);
    grid->addWidget(tt, 0, 1, 1, 1);
    Table *ttt = new Table(this, 1, 0);
    grid->addWidget(ttt, 1, 0, 1, 1);
    Table *tttt = new Table(this, 1, 1);
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

void MainWindow::delete_t()
{
    Table *native = reinterpret_cast<Table*>(sender()->parent());
    int r = native->row;
    int c = native->column;
    delete native;
    currentSession.openSlot[native->session_id] = false;
    delete currentSession.slot[native->session_id];
    native->session_id = -1;
    Table *t = new Table(this, r, c);
    grid->addWidget(t, r, c, 1, 1);

}
