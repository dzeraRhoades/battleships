#include "startgame.h"
#include "ui_startgame.h"

startgame::startgame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::startgame)
{
    ui->setupUi(this);

    ui->main_label->setText("Place 1-deck ships");


    this->setFixedSize(QSize(1600, 900));
    this->setWindowTitle("Game");
    direction = HORIZONTAL;

}

startgame::~startgame()
{
    delete ui;
}




void startgame::paintEvent(QPaintEvent* paintEventArgs)
{
    Q_UNUSED(paintEventArgs);
    QPainter painter;
    painter.begin(this);
    painter.drawImage(QRect(0, 0, 1600, 900), QImage(":/pics/game_background.jpg"));
    _game.paint(painter);
}
void startgame::mousePressEvent(QMouseEvent* mousePressEventArgs)
{
    mousePressEventArgs->setAccepted(false);
    if (mousePressEventArgs->button() == Qt::MouseButton::RightButton && !_game.last_1deck_ships && _game.game_step == battleShips::gameStep::LOCATION){
        if(direction)
        {
            direction = VERTICAL;
            setCursor(QCursor(QPixmap(":/cursors/cursors/cursor_v.png")));
        }
        else {
            direction = HORIZONTAL;
            setCursor(QCursor(QPixmap(":/cursors/cursors/cursor_h.png")));

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
                //QMessageBox::warning(this, "try again", "this field is not empty!");
                    break;

                case 0:
                if (!_game.last_1deck_ships)
                {
                    ui->main_label->setText("Place 2-deck ships");
                    setCursor(QCursor(QPixmap(":/cursors/cursors/cursor_h.png")));
                }
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
                  //  QMessageBox::warning(this, "try again", "entered coordinates are wrong!");
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
                    //QMessageBox::warning(this, "try again", "entered coordinates are wrong!");
                    break;
                }
            }

            if (!_game.last_2deck_ships)
                ui->main_label->setText("Place 3-deck ships");

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
                   // QMessageBox::warning(this, "try again", "entered coordinates are wrong!");
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
                   // QMessageBox::warning(this, "try again", "entered coordinates are wrong!");
                    break;
                }
            }

            if (!_game.last_3deck_ships)
                ui->main_label->setText("Place 4-deck ships");
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
                  //  QMessageBox::warning(this, "try again", "entered coordinates are wrong!");
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
                   // QMessageBox::warning(this, "try again", "entered coordinates are wrong!");
                    break;
                }
            }
            if(!_game.last_4deck_ships){
                ui->main_label->setText("Game started, your move");
                _game.game_step = battleShips::gameStep::PLAY;
                _game.bot_field_filling();
                setCursor(QCursor(QPixmap(":/cursors/cursors/cursor.png")));
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
            QMessageBox::warning(this, "", "you've already shooted this field");
            break;

        case 1:
            ui->main_label->setText("you missed,enemy's move");
            removeEventFilter(this);

            repaint();
            Sleep(1000);

            while(!_game.bot_step())
            {
                repaint();
                ui->main_label->setText("our ship is damaged!!!");
                Sleep(1000);
                if (_game.game_over())
                {
                    ui->main_label->setText("Enemy won the game(((");
                    _game.game_step = battleShips::gameStep::BOT_WIN;
                    repaint();
                    return;
                }
            }

            repaint();
           ui->main_label->setText("your move");
            break;

        case 0:
            repaint();
            if (_game.game_over())
            {
//                ui->main_label->setAlignment(Qt::AlignVCenter);
//                ui->main_label->setGeometry(600, 400, 300, 100);

                ui->main_label->setText("You won the game!!!");
                _game.game_step = battleShips::gameStep::PLAYER_WIN;
                repaint();
                return;
            }
            ui->main_label->setText("your move");
            break;

        }


    }


}



void startgame::on_actionExit_triggered()
{
    this->close();
    emit back_to_menu();
}

void startgame::on_actionSave_triggered()
{

    if(_game.game_step == battleShips::gameStep::PLAY)
    {
        _game.save();
    }
    else
    {
        QMessageBox::warning(this, "wrong saving", "You can't save the game at this stage!");
    }
}

int startgame::load()
{
    int tmp = _game.load();
    if(tmp == -2)
    {
        QMessageBox::warning(this, "file isn't opened", "file save opening error");
        return 1;
    }
    else if(tmp == -1)
    {
        QMessageBox::warning(this, "empty", "the game wasn't saved");
        return 1;
    }
    else if(tmp == 0)
    {
        setCursor(QCursor(QPixmap(":/cursors/cursors/cursor.png")));
        ui->main_label->setText("Your move");
    }
    return 0;
}



void startgame::on_actionAuthor_triggered()
{
    QMessageBox::information(this, "author", "Made by Kesaev Vladislav Igorevich\n M8O-111B-20 group.");
}
