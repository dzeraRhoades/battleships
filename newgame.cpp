#include "newgame.h"
#include "ui_newgame.h"


newGame::newGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newGame)
{
    ui->setupUi(this);

    main_label = new QLabel(this);
    main_label->setGeometry(700, 20, 900, 100);
    main_label->setStyleSheet("font-size: 36px");
    main_label->setText("Place 1-deck ships");

    this->setFixedSize(QSize(1600, 900));
    this->setWindowTitle("Game");
    direction = HORIZONTAL;
}

newGame::~newGame()
{
    delete main_label;
    delete ui;
}

void newGame::on_pushButton_clicked()
{
    this->close();
    emit back_to_menu();


}

void newGame::paintEvent(QPaintEvent* paintEventArgs)
{
    Q_UNUSED(paintEventArgs);
    QPainter painter;
    painter.begin(this);
    _game.paint(painter);
}
void newGame::mousePressEvent(QMouseEvent* mousePressEventArgs)
{
    if (mousePressEventArgs->button() == Qt::MouseButton::RightButton){
        if(direction)
            direction = VERTICAL;
        else {
            direction = HORIZONTAL;
        }
    }
    if (mousePressEventArgs->button() != Qt::MouseButton::LeftButton)
    {
        return;
    }

    int x = mousePressEventArgs->x();
    int y = mousePressEventArgs->y();
    // checking the correct of click

    if(_game.game_step == battleShips::gameStep::LOCATION)
    {
        if(x < 400 || x > (400 + 511) || y < 200 || y > (200 + 511))
            return;

        // checking if we clicked the lines
        if ((x - 400) % 51 == 0 || (y - 200) % 51 == 0)
        {
            return;
        }
        // row = y, column = x
        int row = (y - 200) / 51;
        int column = (x - 400) / 51;

        // placing 1-deck ships
        if(_game.last_1deck_ships){
            switch (int result_of_click = _game.place_ship(column, row)) {
                case -1:
                QMessageBox::warning(this, "try again", "this field is not empty!");
                    break;

                case 0:
                if (!_game.last_1deck_ships)
                    main_label->setText("Place 2-deck ships");
                  repaint();
                  break;
                }
             return;
        }

        // placing 2-deck ships
        if(_game.last_2deck_ships)
        {

            if(direction) {
                switch (_game.place_ship(column, row, column + 1, row)) {

                case 0:
                    repaint();
                    break;
                case -1:
                    QMessageBox::warning(this, "try again", "entered coordinates are wrong!");
                    break;

                }
            }
            else
            {
                switch (_game.place_ship(column, row, column, row + 1)) {

                case 0:
                    repaint();
                    break;
                case -1:
                    QMessageBox::warning(this, "try again", "entered coordinates are wrong!");
                    break;
                }
            }

            if (!_game.last_2deck_ships)
                main_label->setText("Place 3-deck ships");

            return;

        }

        // placing 3-deck ships
        if(_game.last_3deck_ships)
        {

            if(direction) {
                switch (_game.place_ship(column, row, column + 2, row)) {

                case 0:
                    repaint();
                    break;
                case -1:
                    QMessageBox::warning(this, "try again", "entered coordinates are wrong!");
                    break;

                }
            }
            else
            {
                switch (_game.place_ship(column, row, column, row + 2)) {

                case 0:
                    repaint();
                    break;
                case -1:
                    QMessageBox::warning(this, "try again", "entered coordinates are wrong!");
                    break;
                }
            }

            if (!_game.last_3deck_ships)
                main_label->setText("Place 4-deck ships");
            return;

        }

        // placing 4-deck ships
        if(_game.last_4deck_ships)
        {

            if(direction) {
                switch (_game.place_ship(column, row, column + 3, row)) {

                case 0:
                    repaint();
                    break;
                case -1:
                    QMessageBox::warning(this, "try again", "entered coordinates are wrong!");
                    break;

                }
            }
            else
            {
                switch (_game.place_ship(column, row, column, row + 3)) {

                case 0:
                    repaint();
                    break;
                case -1:
                    QMessageBox::warning(this, "try again", "entered coordinates are wrong!");
                    break;
                }
            }
            if(!_game.last_4deck_ships){
                main_label->setText("Game started, your move");
                _game.game_step = battleShips::gameStep::PLAY;
                _game.bot_field_filling();
                repaint();
            }
            return;
        }
    }
    else if(_game.game_step == battleShips::gameStep::PLAY)
    {
        // check if we clicked wrong palce
        if(x < 1000 || x > (1000+511) || y < 200 || y > (200 + 511))
            return;
        // check if we clicked field lines
        if ((x - 1000) % 51 == 0 || (y - 200) % 51 == 0)
            return;

        int row = (y - 200) / 51;
        int column = (x - 1000) / 51;

        switch (_game.player_move(column, row)) {
        case -1:
           // QMessageBox::warning(this, "", "you've already shooted this field");
            break;

        case 1:
            main_label->setText("you missed");
            repaint();

            main_label->setText("enemy's move");
            Sleep(1000);

            while(!_game.bot_step())
            {
                repaint();
                main_label->setText("our ship is damaged!!!");
                Sleep(1000);
                if (_game.game_over())
                {
                    main_label->setText("Enemy won the game(((");
                    _game.game_step = battleShips::gameStep::BOT_WIN;
                    repaint();
                    return;
                }
            }
            repaint();
            main_label->setText("enemy missed his shot");
            Sleep(1000);
            main_label->setText("your move");
            break;

        case 0:
            main_label->setText("you've got this motherfucker!");
            repaint();
            Sleep(1000);
            if (_game.game_over())
            {
                main_label->setText("You won the game!!!");
                _game.game_step = battleShips::gameStep::PLAYER_WIN;
                repaint();
                return;
            }
            main_label->setText("your move");
            break;

        }


    }

}


