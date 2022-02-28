#ifndef GAME_H
#define GAME_H
#include<QPainter>
#include <QLabel>
#include<random>
#include<windows.h>
#include"funcs.h"
#include<fstream>
#include<QPixmap>

#endif // GAME_H

class battleShips
{
private:
    MyStack stack;

    enum field_type {EMPTY, SHIP, EXPLODED, MISSED};
    field_type game_field[10][10];
    field_type bot_game_field[10][10];
private:
    QPixmap* short_ship;
    QImage* img_short_ship;

    std::string letters;
    std::string numbers;
    QString nums;
    QString letterss;

    botDir is_ship_destroyed_dir;
    int is_ship_destroyed_num;




public:
    int last_1deck_ships = 4;
    int last_2deck_ships = 3;
    int last_3deck_ships = 2;
    int last_4deck_ships = 1;



public:
    QImage draw_bot_deck(int, int);
    QImage draw_deck(int x, int y);
    int load();
    void save();
    int player_move(int column, int row);
    int bot_step();
    int bot_logic();
    int game_over();
    enum gameStep{LOCATION, PLAY, BOT_WIN, PLAYER_WIN};
    battleShips();
    ~battleShips();
    gameStep game_step;
    void paint(QPainter &painter);
    int place_ship(int column, int row);
    int place_ship(int ax, int ay, int bx, int by);
    void bot_field_filling();

private:
    int is_ship_destroyed(int, int);
    void round_destroyed_ships(int, int);
    int is_bot_ship_destroyed(int, int);
    void round_bot_destroyed_ships(int, int);
};
