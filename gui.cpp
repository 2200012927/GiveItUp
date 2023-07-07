#include "gui.h"
#include "ui_gui.h"

#include <QPainter>
#include <QRect>
#include <QImage>
#include <QLabel>
#include <QPropertyAnimation>

const int setSize = 75;
const int setStart = 100;
const int setClose = 50;
const int levelWidth = 50;
const int levelHeight = 32;
const int interval = 10;
const int left = (800 - 9 * levelWidth - 8 * interval) / 2;
const int right = left;
const int sizePoint = 40;

void GUI::paintEvent(QPaintEvent *event)
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

bool GUI::eventFilter(QObject *watched, QEvent *e)
{
    int levelNum = 0;
    if (e->type() == QEvent::MouseButtonPress){
        for (int i = 0; i < 9; i++)
            if (watched == levels[i]){
                levelNum = i + 1;
                break;
            }

        if (levelNum){
            do_changePlace(levelNum);
            currentLevel = levelNum;
        }
    }
    return QWidget::eventFilter(watched, e);

}

GUI::GUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GUI)
{
    ui->setupUi(this);

    int w = this->width();
    int h = this->height();

    //label - logo
    ui->logo->setGeometry(w / 4, h / 8, w / 2, h / 8);
    ui->logo->setFixedSize(w / 2, h / 3);
    QPixmap *pixma = new QPixmap(":/banner/images/logo.png");
    QPixmap pixmap = pixma->scaled(w / 2, h / 5, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->logo->setText("");
    ui->logo->setPixmap(pixmap);
    animation = new QPropertyAnimation;
    animation->setTargetObject(ui->logo);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setPropertyName("pos");
    animation->setDuration(4000);
    animation->setStartValue(QPoint(w / 4, - h / 3));
    animation->setEndValue(QPoint(w / 4, h / 16 - 30));
    animation->start();

    //label - settings

    QPixmap *pixSettings = new QPixmap(":/images/images/setting.png");
    QPixmap pixSetting =
        pixSettings->scaled(setSize, setSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->settings->setText("");
    ui->settings->setPixmap(pixSetting);
    ui->settings->setGeometry(w / 4 - 75, h / 3, setSize, setSize);
    ui->settings->setFixedSize(setSize, setSize);
    connect(ui->settings, SIGNAL(clicked()), this, SLOT(emit_turnToSet()));

    //label - start

    QPixmap *pixStart = new QPixmap(":/images/images/start.png");
    QPixmap pixStar = pixStart->scaled(setStart, setStart, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->start->setText("");
    ui->start->setPixmap(pixStar);
    ui->start->setGeometry(w / 2 - 50, h / 3, setStart, setStart);
    ui->start->setFixedSize(setStart, setStart);
    connect(ui->start, SIGNAL(clicked()), this, SLOT(emit_newGame()));

    //label - closeLabel

    QPixmap *pixClose = new QPixmap(":/images/images/close.png");
    QPixmap pixClos = pixClose->scaled(setClose, setClose, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->closeLabel->setText("");
    ui->closeLabel->setPixmap(pixClos);
    ui->closeLabel->setGeometry(w / 4 * 3, h / 3, setClose, setClose);
    ui->closeLabel->setFixedSize(setClose, setClose);


    QPixmap *pixLevel = new QPixmap(":/images/images/plat0.png");
    QPixmap pixlevel = pixLevel->scaled(levelWidth, levelHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);


    for (int i = 0; i <= 8; i++){
        levels[i] = new clickableLabel(this);
        levels[i]->setText("");
        levels[i]->setPixmap(pixlevel);
        levels[i]->setGeometry(left + i * (levelWidth + interval), h / 4 * 3, levelWidth, levelHeight);
    }

    for (int i = 0; i < 9; i++){
        levelNames[i] = new QLabel(this);
        levelNames[i]->setText(QString("%1").arg(i + 1));
        levelNames[i]->adjustSize();
        levelNames[i]->setGeometry(left + levelWidth / 2 + i * (levelWidth + interval) - interval / 2, h / 4 * 3 + levelHeight + interval  / 2, levelNames[i]->size().width(), levelNames[i]->size().height());

    }

    smallPoint = new QLabel(this);
    QPixmap * pixPoint = new QPixmap(":/images/images/smallpoint.png");
    QPixmap pixpoint = pixPoint->scaled(sizePoint, sizePoint, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    smallPoint->setText("");
    smallPoint->setPixmap(pixpoint);
    currentLevel = 1;
    do_changePlace(currentLevel);
    //smallPoint->setGeometry(left + (levelWidth - sizePoint) / 2, h / 4 * 3 + levelHeight / 3 - sizePoint, sizePoint, sizePoint);

    connect(ui->closeLabel, SIGNAL(clicked()), this, SLOT(close_mainwidget()));

    for (int i = 0; i < 9; i++)
        levels[i]->installEventFilter(this);

}

GUI::~GUI()
{
    delete ui;
}

void GUI::close_mainwidget()
{
    emit myClose();
}

void GUI::do_changePlace(int levelNum)
{
    int h = this->height();
    smallPoint->setGeometry(left + (levelWidth - sizePoint) / 2 + (levelWidth + interval) * (levelNum - 1), h / 4 * 3 + levelHeight / 3 - sizePoint, sizePoint, sizePoint);
}

void GUI::emit_turnToSet()
{
    emit turnToSet();
}

void GUI::emit_newGame()
{
    emit newGame(currentLevel);
}
