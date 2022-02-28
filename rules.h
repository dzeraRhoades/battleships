#ifndef RULES_H
#define RULES_H

#include <QDialog>
#include<QPainter>

namespace Ui {
class rules;
}

class rules : public QDialog
{
    Q_OBJECT

public:
    explicit rules(QWidget *parent = nullptr);
    ~rules();

private slots:
    void on_pushButton_clicked();
protected:
    void paintEvent(QPaintEvent* paintEventArgs);


private:
    Ui::rules *ui;
};

#endif // RULES_H
