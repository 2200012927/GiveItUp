#include "widget.h"
#include "ui_widget.h"
#include "macro.h"

#include <QTimer>
#include "banner.h"
#include "producedBy.h"
#include "gui.h"
#include "settings.h"
#include "game.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(WID, HEI);

    ui->stackedWidget->setFixedSize(WID, HEI);

    ban = new banner;
    ui->stackedWidget->addWidget(ban);//2
    ui->stackedWidget->setCurrentIndex(2);


    pro = new producedBy;
    ui->stackedWidget->addWidget(pro);//3

    gui = new GUI;
    ui->stackedWidget->addWidget(gui);//4
    connect(gui, SIGNAL(myClose()), this, SLOT(close()));
    connect(gui, SIGNAL(turnToSet()), this, SLOT(turnToSet()));

    settings = new Settings;
    ui->stackedWidget->addWidget(settings);//5
    connect(settings, SIGNAL(turnToGUI()), this, SLOT(turnToGUI()));
    connect(settings, SIGNAL(changeMusicSoundState(bool,bool)), this, SLOT(setMSState(bool,bool)));

    connect(gui, SIGNAL(newGame(int)), this, SLOT(newGame(int)));
    game = nullptr;
    fail = nullptr;
    success = nullptr;



    QTimer::singleShot(1500, Qt::PreciseTimer, this, &Widget::fromBannerToProduced);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::fromBannerToProduced()
{
    ui->stackedWidget->setCurrentIndex(3);
    QTimer::singleShot(1500, Qt::PreciseTimer, this, &Widget::fromProducedByToGUI);
    return;
}

void Widget::fromProducedByToGUI()
{
    ui->stackedWidget->setCurrentIndex(4);
    return;
}

void Widget::turnToGUI()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void Widget::turnToSet()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void Widget::newGame(int gameLevel)
{
    if (game)
        delete game;
    game = new Game(gameLevel, this);
    connect(game, SIGNAL(fail(int,int,int)), this, SLOT(turnToFailWidget(int,int,int)));
    connect(game, SIGNAL(success(int)), this, SLOT(turnToSuccessWidget(int)));
    ui->stackedWidget->addWidget(game);
    ui->stackedWidget->setCurrentWidget(game);
}

void Widget::turnToSuccessWidget(int levelNum)
{
    if(success)
        delete success;
    success = new SucceedWidget(levelNum, this);
    connect(success, SIGNAL(reTry(int)), this, SLOT(newGame(int)));
    connect(success, SIGNAL(meNu()), this, SLOT(turnToGUI()));
    ui->stackedWidget->addWidget(success);//7
    ui->stackedWidget->setCurrentWidget(success);
}

void Widget::turnToFailWidget(int h, int w, int levelNum)
{
    if (fail)
        delete fail;
    fail = new FailWidget(h, w, levelNum, this);
    connect(fail, SIGNAL(reTry(int)), this, SLOT(newGame(int)));
    connect(fail, SIGNAL(meNu()), this, SLOT(turnToGUI()));
    ui->stackedWidget->addWidget(fail);//8
    ui->stackedWidget->setCurrentWidget(fail);
}

void Widget::setMSState(bool musicS, bool soundS)
{
    clickableLabel::soundS = soundS;
    clickableLabel::musicS = musicS;
}

