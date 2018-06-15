#include "QDebug"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "QKeyEvent"

const int KEY_UP = 1;
const int KEY_RIGHT = 2;
const int KEY_LEFT = 3;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->timer = new QTimer(this);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(tick()));
    ui->game->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_quit_triggered()
{
    this->close();
}

void MainWindow::on_action_new_game_triggered()
{
    new_game();
}

void MainWindow::new_game() {
    ctrl = new controller();
    lines = 0;
    ui->lbl_lines->setText("Линии: 0");
    ui->btn_pause->setEnabled(true);

    this->timer->start(300);
}

void MainWindow::on_btn_start_clicked()
{
    new_game();
}

void MainWindow::tick() {
    int dx = 0;
    bool rotate = false;
    switch (key) {
    case KEY_UP:
        rotate = true;
        break;
    case KEY_RIGHT:
        dx++;
        break;
    case KEY_LEFT:
        dx--;
        break;
    }
    int i = ctrl->do_game_tick(dx, rotate);
    if (i == -1) {
        //Game over
        qDebug() << "Game over";
        this->timer->stop();
        ui->btn_pause->setEnabled(false);
    } else if (i > 0) {
        lines += i;
        ui->lbl_lines->setText("Линии: " + QString::number(lines));
    }
    ui->game->repaint();
}

bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == ui->game && event->type() == QEvent::Paint) {
            QPainter painter;
            painter.begin(ui->game);
            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.drawImage(0,0,QImage(":/bg.png"));

            for (int i = 0; i < ctrl->M; i++) {
                for (int j = 0; j < ctrl->N; j++) {
                    if (ctrl->field[i][j] != 0) {
                        //qDebug() << "there is a block";
                        painter.drawImage(j*15, i*15, QImage(
                           ":/sprites/tile" + QString::number(ctrl->field[i][j]) + ".png"));
                    }
                }
            }
            for (int i = 0; i < 4; i++) {
                painter.drawImage(ctrl->a[i].x*15, ctrl->a[i].y*15, QImage(":/sprites/tile"+QString::number(ctrl->color)+".png"));
            }
            painter.end();
            return true; // return true if you do not want to have the child widget paint on its own afterwards, otherwise, return false.
        }
    else if (!key && event->type() == QEvent::KeyPress) {
        QKeyEvent* k = static_cast<QKeyEvent*>(event);
        if (k->key() == Qt::Key_Left) {
            key = KEY_LEFT;
        } else if (k->key() == Qt::Key_Right) {
            key = KEY_RIGHT;
        } else if (k->key() == Qt::Key_Up) {
            key = KEY_UP;
        } else if (k->key() == Qt::Key_Down) {
            this->timer->setInterval(50);
        }
    }
    else if (event->type() == QEvent::KeyRelease) {
        key = 0;
        this->timer->setInterval(300);
    }
        return QObject::eventFilter(watched, event);
}


void MainWindow::on_btn_pause_clicked()
{
    if (!this->paused) {
        this->paused = true;
        this->timer->stop();
        ui->btn_pause->setText("Продолжить");
    } else {
        this->paused = false;
        this->timer->start();
        ui->btn_pause->setText("Пауза");
    }
}
