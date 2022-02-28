#ifndef STARTGAME_H
#define STARTGAME_H

#include <QMainWindow>

#include<QPainter>
#include"game.h"
#include<QMouseEvent>
#include<QMessageBox>
#include<QLabel>
#include<windows.h>
#include<QPixmap>
#include<QMouseEvent>


namespace Ui {
class startgame;
}

class startgame : public QMainWindow
{
    Q_OBJECT

public:
    explicit startgame(QWidget *parent = nullptr);
    ~startgame();

signals:
    void back_to_menu();

protected:
    void mousePressEvent(QMouseEvent* mousePressEventArgs);
    void paintEvent(QPaintEvent* paintEventArgs);

private slots:
    void on_actionExit_triggered();

    void on_actionSave_triggered();

    void on_actionAuthor_triggered();

private:
    Ui::startgame *ui;

   // QLabel *main_label;
    battleShips _game;
    enum VH{VERTICAL, HORIZONTAL};
    VH direction;

public:
    int load();
private:

};


#endif // STARTGAME_H
