#include "settings.h"
#include "ui_settings.h"

#include <QPainter>
#include <QFont>
#include <QPalette>
#include "clickablelabel.h"

const int menuSize = 75;
const int msWidth = 200;
const int msHeight = 75;

void Settings::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    int w = this->width();
    int h = this->height();

    QRect *rect = new QRect(0, 0, w, h);
    QImage *image = new QImage(":/background/images/background.bmp");
    painter.drawImage(*rect, *image);
}

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    int w = this->width();
    int h = this->height();

    menu = new clickableLabel(this);
    QPixmap * pixmenu = new QPixmap(":/images/images/menu.png");
    QPixmap pixMenu = pixmenu->scaled(menuSize, menuSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    menu->setText("");
    menu->setPixmap(pixMenu);
    menu->setGeometry(20, h - menuSize - 20, menuSize, menuSize);
    connect(menu, SIGNAL(clicked()), this, SLOT(emit_turnToGUI()));

    proBy = new QLabel(this);
    proBy->setText("Produced by:\n\t刘智轩\n\t翟劲博\n\t李睿健\n@程序设计实习(PKU)");
    proBy->setTextFormat(Qt::PlainText);
    QFont font = proBy->font();
    font.setPointSize(30);
    font.setBold(true);
    proBy->setFont(font);
    QPalette palette = proBy->palette();
    palette.setColor(QPalette::WindowText, Qt::red);
    proBy->setPalette(palette);
    proBy->adjustSize();
    proBy->setGeometry(50, 20, proBy->width(), proBy->height());

    QPixmap * pix_on = new QPixmap(":/sound/images/sounds_on.png");
    QPixmap * pix_off = new QPixmap(":/sound/images/sounds_off.png");
    QPixmap pixMS_on = pix_on->scaled(msWidth, msHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap pixMS_off = pix_off->scaled(msWidth, msHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    music = new clickableLabel(this);
    sound = new clickableLabel(this);
    music->setText("");
    music->setPixmap(pixMS_on);
    sound->setText("");
    sound->setPixmap(pixMS_on);
    music->setGeometry(w - msWidth - 20, 20, msWidth, msHeight);
    sound->setGeometry(w - msWidth - 20, 60 + msHeight, msWidth, msHeight);
    connect(music, SIGNAL(clicked()), this, SLOT(turn_musicState()));
    connect(sound, SIGNAL(clicked()), this, SLOT(turn_soundState()));

    musicName = new QLabel(this);
    soundName = new QLabel(this);
    musicName->setText("音乐");
    musicName->adjustSize();
    soundName->setText("音效");
    soundName->adjustSize();
    musicName->setGeometry(w - msWidth - 20, 10, musicName->width(), musicName->height());
    soundName->setGeometry(w - msWidth - 20, 50 + msHeight, soundName->width(), soundName->height());
}

Settings::~Settings()
{
    delete ui;
}

bool Settings::getMusicState()
{
    return musicState;
}

bool Settings::getSoundState()
{
    return soundState;
}

void Settings::emit_turnToGUI()
{
    emit turnToGUI();
}

void Settings::turn_musicState()
{
    QPixmap * pix_on = new QPixmap(":/sound/images/sounds_on.png");
    QPixmap * pix_off = new QPixmap(":/sound/images/sounds_off.png");
    QPixmap pixMS_on = pix_on->scaled(msWidth, msHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap pixMS_off = pix_off->scaled(msWidth, msHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    musicState = !musicState;
    if (musicState)
        music->setPixmap(pixMS_on);
    else
        music->setPixmap(pixMS_off);

    emit changeMusicSoundState(musicState, soundState);
}

void Settings::turn_soundState()
{
    QPixmap * pix_on = new QPixmap(":/sound/images/sounds_on.png");
    QPixmap * pix_off = new QPixmap(":/sound/images/sounds_off.png");
    QPixmap pixMS_on = pix_on->scaled(msWidth, msHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap pixMS_off = pix_off->scaled(msWidth, msHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    soundState = !soundState;
    if (soundState)
        sound->setPixmap(pixMS_on);
    else
        sound->setPixmap(pixMS_off);

    emit changeMusicSoundState(musicState, soundState);
}
