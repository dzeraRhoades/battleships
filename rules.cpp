#include "rules.h"
#include "ui_rules.h"

rules::rules(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rules)
{
    ui->setupUi(this);


    setFixedSize(1000, 500);

}

rules::~rules()
{
    delete ui;
}

void rules::paintEvent(QPaintEvent* paintEventArgs)

{
    Q_UNUSED(paintEventArgs);
    QPainter painter;
    painter.begin(this);
    painter.drawImage(QRect(0, 0, 1000, 500), QImage(":/pics/field_background"));

}

void rules::on_pushButton_clicked()
{
    close();
}
