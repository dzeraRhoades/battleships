#include"game.h"
#include"iostream"
#include"QPainter"
#include<string>


//-------------------------------------------------------------------
// Constructor
battleShips::battleShips()
{
   game_step = LOCATION;
   for(int i = 0; i < 10; i ++)
       for(int j = 0; j < 10; j++)
           game_field[i][j] = EMPTY;


   img_short_ship = new QImage("C:/ShittyQt/short_ship.jpg");

   is_ship_destroyed_dir = NONE;
   is_ship_destroyed_num = 0;
}
//-------------------------------------------------------------------
battleShips:: ~battleShips()
{
    delete img_short_ship;
    stack.clean();
}
//-------------------------------------------------------------------
void battleShips::paint(QPainter& painter)
{
    int i, j;
    if(game_step == LOCATION)
    {
        painter.setPen(QColor::fromRgb(0, 0, 255));
        painter.setBrush(QColor(255, 255, 255));
        painter.drawRect(QRect(400, 200, 511, 511));
        int x = 400;
        int y = 200;

        for(i = 0; i < 10; i++)
        {
            // пишем буквы сверху поля
            letters  = (char)('a'+i);
            letterss = QString::fromStdString(letters);
            painter.drawText(QRect(x + 20, y - 50, x+40, y - 10), letterss);

            x+=51;
            painter.drawLine(x, y, x, y + 511);
        }
        x = 400;
        for(i = 0; i < 10; i++)
        {
            // пишем цифры сбоку поля
            numbers = std::to_string(i+1);
            nums = QString::fromStdString(numbers);
            painter.drawText(QRect(x - 50, y + 10, x-10, y + 40), nums);

            y+=51;
            painter.drawLine(x, y, x + 511, y);
        }
        y = 200;

        for (int i = 0; i < 10; i++)
            for(j = 0; j < 10; j++)
            {
                if (game_field[i][j] == SHIP)
                {
                    // рисуем корабль
                    *img_short_ship = draw_deck(i, j);
                    painter.drawImage(QRect(400 + 51 * i+1, 200 + 51 * j+1, 50, 50), *img_short_ship);
                }
            }
    }
    else if(game_step == PLAY) // now game starts
    {

        // drawing gamers field
        painter.setBrush(QColor::fromRgb(255, 255, 255));
        painter.setPen(QColor::fromRgb(0, 0, 255));
        painter.drawRect(QRect(200, 200, 511, 511));
        int x = 200;
        int y = 200;

        for(i = 0; i < 10; i++)
        {
            letters  = (char)(97+i);
            letterss = QString::fromStdString(letters);
            painter.drawText(QRect(x + 20, y - 50, x+40, y - 10), letterss);

            x+=51;
            painter.drawLine(x, y, x, y + 511);

        }
        x = 200;
        for(i = 0; i < 10; i++)
        {
            numbers = std::to_string(i+1);
            nums = QString::fromStdString(numbers);
            painter.drawText(QRect(x - 50, y + 10, x-10, y + 40), nums);

            y+=51;
            painter.drawLine(x, y, x + 511, y);
        }
        y = 200;

        for (int i = 0; i < 10; i++)
            for(j = 0; j < 10; j++)
            {
                if (game_field[i][j] == SHIP)
                {
                    painter.setBrush(QColor::fromRgb(0, 0, 255));
                    //painter.drawEllipse(x + 51 * i, y + 51 * j, 48, 48);
                    *img_short_ship = draw_deck(i, j);
                    painter.drawImage(QRect(x + 51 * i+1, y + 51 * j+1, 50, 50), *img_short_ship);
                }
                if (game_field[i][j] == EXPLODED)
                {
                    painter.setBrush(QColor::fromRgb(255, 0, 0));
                    //painter.drawEllipse(x + 51 * i, y + 51 * j, 48, 48);
                    *img_short_ship = draw_deck(i, j);
                    painter.drawImage(QRect(x + 51 * i+1, y + 51 * j+1, 50, 50), *img_short_ship);
                }
                if (game_field[i][j] == MISSED)
                {
                    painter.setBrush(QColor(255, 255, 255));
                    painter.setPen(QColor(0, 0, 0));
                    painter.drawEllipse(x + 12 + 51 * i, y + 12 + 51 * j, 30, 30);
                    //img_short_ship->load(":/pics/hole.jpg");
                    //painter.drawImage(QRect(x + 51 * i+1, y + 51 * j+1, 50, 50), *img_short_ship);
                }
            }

        // drawing the bot field
        painter.setPen(QColor::fromRgb(255, 0, 0));
        painter.setBrush(QColor::fromRgb(255, 255, 255));

        painter.drawRect(QRect(1000, 200, 511, 511));
        x = 1000;
        y = 200;



        for(i = 0; i < 10; i++)
        {
            letters  = (char)(97+i);
            letterss = QString::fromStdString(letters);
            painter.drawText(QRect(x + 20, y - 50, x+40, y - 10), letterss);

            x+=51;
            painter.drawLine(x, y, x, y + 511);
        }
        x = 1000;
        for(i = 0; i < 10; i++)
        {
            numbers = std::to_string(i+1);
            nums = QString::fromStdString(numbers);
            painter.drawText(QRect(x - 50, y + 10, x-10, y + 40), nums);

            y+=51;
            painter.drawLine(x, y, x + 511, y);
        }
        y = 200;

        for (int i = 0; i < 10; i++)
            for(j = 0; j < 10; j++)
            {
//                if (bot_game_field[i][j] == SHIP)
//                {
////
//                    *img_short_ship = draw_bot_deck(i, j);
//                    painter.drawImage(QRect(x + 51 * i+1, y + 51 * j+1, 50, 50), *img_short_ship);
//                }
                if (bot_game_field[i][j] == MISSED)
                {
//                    img_short_ship->load(":/pics/hole.jpg");
//                    painter.drawImage(QRect(x + 51 * i+1, y + 51 * j+1, 50, 50), *img_short_ship);
                    painter.setBrush(QColor(255, 255, 255));
                    painter.setPen(QColor(0, 0, 0));
                    painter.drawEllipse(x + 12 + 51 * i, y + 12 + 51 * j, 30, 30);
                }
                if (bot_game_field[i][j] == EXPLODED)
                {
                    *img_short_ship = draw_bot_deck(i, j);
                    painter.drawImage(QRect(x + 51 * i+1, y + 51 * j+1, 50, 50), *img_short_ship);
                }

            }
    }
    else if(game_step == PLAYER_WIN)
    {
        img_short_ship->load(":/pics/povezlo.jpg");
        painter.drawImage(QRect(0, 0, 1600, 900), *img_short_ship);
    }
    else if(game_step == BOT_WIN)
    {
        img_short_ship->load(":/pics/nepovezlo.jpg");
        painter.drawImage(QRect(0, 0, 1600, 900), *img_short_ship);
    }



}

//-------------------------------------------------------------------
int battleShips :: place_ship(int x, int y)
{
    int i, j;
    for (i = (y - 1); i <= (y + 1); i++)
        for (j = (x - 1); j <= (x + 1); j++)
        {
            if(i < 0 || i > 9 || j < 0 || j > 9)
                continue;
            if (game_field[j][i] != EMPTY)
                return -1;
        }
    game_field[x][y] = SHIP;
    last_1deck_ships--;


    return 0;
}
//-------------------------------------------------------------------
int battleShips::place_ship(int ax, int ay, int bx, int by)
{
    int i, j;
    if (bx > 9 || by > 9)
        return -1;

    for (i = ay - 1; i <= by + 1; i++)
    {
        for(j = ax - 1; j <= bx + 1; j++)
        {
            if(i < 0 || i > 9 || j < 0 || j > 9)
                continue;
            if (game_field[j][i] != EMPTY)
                return -1;
        }
    }

    for (i = ay; i <= by; i++)
        for(j = ax; j <= bx; j++)
            game_field[j][i] = SHIP;



    int ship_length = bx - ax + by - ay;
    switch (ship_length) {
    case 1:
        last_2deck_ships--;
        break;

    case 2:
        last_3deck_ships--;
        break;

    case 3:
        last_4deck_ships--;
        break;

    }
    return 0;
}
//-------------------------------------------------------------------
// puting random ships in bot field
void battleShips::bot_field_filling()
{
    int i, j, k, h;
    int mistake = 0;
    int x, y;
    int vh;
    int shipl = 1;
    srand(time(NULL));

    // make all field empty
    for(i = 0; i < 10; i++)
        for(j = 0; j < 10; j++)
            bot_game_field[i][j] = EMPTY;

    //using rand() we fill all ships
    for (i = 0; i < 4; i++)
    {
        shipl = 4 - i;

        while(shipl)
        {
          // shipl = i;
            mistake = 0;
            x = rand() % 10;
            y = rand() % 10;
            vh = rand() % 2;
            if (vh)
            {
                if (x + i > 9)
                    continue;
                for (h = y - 1; h <= y + 1; h++)
                {
                    if(mistake)
                        break;
                    for(j = x - 1; j <= (x+i) + 1; j++)
                    {
                        if(h < 0 || h > 9 || j < 0 || j > 9)
                            continue;
                        if (bot_game_field[h][j] == SHIP)
                        {
                            mistake = 1;
                            break;
                        }
                    }
                }
                if(!mistake)
                {
                    for (k = 0; k < i + 1; k++)
                    {
                        bot_game_field[y][x+k] = SHIP;

                    }
                    shipl--;
                }
            }
            else
            {
                if(y + i > 9)
                    continue;

                for (h = y - 1; h <= (y+i) + 1; h++)
                {
                    if(mistake)
                        break;
                    for(j = x - 1; j <= x + 1; j++)
                    {
                        if(h < 0 || h > 9 || j < 0 || j > 9)
                            continue;
                        if (bot_game_field[h][j] == SHIP)
                        {
                            mistake = 1;
                            break;
                        }
                    }
                }
                if(!mistake)
                {
                    for (k = 0; k < i + 1; k++)
                    {
                        bot_game_field[y+k][x] = SHIP;

                    }
                    shipl--;
                }

            }
        }
    }
}

//-------------------------------------------------------------------
int battleShips :: player_move(int x, int y)
{
    if (bot_game_field[x][y] == SHIP)
    {
        bot_game_field[x][y] = EXPLODED;
        if(is_bot_ship_destroyed(x, y))
        {
            is_ship_destroyed_dir = NONE;
            round_bot_destroyed_ships(x, y);
        }
        is_ship_destroyed_dir = NONE;
        return 0;
    }
    if (bot_game_field[x][y] == MISSED || bot_game_field[x][y] == EXPLODED)
    {
        return -1;
    }
    if (bot_game_field[x][y] == EMPTY)
    {
        bot_game_field[x][y] = MISSED;
        return 1;
    }
    return 0;

}
//-------------------------------------------------------------------
int battleShips::bot_step()
{
    int x, y;
    srand(time(NULL));
    while(1)
    {
        if(stack.is_empty())
        {
            x = rand() % 10;
            y = rand() % 10;

            if (game_field[x][y] == EMPTY)
            {
                game_field[x][y] = MISSED;
                return 1;
            }
            if (game_field[x][y] == SHIP)
            {
                stack.push(x, y);
                game_field[x][y] = EXPLODED;
                if(is_ship_destroyed(x, y))
                {
                    is_ship_destroyed_dir = NONE;
                    round_destroyed_ships(x, y);
                }
                is_ship_destroyed_dir = NONE;
                return 0;
            }
        }
        else
        {
            int res = bot_logic();
            if (res == -1)
                return bot_step();

            return res;

        }

    }
    return 0;

}
//-------------------------------------------------------------------
int battleShips::bot_logic()
{


    while(1)
    {
        int x = stack.top->x;
        int y = stack.top->y;

        if (stack.direction != botDir::NONE)
        {
            if(stack.direction == botDir::UP)
            {
                if(game_field[x][y - 1] == EXPLODED || game_field[x][y - 1] == MISSED || (y-1) < 0)
                {
                    while(stack.row != 1)
                    {
                        stack.pop();
                    }
                    stack.direction = botDir::DOWN;
                    continue;
                }
                else if(game_field[x][y - 1] == SHIP)
                {
                    game_field[x][y - 1] = EXPLODED;
                    stack.push(x, y - 1);
                    if(is_ship_destroyed(x, y-1))
                    {
                        is_ship_destroyed_dir = NONE;
                        round_destroyed_ships(x, y-1);
                    }
                    is_ship_destroyed_dir = NONE;
                    return 0;
                }
                else if(game_field[x][y -1] == EMPTY)
                {
                    game_field[x][y - 1] = MISSED;
                    std::cout<<x<<", "<<y-1<<std::endl;
                    return 1;
                }
            }
            else if(stack.direction == botDir::DOWN)
            {
                if(game_field[x][y + 1] == EXPLODED || game_field[x][y + 1] == MISSED || (y+1) > 9)
                {
                    while(stack.row != 1)
                    {
                        stack.pop();

                    }
                    stack.direction = botDir::NONE;
                    stack.pop();
                    return -1;
                }
                else if(game_field[x][y + 1] == SHIP)
                {
                    game_field[x][y + 1] = EXPLODED;
                    stack.push(x, y + 1);
                    if(is_ship_destroyed(x, y+1))
                    {
                        is_ship_destroyed_dir = NONE;
                        round_destroyed_ships(x, y+1);
                    }
                    is_ship_destroyed_dir = NONE;
                    return 0;
                }
                else if(game_field[x][y +1] == EMPTY)
                {
                    game_field[x][y + 1] = MISSED;
                    std::cout<<x<<", "<<y+1<<std::endl;
                    return 1;
                }
            }
            else if(stack.direction == botDir::RIGHT)
            {
                if(game_field[x + 1][y] == EXPLODED || game_field[x + 1][y] == MISSED || (x + 1) > 9)
                {
                    while(stack.row != 1)
                    {
                        stack.pop();
                    }
                    stack.direction = botDir::LEFT;
                    continue;
                }
                else if(game_field[x + 1][y] == SHIP)
                {
                    game_field[x + 1][y] = EXPLODED;
                    stack.push(x + 1, y);
                    if(is_ship_destroyed(x+1, y))
                    {
                        is_ship_destroyed_dir = NONE;
                        round_destroyed_ships(x+1, y);
                    }
                    is_ship_destroyed_dir = NONE;
                    return 0;
                }
                else if(game_field[x + 1][y] == EMPTY)
                {
                    game_field[x + 1][y] = MISSED;
                    std::cout<<x+1<<", "<<y<<std::endl;
                    return 1;
                }
            }
            else if(stack.direction == botDir::LEFT)
            {
                if(game_field[x - 1][y] == EXPLODED || game_field[x - 1][y] == MISSED || (x - 1) < 0)
                {
                    while(stack.row != 1)
                    {
                        stack.pop();
                    }
                    stack.direction = botDir::NONE;
                    stack.pop();
                    return -1;
                }
                else if(game_field[x - 1][y] == SHIP)
                {
                    game_field[x - 1][y] = EXPLODED;
                    stack.push(x - 1, y);
                    if(is_ship_destroyed(x-1, y))
                    {
                        is_ship_destroyed_dir = NONE;
                        round_destroyed_ships(x-1, y);
                    }
                    is_ship_destroyed_dir = NONE;
                    return 0;
                }
                else if(game_field[x - 1][y] == EMPTY)
                {
                    game_field[x - 1][y] = MISSED;
                    std::cout<<x-1<<", "<<y<<std::endl;
                    return 1;
                }
            }
        }
        else
        {
            if(game_field[x][y-1] != EXPLODED && game_field[x][y-1] != MISSED && (y-1) >= 0)
            {
                if(game_field[x][y-1] == EMPTY)
                {
                    game_field[x][y-1] = MISSED;
                    return 1;
                }
                else
                {
                    stack.direction = botDir::UP;
                    stack.push(x, y-1);
                    game_field[x][y-1] = EXPLODED;
                    if(is_ship_destroyed(x, y-1))
                    {
                        is_ship_destroyed_dir = NONE;
                        round_destroyed_ships(x, y-1);
                    }
                    is_ship_destroyed_dir = NONE;
                    return 0;
                }
            }
            if(game_field[x][y+1] != EXPLODED && game_field[x][y+1] != MISSED && (y+1) <= 9)
            {
                if(game_field[x][y+1] == EMPTY)
                {
                    game_field[x][y+1] = MISSED;
                    std::cout<<x<<", "<<y+1<<std::endl;
                    return 1;
                }
                else
                {
                    stack.direction = botDir::DOWN;
                    stack.push(x, y+1);
                    game_field[x][y+1] = EXPLODED;
                    if(is_ship_destroyed(x, y+1))
                    {
                        is_ship_destroyed_dir = NONE;
                        round_destroyed_ships(x, y+1);
                    }
                    is_ship_destroyed_dir = NONE;
                    return 0;
                }
            }
            if(game_field[x+1][y] != EXPLODED && game_field[x+1][y] != MISSED && (x+1) <=9)
            {
                if(game_field[x+1][y] == EMPTY)
                {
                    game_field[x+1][y] = MISSED;
                    std::cout<<x+1<<", "<<y<<std::endl;
                    return 1;
                }
                else
                {
                    stack.direction = botDir::RIGHT;
                    stack.push(x+1, y);
                    game_field[x+1][y] = EXPLODED;
                    if(is_ship_destroyed(x+1, y))
                    {
                        is_ship_destroyed_dir = NONE;
                        round_destroyed_ships(x+1, y);
                    }
                    is_ship_destroyed_dir = NONE;
                    return 0;
                }
            }
            if(game_field[x-1][y] != EXPLODED && game_field[x-1][y] != MISSED && (x-1) >= 0)
            {
                if(game_field[x-1][y] == EMPTY)
                {
                    game_field[x-1][y] = MISSED;
                    std::cout<<x-1<<", "<<y<<std::endl;
                    return 1;
                }
                else
                {
                    stack.direction = botDir::LEFT;
                    stack.push(x-1, y);
                    game_field[x-1][y] = EXPLODED;
                    if(is_ship_destroyed(x-1, y))
                    {
                        is_ship_destroyed_dir = NONE;
                        round_destroyed_ships(x-1, y);
                    }
                    is_ship_destroyed_dir = NONE;
                    return 0;
                }
            }
            stack.pop();
            return -1;
        }
    }
}
//-------------------------------------------------------------------
int battleShips::game_over()
{
    int i, j;
    int player_win = 1;
    int bot_win = 1;

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            if(bot_game_field[i][j] == SHIP)
            {
                player_win = 0;
                break;
            }
        }
    }

    if(player_win)
    {
        return 1;
    }

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            if(game_field[i][j] == SHIP)
            {
                bot_win = 0;
                break;
            }
        }
    }
    if(bot_win)
    {
        return 2;
    }

    return 0;
}
//-------------------------------------------------------------------
void battleShips::save()
{
    std::ofstream saving;
    saving.open("save.txt");
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
        {
            saving<<int(game_field[i][j]);
            saving<<int(bot_game_field[i][j]);
        }
    saving.close();

}
//-------------------------------------------------------------------
int battleShips::load()
{

    std::ifstream loading;
    loading.open("save.txt");
    if(!loading.is_open())
        return -2;
    else
    {
        if(loading.peek() == EOF)
            return -1;

        game_step = PLAY;
        for(int i = 0; i< 10; i++)
            for(int j = 0; j < 10; j++)
            {
                game_field[i][j] = (field_type)(loading.get() - 48);
                bot_game_field[i][j] = (field_type)(loading.get() - 48);
            }

        loading.close();
    }
    return 0;


}
//-------------------------------------------------------------------

QImage battleShips::draw_deck(int x, int y)
{
    QImage image;

    if(game_field[x][y] == SHIP)
    {
        if (x > 0 && (game_field[x - 1][y] == SHIP || game_field[x-1][y] == EXPLODED))
        {
            if (x < 9 && (game_field[x + 1][y] == SHIP || game_field[x+1][y] == EXPLODED))
            {
                image.load(":/pics/deck_h.png");
                return image;
            }
            else
            {
                image.load(":/pics/deck_front_h.png");
                return image;
            }
        }
        else
        {
            if (x < 9 && (game_field[x + 1][y] == SHIP || game_field[x+1][y] == EXPLODED))
            {
                image.load(":/pics/deck_back_h.png");
                return image;
            }
        }


        if(y > 0 && (game_field[x][y-1] == SHIP || game_field[x][y-1] == EXPLODED))
        {
            if(y < 9 && (game_field[x][y+1] == SHIP || game_field[x][y+1] == EXPLODED))
            {
                image.load(":/pics/deck_v.png");
                return image;
            }
            else
            {
                image.load(":/pics/deck_front_v.png");
                return image;
            }
        }
        else
        {
            if(y < 9 && (game_field[x][y+1] == SHIP || game_field[x][y+1] == EXPLODED))
                image.load(":/pics/deck_back_v.png");
            else
                image.load(":/pics/deck.png");
        }
    }
    else
    {
        image.load(":/pics/exploded.png");
    }
    return image;
}

//-------------------------------------------------------------------

QImage battleShips::draw_bot_deck(int x, int y)
{
    QImage image;

    if(bot_game_field[x][y] == SHIP)
    {
        if (x > 0 && (bot_game_field[x - 1][y] == SHIP || bot_game_field[x-1][y] == EXPLODED))
        {
            if (x < 9 && (bot_game_field[x + 1][y] == SHIP || bot_game_field[x+1][y] == EXPLODED))
            {
                image.load(":/pics/deck_h_2.png");
                return image;
            }
            else
            {
                image.load(":/pics/deck_front_h_2.png");
                return image;
            }
        }
        else
        {
            if (x < 9 && (bot_game_field[x + 1][y] == SHIP || bot_game_field[x+1][y] == EXPLODED))
            {
                image.load(":/pics/deck_back_h_2.png");
                return image;
            }
        }


        if(y > 0 && (bot_game_field[x][y-1] == SHIP || bot_game_field[x][y-1] == EXPLODED))
        {
            if(y < 9 && (bot_game_field[x][y+1] == SHIP || bot_game_field[x][y+1] == EXPLODED))
            {
                image.load("C:/ShittyQt/pics/deck_v_2.png");
                return image;
            }
            else
            {
                image.load(":/pics/deck_front_v_2.png");
                return image;
            }
        }
        else
        {
            if(y < 9 && (bot_game_field[x][y+1] == SHIP || bot_game_field[x][y+1] == EXPLODED))
                image.load(":/pics/deck_back_v_2.png");
            else
                image.load(":/pics/deck_2.png");
        }
    }
    else
    {
        image.load(":/pics/exploded_2.png");
    }
    return image;
}

//-------------------------------------------------------------------
int battleShips::is_ship_destroyed(int x, int y)
{
    if(is_ship_destroyed_dir == NONE)
    {
        // checking upper position
        if ((game_field[x][y-1] == EXPLODED || game_field[x][y-1] == SHIP) && y > 0)
        {
            if(game_field[x][y-1] == EXPLODED)
            {
                is_ship_destroyed_dir = UP;
                if(!is_ship_destroyed(x, y-1))
                    return 0;
            }
            else
            {
                return 0;
            }
        }

        // checking lowwer position
        if ((game_field[x][y+1] == EXPLODED || game_field[x][y+1] == SHIP) && y < 9)
        {
            if(game_field[x][y+1] == EXPLODED)
            {
                is_ship_destroyed_dir = DOWN;
                if(!is_ship_destroyed(x, y+1))
                    return 0;
            }
            else
            {
                return 0;
            }
        }

        // checking right position
        if ((game_field[x+1][y] == EXPLODED || game_field[x+1][y] == SHIP) && x < 9)
        {
            if(game_field[x+1][y] == EXPLODED)
            {
                is_ship_destroyed_dir = RIGHT;
                if(!is_ship_destroyed(x+1, y))
                    return 0;
            }
            else
            {
                return 0;
            }
        }

        // checking left position
        if ((game_field[x-1][y] == EXPLODED || game_field[x-1][y] == SHIP) && x > 0)
        {
            if(game_field[x-1][y] == EXPLODED)
            {
                is_ship_destroyed_dir = LEFT;
                if(!is_ship_destroyed(x-1, y))
                    return 0;
            }
            else
            {
                return 0;
            }
        }
        return 1;

    }
    else
    {
        if (is_ship_destroyed_dir == UP)
        {
            if(game_field[x][y-1] == EXPLODED && y > 0)
            {
                if(!is_ship_destroyed(x, y-1))
                    return 0;
                else
                    return 1;
            }
            else
            {
                if(game_field[x][y-1] == SHIP && y > 0)
                    return 0;
                else
                    return 1;
            }
        }

        if (is_ship_destroyed_dir == DOWN)
        {
            if(game_field[x][y+1] == EXPLODED && y < 9)
            {
                if(!is_ship_destroyed(x, y+1))
                    return 0;
                else
                    return 1;
            }
            else
            {
                if(game_field[x][y+1] == SHIP && y < 9)
                    return 0;
                else
                    return 1;
            }
        }

        if (is_ship_destroyed_dir == RIGHT)
        {
            if(game_field[x+1][y] == EXPLODED && x < 9)
            {
                if(!is_ship_destroyed(x+1, y))
                    return 0;
                else
                    return 1;
            }
            else
            {
                if(game_field[x+1][y] == SHIP && x < 9)
                    return 0;
                else
                    return 1;
            }
        }

        if (is_ship_destroyed_dir == LEFT)
        {
            if(game_field[x-1][y] == EXPLODED && x > 0)
            {
                if(!is_ship_destroyed(x-1, y))
                    return 0;
                else
                    return 1;
            }
            else
            {
                if(game_field[x-1][y] == SHIP && x > 0)
                    return 0;
                else
                    return 1;
            }
        }
    }

   // is_ship_destroyed_dir = NONE;
    return 1;

}

void battleShips::round_destroyed_ships(int x, int y)
{
    int i;
    if(is_ship_destroyed_dir == NONE)
    {
        if (game_field[x][y-1] == EXPLODED && y > 0)
        {
            is_ship_destroyed_dir = UP;
            for(int i = 0; i < 3; i++)
            {
                if(x > 0 && y + 1 - i < 9)
                    game_field[x-1][y+1-i] = MISSED;
                if(x < 9 && y + 1 - i < 9)
                    game_field[x+1][y+1-i] = MISSED;
            }
            round_destroyed_ships(x, y-1);
        }

        // checking lowwer position
        if (game_field[x][y+1] == EXPLODED && y < 9)
        {
            is_ship_destroyed_dir = DOWN;
            for(int i = 0; i < 3; i++)
            {
                if (x > 0 && y - 1 + i > 0)
                    game_field[x-1][y-1+i] = MISSED;
                if (x < 9 && y - 1 + i > 0)
                    game_field[x+1][y-1+i] = MISSED;
            }
            round_destroyed_ships(x, y+1);
        }

        // checking right position
        if (game_field[x+1][y] == EXPLODED && x < 9)
        {
            is_ship_destroyed_dir = RIGHT;
            for(int i = 0; i < 3; i++)
            {
                if(y > 0 && x - 1 + i > 0)
                    game_field[x-1+i][y-1] = MISSED;
                if(y < 9 && x - 1 + i > 0)
                    game_field[x-1+i][y+1] = MISSED;
            }
            round_destroyed_ships(x+1, y);
        }

        // checking left position
        if (game_field[x-1][y] == EXPLODED && x > 0)
        {
            is_ship_destroyed_dir = LEFT;
            for(int i = 0; i < 3; i++)
            {
                if(y > 0 && x + 1 -i < 9)
                    game_field[x+1-i][y-1] = MISSED;
                if(y < 9 && x + 1 - i < 9)
                    game_field[x+1-i][y+1] = MISSED;
            }
            round_destroyed_ships(x-1, y);
        }

        if(is_ship_destroyed_dir == NONE)
        {
            for(i = 0; i < 3; i++)
            {
                if(y > 0 && x - 1 + i >= 0 && x - 1 + i <= 9)
                    game_field[x-1+i][y-1] = MISSED;
                if(y < 9 && x - 1 + i >= 0 && x - 1 + i <= 9)
                    game_field[x-1+i][y+1] = MISSED;
            }
            if(x > 0)
                game_field[x-1][y] = MISSED;
            if(x < 9)
                game_field[x+1][y] = MISSED;
        }
        else
        {
            if(is_ship_destroyed_dir == RIGHT && game_field[x-1][y] != EXPLODED && x > 0)
                game_field[x-1][y] = MISSED;
            if(is_ship_destroyed_dir == UP && game_field[x][y+1] != EXPLODED && y < 9)
                game_field[x][y+1] = MISSED;
            if(is_ship_destroyed_dir == DOWN && game_field[x][y-1] != EXPLODED && y > 0)
                game_field[x][y-1] = MISSED;
            if(is_ship_destroyed_dir == LEFT && game_field[x+1][y] != EXPLODED && x < 9)
                game_field[x+1][y] = MISSED;

        }
    }
    else
    {
        if(is_ship_destroyed_dir == UP)
        {
            for(int i = 0; i < 3; i++)
            {
                if(x > 0 && y + 1 - i >=0 && y + 1 - i <= 9)
                    game_field[x-1][y+1-i] = MISSED;
                if(x < 9 && y + 1 - i >=0 && y + 1 - i <= 9)
                    game_field[x+1][y+1-i] = MISSED;
            }
            if(y > 0)
            {
                if(game_field[x][y-1] == EXPLODED)
                {
                    round_destroyed_ships(x, y-1);
                }
                else
                {
                    game_field[x][y-1] = MISSED;
                }
            }

        }

        if(is_ship_destroyed_dir == DOWN)
        {
            for(int i = 0; i < 3; i++)
            {
                if(x > 0 && y - 1 + i >= 0 && y - 1 + i <= 9)
                    game_field[x-1][y-1+i] = MISSED;
                if(x < 9 && y - 1 + i >= 0 && y - 1 + i <= 9)
                    game_field[x+1][y-1+i] = MISSED;
            }
            if(y < 9)
            {
                if(game_field[x][y+1] == EXPLODED)
                {
                    round_destroyed_ships(x, y+1);
                }
                else
                {
                    game_field[x][y+1] = MISSED;
                }
            }
        }

        if(is_ship_destroyed_dir == RIGHT)
        {
            for(int i = 0; i < 3; i++)
            {
                if(y > 0 && x - 1 + i >= 0 && x - 1 + i <= 9)
                    game_field[x-1+i][y-1] = MISSED;
                if(y < 9 && x - 1 + i >= 0 && x - 1 + i <= 9)
                    game_field[x-1+i][y+1] = MISSED;
            }
            if(x < 9)
            {
                if(game_field[x+1][y] == EXPLODED)
                {
                    round_destroyed_ships(x+1, y);
                }
                else
                {
                    game_field[x+1][y] = MISSED;
                }
            }

        }

        if(is_ship_destroyed_dir == LEFT)
        {
            for(int i = 0; i < 3; i++)
            {
                if(y > 0 && x + 1 - i >= 0 && x + 1 - i <= 9)
                    game_field[x+1-i][y-1] = MISSED;
                if(y < 9 && x + 1 - i >= 0 && x + 1 - i <= 9)
                    game_field[x+1-i][y+1] = MISSED;
            }
            if(x > 0)
            {
                if(game_field[x-1][y] == EXPLODED)
                {
                    round_destroyed_ships(x-1, y);
                }
                else
                {
                    game_field[x-1][y] = MISSED;
                }
            }

        }
    }

}

//-------------------------------------------------------------------
int battleShips::is_bot_ship_destroyed(int x, int y)
{
    if(is_ship_destroyed_dir == NONE)
    {
        // checking upper position
        if ((bot_game_field[x][y-1] == EXPLODED || bot_game_field[x][y-1] == SHIP) && y > 0)
        {
            if(bot_game_field[x][y-1] == EXPLODED)
            {
                is_ship_destroyed_dir = UP;
                if(!is_bot_ship_destroyed(x, y-1))
                    return 0;
            }
            else
            {
                return 0;
            }
        }

        // checking lowwer position
        if ((bot_game_field[x][y+1] == EXPLODED || bot_game_field[x][y+1] == SHIP) && y < 9)
        {
            if(bot_game_field[x][y+1] == EXPLODED)
            {
                is_ship_destroyed_dir = DOWN;
                if(!is_bot_ship_destroyed(x, y+1))
                    return 0;
            }
            else
            {
                return 0;
            }
        }

        // checking right position
        if ((bot_game_field[x+1][y] == EXPLODED || bot_game_field[x+1][y] == SHIP) && x < 9)
        {
            if(bot_game_field[x+1][y] == EXPLODED)
            {
                is_ship_destroyed_dir = RIGHT;
                if(!is_bot_ship_destroyed(x+1, y))
                    return 0;
            }
            else
            {
                return 0;
            }
        }

        // checking left position
        if ((bot_game_field[x-1][y] == EXPLODED || bot_game_field[x-1][y] == SHIP) && x > 0)
        {
            if(bot_game_field[x-1][y] == EXPLODED)
            {
                is_ship_destroyed_dir = LEFT;
                if(!is_bot_ship_destroyed(x-1, y))
                    return 0;
            }
            else
            {
                return 0;
            }
        }
        return 1;

    }
    else
    {
        if (is_ship_destroyed_dir == UP)
        {
            if(bot_game_field[x][y-1] == EXPLODED && y > 0)
            {
                if(!is_bot_ship_destroyed(x, y-1))
                    return 0;
                else
                    return 1;
            }
            else
            {
                if(bot_game_field[x][y-1] == SHIP && y > 0)
                    return 0;
                else
                    return 1;
            }
        }

        if (is_ship_destroyed_dir == DOWN)
        {
            if(bot_game_field[x][y+1] == EXPLODED && y < 9)
            {
                if(!is_bot_ship_destroyed(x, y+1))
                    return 0;
                else
                    return 1;
            }
            else
            {
                if(bot_game_field[x][y+1] == SHIP && y < 9)
                    return 0;
                else
                    return 1;
            }
        }

        if (is_ship_destroyed_dir == RIGHT)
        {
            if(bot_game_field[x+1][y] == EXPLODED && x < 9)
            {
                if(!is_bot_ship_destroyed(x+1, y))
                    return 0;
                else
                    return 1;
            }
            else
            {
                if(bot_game_field[x+1][y] == SHIP && x < 9)
                    return 0;
                else
                    return 1;
            }
        }

        if (is_ship_destroyed_dir == LEFT)
        {
            if(bot_game_field[x-1][y] == EXPLODED && x > 0)
            {
                if(!is_bot_ship_destroyed(x-1, y))
                    return 0;
                else
                    return 1;
            }
            else
            {
                if(bot_game_field[x-1][y] == SHIP && x > 0)
                    return 0;
                else
                    return 1;
            }
        }
    }

   // is_ship_destroyed_dir = NONE;
    return 1;

}
//-------------------------------------------------------------------

void battleShips::round_bot_destroyed_ships(int x, int y)
{
    int i;
    if(is_ship_destroyed_dir == NONE)
    {
        if (bot_game_field[x][y-1] == EXPLODED && y > 0)
        {
            is_ship_destroyed_dir = UP;
            for(int i = 0; i < 3; i++)
            {
                if(x > 0 && y + 1 - i < 9)
                    bot_game_field[x-1][y+1-i] = MISSED;
                if(x < 9 && y + 1 - i < 9)
                    bot_game_field[x+1][y+1-i] = MISSED;
            }
            round_bot_destroyed_ships(x, y-1);
        }

        // checking lowwer position
        if (bot_game_field[x][y+1] == EXPLODED && y < 9)
        {
            is_ship_destroyed_dir = DOWN;
            for(int i = 0; i < 3; i++)
            {
                if (x > 0 && y - 1 + i > 0)
                    bot_game_field[x-1][y-1+i] = MISSED;
                if (x < 9 && y - 1 + i > 0)
                    bot_game_field[x+1][y-1+i] = MISSED;
            }
            round_bot_destroyed_ships(x, y+1);
        }

        // checking right position
        if (bot_game_field[x+1][y] == EXPLODED && x < 9)
        {
            is_ship_destroyed_dir = RIGHT;
            for(int i = 0; i < 3; i++)
            {
                if(y > 0 && x - 1 + i > 0)
                    bot_game_field[x-1+i][y-1] = MISSED;
                if(y < 9 && x - 1 + i > 0)
                    bot_game_field[x-1+i][y+1] = MISSED;
            }
            round_bot_destroyed_ships(x+1, y);
        }

        // checking left position
        if (bot_game_field[x-1][y] == EXPLODED && x > 0)
        {
            is_ship_destroyed_dir = LEFT;
            for(int i = 0; i < 3; i++)
            {
                if(y > 0 && x + 1 -i <= 9)
                    bot_game_field[x+1-i][y-1] = MISSED;
                if(y < 9 && x + 1 - i <= 9)
                    bot_game_field[x+1-i][y+1] = MISSED;
            }
            round_bot_destroyed_ships(x-1, y);
        }

        if(is_ship_destroyed_dir == NONE)
        {
            for(i = 0; i < 3; i++)
            {
                if(y > 0 && x - 1 + i >= 0 && x - 1 + i <= 9)
                    bot_game_field[x-1+i][y-1] = MISSED;
                if(y < 9 && x - 1 + i >= 0 && x - 1 + i <= 9)
                    bot_game_field[x-1+i][y+1] = MISSED;
            }
            if(x > 0)
                bot_game_field[x-1][y] = MISSED;
            if(x < 9)
                bot_game_field[x+1][y] = MISSED;
        }
        else
        {
            if(is_ship_destroyed_dir == RIGHT && bot_game_field[x-1][y] != EXPLODED && x > 0)
                bot_game_field[x-1][y] = MISSED;
            if(is_ship_destroyed_dir == UP && bot_game_field[x][y+1] != EXPLODED && y < 9)
                bot_game_field[x][y+1] = MISSED;
            if(is_ship_destroyed_dir == DOWN && bot_game_field[x][y-1] != EXPLODED && y > 0)
                bot_game_field[x][y-1] = MISSED;
            if(is_ship_destroyed_dir == LEFT && bot_game_field[x+1][y] != EXPLODED && x < 9)
                bot_game_field[x+1][y] = MISSED;

        }
    }
    else
    {
        if(is_ship_destroyed_dir == UP)
        {
            for(int i = 0; i < 3; i++)
            {
                if(x > 0 && y + 1 - i >=0 && y + 1 - i <= 9)
                    bot_game_field[x-1][y+1-i] = MISSED;
                if(x < 9 && y + 1 - i >=0 && y + 1 - i <= 9)
                    bot_game_field[x+1][y+1-i] = MISSED;
            }
            if(y > 0)
            {
                if(bot_game_field[x][y-1] == EXPLODED)
                {
                    round_bot_destroyed_ships(x, y-1);
                }
                else
                {
                    bot_game_field[x][y-1] = MISSED;
                }
            }

        }

        if(is_ship_destroyed_dir == DOWN)
        {
            for(int i = 0; i < 3; i++)
            {
                if(x > 0 && y - 1 + i >= 0 && y - 1 + i <= 9)
                    bot_game_field[x-1][y-1+i] = MISSED;
                if(x < 9 && y - 1 + i >= 0 && y - 1 + i <= 9)
                    bot_game_field[x+1][y-1+i] = MISSED;
            }
            if(y < 9)
            {
                if(bot_game_field[x][y+1] == EXPLODED)
                {
                    round_bot_destroyed_ships(x, y+1);
                }
                else
                {
                    bot_game_field[x][y+1] = MISSED;
                }
            }
        }

        if(is_ship_destroyed_dir == RIGHT)
        {
            for(int i = 0; i < 3; i++)
            {
                if(y > 0 && x - 1 + i >= 0 && x - 1 + i <= 9)
                    bot_game_field[x-1+i][y-1] = MISSED;
                if(y < 9 && x - 1 + i >= 0 && x - 1 + i <= 9)
                    bot_game_field[x-1+i][y+1] = MISSED;
            }
            if(x < 9)
            {
                if(bot_game_field[x+1][y] == EXPLODED)
                {
                    round_bot_destroyed_ships(x+1, y);
                }
                else
                {
                    bot_game_field[x+1][y] = MISSED;
                }
            }

        }

        if(is_ship_destroyed_dir == LEFT)
        {
            for(int i = 0; i < 3; i++)
            {
                if(y > 0 && x + 1 - i >= 0 && x + 1 - i <= 9)
                    bot_game_field[x+1-i][y-1] = MISSED;
                if(y < 9 && x + 1 - i >= 0 && x + 1 - i <= 9)
                    bot_game_field[x+1-i][y+1] = MISSED;
            }
            if(x > 0)
            {
                if(bot_game_field[x-1][y] == EXPLODED)
                {
                    round_bot_destroyed_ships(x-1, y);
                }
                else
                {
                    bot_game_field[x-1][y] = MISSED;
                }
            }

        }
    }

}
//-------------------------------------------------------------------
