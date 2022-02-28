#ifndef NEWGAME_H
#define NEWGAME_H

#include <QDialog>
#include<QPainter>
#include"game.h"
#include<QMouseEvent>
#include<QMessageBox>
#include<QLabel>
#include<windows.h>

namespace Ui {
class newGame;
}

class newGame : public QDialog
{
    Q_OBJECT

public:
    explicit newGame(QWidget *parent = nullptr);
    ~newGame();
    signals:
        void back_to_menu();
private slots:
    void on_pushButton_clicked();

protected:
    void mousePressEvent(QMouseEvent* mousePressEventArgs);
    void paintEvent(QPaintEvent* paintEventArgs);
private:

    QLabel *main_label;
    battleShips _game;
    enum VH{VERTICAL, HORIZONTAL};
    VH direction;
    Ui::newGame *ui;

};

#endif // NEWGAME_H
