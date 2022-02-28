#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include"startgame.h"
#include"rules.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
   // void mousePressEvent(QMouseEvent* mousePressEventArgs);
    void paintEvent(QPaintEvent* paintEventArgs);

private slots:

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_actionauthor_triggered();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    startgame* stgame;
    rules myrules;
};
#endif // MAINWINDOW_H
