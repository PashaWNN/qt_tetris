#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTimer"
#include "controller.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void new_game();

private slots:
    void on_action_quit_triggered();

    void on_action_new_game_triggered();

    void on_btn_start_clicked();

    void tick();

    void on_btn_pause_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    controller *ctrl = new controller();
    int key = 0;
    int lines = 0;
    bool paused = false;
    bool eventFilter(QObject* watched, QEvent* event);
};

#endif // MAINWINDOW_H
