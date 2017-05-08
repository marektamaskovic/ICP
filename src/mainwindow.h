#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>

namespace Ui {
class MainWindow;
}

/**
 * @brief      Class for main window.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	/**
	 * @brief      Constructor
	 *
	 * @param      parent  The parent
	 */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * @brief      Destroys the object.
     */
    ~MainWindow();

    /**
     * Grid layout of games in main window.
     */
    QGridLayout *grid;
public slots:

	/**
	 * @brief      Quit from specified game.
	 */
    void delete_t();

private:
	/**
	 * Ui specifier.
	 */
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
