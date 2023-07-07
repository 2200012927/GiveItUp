#include "banner.h"
#include "ui_banner.h"
#include <QPainter>
#include <QRect>
#include <QImage>

void banner::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    int W = this->width();
    int H = this->height();

    QRect *rect = new QRect(0, 0, W, H);
    QImage *image = new QImage(":/banner/images/banner.png");
    painter.drawImage(*rect, *image);
}

banner::banner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::banner)
{
    ui->setupUi(this);

}

banner::~banner()
{
    delete ui;
}
