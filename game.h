#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "macro.h"
#include <QLabel>
#include "clickablelabel.h"
#include <QPropertyAnimation>
#include <QTimer>
#include <QtMultiMedia>

const int stockWidth = 56;
const int interval = 8;
const int stockHeight = 50;
const int basicHeight = 32;
const int midPlace = 256;
const int bottom = 100;
const int smallPointSize = 42;
const int leapHeight = 30;
const int spurHeight = 40;
const int duration = 2784;
const int beatDuration = duration / 8;


const int maxSize = 1010;

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent * event);

public:
    explicit Game(int levelNum, QWidget *parent = nullptr);
    ~Game();

private:
    Ui::Game *ui;
    int LEVEL;
    stock Stocks[maxSize];
    QLabel * picStocks[maxSize];
    QLabel * revSpurs[maxSize];
    int revSpursPlace[maxSize];
    int gameLength = 0;
    int revSpurNum = 0;
    QLabel * smallPoint;
    void iniTimer();

private:
    clickableLabel * start;
    int currentStock = 0;
    int currentRevSpur = 0;
    int nextStock = 1;
    int nextHeight = 0;
    int jumpHeight = 0;
    int speedTimes = 1;
    QLabel * percent;
    QPropertyAnimation *aniSmallPoint;
    QPropertyAnimation * aniStocks[maxSize];
    QPropertyAnimation * aniRevSpur[maxSize];
    QTimer * gameTimer;
    QTimer * musicTimer;
    QMediaPlayer * musicPlayer;
    int currentMusic = 1;
    bool phase = 0;
    bool jump = 0;
    bool failed = 0;
    void stopTimerandMedia();
    void playJumpupSound();
    void playJumpoverSound();
    QPixmap pixPass0;
    QPixmap pixPass1;
    QPixmap pixPass2;
    QPixmap pixPass3;



private slots:
    void startTheGame();
    void changeMusic();
    void getMap(int levelNum);
    void changePhase();

signals:
    void fail(int height, int perc, int levelNum);
    void success(int levelNum);
};

#endif // GAME_H
