#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QGridLayout *grid;
    ~MainWindow();
public slots:
    void delete_t();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
