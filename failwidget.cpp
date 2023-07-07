#include "failwidget.h"
#include "ui_failwidget.h"

#include <QPainter>
#include <QPixmap>
#include <QtMultimedia>

const int midPlace = 256;
const int splashWidth = 150;
const int splashHeight = 200;
const int retrySize = 70;
const int menuSize = 70;

void FailWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    int w = this->width();
    int h = this->height();

    QRect *rect = new QRect(0, 0, w, h);
    QImage *image = new QImage(":/background/images/background.bmp");
    painter.drawImage(*rect, *image);
}

FailWidget::FailWidget(int h, int p, int levelNum, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FailWidget)
{
    ui->setupUi(this);

    if (clickableLabel::soundS){
        QMediaPlayer * player = new QMediaPlayer(this);
        QAudioOutput * audioOutput = new QAudioOutput(this);
        QUrl * source = new QUrl("qrc:/sound/Sound/end/Die.mp3");
        player->setAudioOutput(audioOutput);
        player->setSource(*source);
        player->play();
    }

    LEVEL = levelNum;
    QPixmap pixSplash = QPixmap(":/images/images/dieSplash.png").scaled(splashWidth, splashHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    splashedSmallpoint = new QLabel(this);
    splashedSmallpoint->setText("");
    splashedSmallpoint->setPixmap(pixSplash);
    splashedSmallpoint->adjustSize();
    splashedSmallpoint->setGeometry(midPlace - splashWidth / 2, h, splashedSmallpoint->width(), splashedSmallpoint->height());

    aniSplash = new QPropertyAnimation;
    aniSplash->setPropertyName("pos");
    aniSplash->setTargetObject(splashedSmallpoint);
    aniSplash->setEasingCurve(QEasingCurve::InOutQuad);
    aniSplash->setStartValue(splashedSmallpoint->pos());
    aniSplash->setEndValue(splashedSmallpoint->pos() + QPoint(0, 100));
    aniSplash->setDuration(10000);
    aniSplash->start();

    percent = new QLabel(this);
    percent->setText(QString("%1%").arg(p));
    QFont font = percent->font();
    font.setPointSize(100);
    font.setItalic(false);
    font.setBold(true);
    percent->setFont(font);
    QPalette pal = percent->palette();
    pal.setColor(QPalette::WindowText, Qt::green);
    percent->setPalette(pal);
    percent->adjustSize();
    percent->setGeometry(600 - percent->width() / 2, 75, percent->width(), percent->height());

    retry = new clickableLabel(this);
    QPixmap pixRetry = QPixmap(":/images/images/reTry.png").scaled(retrySize, retrySize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    retry->setText("");
    retry->setPixmap(pixRetry);
    retry->adjustSize();
    retry->setGeometry(600 - 30 - retrySize, 300, retry->width(), retry->height());
    connect(retry, SIGNAL(clicked()), this, SLOT(emit_retry()));

    menu = new clickableLabel(this);
    QPixmap pixMenu = QPixmap(":/images/images/menu.png").scaled(menuSize, menuSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    menu->setText("");
    menu->setPixmap(pixMenu);
    menu->adjustSize();
    menu->setGeometry(600 + 30, 300, menu->width(), menu->height());
    connect(menu, SIGNAL(clicked()), this, SLOT(emit_menu()));
}

FailWidget::~FailWidget()
{
    delete ui;
}

void FailWidget::emit_retry()
{
    emit reTry(LEVEL);
}

void FailWidget::emit_menu()
{
    emit meNu();
}
