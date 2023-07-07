#ifndef BANNER_H
#define BANNER_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class banner;
}

class banner : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *event);

public:
    explicit banner(QWidget *parent = nullptr);
    ~banner();

private:
    Ui::banner *ui;
};

#endif // BANNER_H
