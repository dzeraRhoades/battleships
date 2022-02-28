#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<iostream>
#include<QPainter>
#include<QLabel>
#include<QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setStyleSheet("background-color: black;");
    this->setFixedSize(QSize(1600, 900));

    // инициализируем новое окно
   // new_game_win = new newGame();

    stgame = new startgame();
    connect(stgame, &startgame::back_to_menu, this, &MainWindow::show);
    // связываем слот вывода первого окна с сигналом кнопки второго окна
    //connect(new_game_win, &newGame::back_to_menu, this, &MainWindow::show);

}

MainWindow::~MainWindow()
{
    delete stgame;
    delete ui;
}

// кнопка new game
void MainWindow::on_pushButton_clicked()
{

    delete stgame;
    stgame = new startgame;
    connect(stgame, &startgame::back_to_menu, this, &MainWindow::show);
    stgame->show();
    this->close();



}

void MainWindow::paintEvent(QPaintEvent* paintEventArgs)
{
    Q_UNUSED(paintEventArgs);
    QPainter my_painter;
    my_painter.begin(this);
    my_painter.drawImage(QRect(0, 0, 1600, 900), QImage(":/pics/main_background.jpg"));
    //my_painter.setBackground()



}

void MainWindow::on_pushButton_4_clicked()
{
    close();
}

void MainWindow::on_pushButton_3_clicked()
{
    myrules.exec();

}

// author
void MainWindow::on_pushButton_5_clicked()
{
    QMessageBox::information(this, "author", "Made by Kesaev Vladislav Igorevich\n M8O-111B-20 group.");
}



void MainWindow::on_pushButton_2_clicked()
{
    delete stgame;
    stgame = new startgame;
    connect(stgame, &startgame::back_to_menu, this, &MainWindow::show);
    if(stgame->load())
        return;
    stgame->show();
    this->close();
}
