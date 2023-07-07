#include "game.h"
#include "ui_game.h"

#include <QPainter>
#include <sstream>
#include <cstring>
#include <QLabel>
#include <QTimer>
#include <cmath>
#include <ctime>
#include <QtMultiMedia>

void Game::paintEvent(QPaintEvent *event)
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

void Game::mousePressEvent(QMouseEvent * event)
{
    if (phase == 1)
        jump = 1;
    event->accept();
}

Game::Game(int levelNum, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);

    pixPass0 = QPixmap(":/images/images/pass0.png").scaled(stockWidth, basicHeight + 0 * (stockHeight), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    pixPass1 = QPixmap(":/images/images/pass1.png").scaled(stockWidth, basicHeight + 1 * (stockHeight), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    pixPass2 = QPixmap(":/images/images/pass2.png").scaled(stockWidth, basicHeight + 2 * (stockHeight), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    pixPass3 = QPixmap(":/images/images/pass3.png").scaled(stockWidth, basicHeight + 3 * (stockHeight), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    if (levelNum < 1)   levelNum = 1;
    if (levelNum > 9)   levelNum = 9;

    LEVEL = levelNum;

    getMap(levelNum);

    int revSpurCnt = 0;

    QPixmap pixPlat0 = QPixmap(":/images/images/plat0.png").scaled(stockWidth, basicHeight + 0 * (stockHeight), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap pixPlat1 = QPixmap(":/images/images/plat1.png").scaled(stockWidth, basicHeight + 1 * (stockHeight), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap pixPlat2 = QPixmap(":/images/images/plat2.png").scaled(stockWidth, basicHeight + 2 * (stockHeight), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap pixPlat3 = QPixmap(":/images/images/plat3.png").scaled(stockWidth, basicHeight + 3 * (stockHeight), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPixmap pixSpur0 = QPixmap(":/images/images/spur0.png").scaled(stockWidth, spurHeight + 0 * (stockHeight), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap pixSpur1 = QPixmap(":/images/images/spur1.png").scaled(stockWidth, spurHeight + 1 * (stockHeight), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap pixSpur2 = QPixmap(":/images/images/spur2.png").scaled(stockWidth, spurHeight + 2 * (stockHeight), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap pixSpur3 = QPixmap(":/images/images/spur3.png").scaled(stockWidth, spurHeight + 3 * (stockHeight), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPixmap pixRevSpur = QPixmap(":/images/images/spur-1.png").scaled(stockWidth, spurHeight + 0 * (stockHeight), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);


    int h = this->height();
    for (int i = 0; i < gameLength; i++){
        picStocks[i] = new QLabel(this);

        picStocks[i]->setText("");

        if (Stocks[i].type == 0 || Stocks[i].type == 2)
            switch (Stocks[i].height){
            case 0:
                picStocks[i]->setPixmap(pixPlat0);
                break;
            case 1:
                picStocks[i]->setPixmap(pixPlat1);
                break;
            case 2:
                picStocks[i]->setPixmap(pixPlat2);
                break;
            case 3:
                picStocks[i]->setPixmap(pixPlat3);
                break;
            default:
                picStocks[i]->setPixmap(pixPlat0);
                break;
            }

        if (Stocks[i].type == 1)
            switch(Stocks[i].height){
            case 0:
                picStocks[i]->setPixmap(pixSpur0);
                break;
            case 1:
                picStocks[i]->setPixmap(pixSpur1);
                break;
            case 2:
                picStocks[i]->setPixmap(pixSpur2);
                break;
            case 3:
                picStocks[i]->setPixmap(pixSpur3);
                break;
            default:
                picStocks[i]->setPixmap(pixSpur0);
                break;
            }
        picStocks[i]->adjustSize();
        picStocks[i]->setGeometry(midPlace - stockWidth / 2 + i * (stockWidth + interval), h - bottom - picStocks[i]->height(), picStocks[i]->width(), picStocks[i]->height());

        if (Stocks[i].type == 2)
        {
            revSpursPlace[revSpurCnt] = i;
            revSpurs[revSpurCnt] = new QLabel(this);
            revSpurs[revSpurCnt]->setPixmap(pixRevSpur);
            revSpurs[revSpurCnt]->adjustSize();
            revSpurs[revSpurCnt]->setGeometry(midPlace - stockWidth / 2 + i * (stockWidth + interval), picStocks[i - 1]->pos().y() - 2 * stockHeight, revSpurs[revSpurCnt]->width(), revSpurs[revSpurCnt]->height());
            revSpurCnt++;
        }
    }


    QPixmap pixSmallPoint = QPixmap(":/images/images/smallpoint.png").scaled(smallPointSize, smallPointSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    smallPoint = new QLabel(this);
    smallPoint->setText("");
    smallPoint->setPixmap(pixSmallPoint);
    smallPoint->adjustSize();
    smallPoint->setGeometry(midPlace - smallPointSize / 2, picStocks[0]->pos().y() + basicHeight / 2 - smallPointSize - 5, smallPointSize, smallPointSize);

    start = new clickableLabel(this);
    start->setText("");
    QPixmap pixStart = QPixmap(":/images/images/start.png").scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    start->setPixmap(pixStart);
    start->adjustSize();
    start->setGeometry(40, 40, start->width(), start->height());
    connect(start, SIGNAL(clicked()), this, SLOT(startTheGame()));

    percent = new QLabel(this);
    QFont font = percent->font();
    font.setPointSize(40);
    font.setBold(true);
    percent->setFont(font);
    QPalette pal = percent->palette();
    pal.setColor(QPalette::WindowText, Qt::yellow);
    percent->setPalette(pal);
    percent->setText("0%");
    percent->adjustSize();
    percent->setGeometry(-1000, -1000, percent->width(), percent->height());  

    iniTimer();
}

Game::~Game()
{
    delete ui;
}

void Game::iniTimer()
{
    musicTimer = new QTimer(this);
    musicTimer->stop();
    musicTimer->setTimerType(Qt::PreciseTimer);
    musicTimer->setSingleShot(false);
    musicTimer->setInterval(duration);
    connect(musicTimer, SIGNAL(timeout()), this, SLOT(changeMusic()));

    gameTimer = new QTimer(this);
    gameTimer->stop();
    gameTimer->setTimerType(Qt::PreciseTimer);
    gameTimer->setInterval(beatDuration / 2);
    gameTimer->setSingleShot(false);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(changePhase()));
}

void Game::stopTimerandMedia()
{
    musicTimer->stop();
    gameTimer->stop();
    delete gameTimer;
    delete musicTimer;

    if (musicPlayer != nullptr){
        musicPlayer->stop();
        delete musicPlayer;
    }
}

void Game::playJumpupSound()
{
    if (clickableLabel::soundS){
        //qrc:/jumpUpSound/Sound/jumpUp/jumpUp01.mp3
        std::srand((unsigned)time(NULL));
        int soundNo = rand() % 12 + 1;
        char c1 = char(soundNo / 10 + '0');
        char c2 = char(soundNo % 10 + '0');
        std::string s = "qrc:/jumpUpSound/Sound/jumpUp/jumpUp";
        s += c1;
        s += c2;
        s += ".mp3";

        QMediaPlayer * soundEffect = new QMediaPlayer;
        QAudioOutput * audioOutput = new QAudioOutput(this);
        soundEffect->setAudioOutput(audioOutput);
        QUrl * source = new QUrl(s.c_str());
        soundEffect->setSource(*source);
        soundEffect->play();
    }
}

void Game::playJumpoverSound()
{
    if (clickableLabel::soundS){
        //qrc:/jumpOverSound/Sound/jumpOver/jumpOver01.mp3
        std::srand((unsigned)time(NULL));
        int soundNo = rand() % 12 + 1;
        char c1 = char(soundNo / 10 + '0');
        char c2 = char(soundNo % 10 + '0');
        std::string s = "qrc:/jumpOverSound/Sound/jumpOver/jumpOver";
        s += c1;
        s += c2;
        s += ".mp3";

        QMediaPlayer * soundEffect = new QMediaPlayer;
        QAudioOutput * audioOutput = new QAudioOutput(this);
        soundEffect->setAudioOutput(audioOutput);
        QUrl * source = new QUrl(s.c_str());
        soundEffect->setSource(*source);
        soundEffect->play();
    }
}

void Game::startTheGame()
{
    delete start;
    start = nullptr;

    percent->setGeometry(20, 10, percent->width(), percent->height());
    phase = 0;
    jump = 0;

    musicTimer->start();
    gameTimer->start();
    musicPlayer = nullptr;

    if (clickableLabel::musicS){
        musicPlayer = new QMediaPlayer(this);
        QAudioOutput * qas = new QAudioOutput(this);
        musicPlayer->setAudioOutput(qas);
        QUrl * source = new QUrl("qrc:/music/Music/gameMusic01/gameMusic01-01.ogg");
        musicPlayer->setSource(*source);
        musicPlayer->play();
    }

    QPoint forsmallPoint(0, -30);
    QPoint forStocks(-(interval + stockWidth) / 2, 0);

    currentStock = 0;
    currentRevSpur = -1;
    switch (Stocks[currentStock].height){
    case 1:
        picStocks[currentStock]->setPixmap(pixPass1);
        break;
    case 2:
        picStocks[currentStock]->setPixmap(pixPass2);
        break;
    case 3:
        picStocks[currentStock]->setPixmap(pixPass3);
        break;
    default:
        picStocks[currentStock]->setPixmap(pixPass0);
        break;
    }

    aniSmallPoint = new QPropertyAnimation;
    aniSmallPoint->setTargetObject(smallPoint);
    aniSmallPoint->setEasingCurve(QEasingCurve::OutQuad);
    aniSmallPoint->setPropertyName("pos");
    aniSmallPoint->setDuration(beatDuration / 2);
    aniSmallPoint->setStartValue(smallPoint->pos());
    aniSmallPoint->setEndValue(smallPoint->pos() + forsmallPoint);
    aniSmallPoint->start();

    for (int i = 0; i < std::min(gameLength, 10); i++){

        aniStocks[i] = new QPropertyAnimation;
        aniStocks[i]->setTargetObject(picStocks[i]);
        aniStocks[i]->setEasingCurve(QEasingCurve::Linear);
        aniStocks[i]->setPropertyName("pos");
        aniStocks[i]->setDuration(beatDuration / 2);
        aniStocks[i]->setStartValue(picStocks[i]->pos());
        aniStocks[i]->setEndValue(picStocks[i]->pos() + forStocks);
        aniStocks[i]->start();
    }

    for (int i = 0; i < std::min(revSpurNum, 10); i++){
        aniRevSpur[i] = new QPropertyAnimation;
        aniRevSpur[i]->setTargetObject(revSpurs[i]);
        aniRevSpur[i]->setEasingCurve(QEasingCurve::Linear);
        aniRevSpur[i]->setPropertyName("pos");
        aniRevSpur[i]->setDuration(beatDuration / 2);
        aniRevSpur[i]->setStartValue(revSpurs[i]->pos());
        aniRevSpur[i]->setEndValue(revSpurs[i]->pos() + forStocks);
        aniRevSpur[i]->start();
    }

}

void Game::changeMusic()
{
    //qrc:/music/Music/gameMusic01/gameMusic01-02.mp3
    if (clickableLabel::musicS){
        currentMusic++;
        char c1 = char(currentMusic / 10 + '0');
        char c2 = char(currentMusic % 10 + '0');
        musicPlayer->stop();
        std::string s = "qrc:/music/Music/gameMusic01/gameMusic01-";
        s += c1;
        s += c2;
        s += ".mp3";
        if (currentMusic == 40)
            currentMusic = 4;

        delete musicPlayer;
        musicPlayer = new QMediaPlayer;
        QAudioOutput * qas = new QAudioOutput(this);
        musicPlayer->setAudioOutput(qas);
        QUrl * source = new QUrl(s.c_str());
        musicPlayer->setSource(*source);
        musicPlayer->play();
    }
}

void Game::getMap(int levelNum)
{
    if (levelNum > 9) levelNum = 9;
    if (levelNum < 1) levelNum = 1;
//:/levels/levels/4.level
    QString qs = QString(":/levels/levels/%1.level").arg(levelNum);
    QFile qf(qs);
    qf.open(QIODevice::ReadOnly);

    gameLength = 0;
    revSpurNum = 0;
    std::stringstream ss;


    while (true){
        ss << qf.readLine(20).data();
        ss >> Stocks[gameLength].type >> Stocks[gameLength].height;
        if (Stocks[gameLength].type == 2)
            revSpurNum++;

        if (Stocks[gameLength].type == -1)
            break;

        gameLength++;
    }
    qf.close();
}

void Game::changePhase()
{
    delete aniSmallPoint;
    for (int i = std::max(0, currentStock - 5); i < std::min(gameLength, currentStock + 10); i++)
        delete aniStocks[i];

    for (int i = std::max(0, currentRevSpur - 5); i < std::min(revSpurNum, currentRevSpur + 10); i++)
        delete aniRevSpur[i];

    phase = !phase;
    if (failed == 1){
        stopTimerandMedia();
        emit fail(smallPoint->pos().y(), floor((double(currentStock) / (gameLength - 1)) * 100), LEVEL);
        return;
    }

    QPoint forsmallPoint;
    QPoint forStocks;

    if (phase == 0){

        currentStock = nextStock;
        if (Stocks[currentStock].type == 2)
            currentRevSpur++;
        smallPoint->setGeometry(midPlace - smallPointSize / 2, picStocks[currentStock]->pos().y() + basicHeight / 2 - smallPointSize - 5, smallPointSize, smallPointSize);

        for (int i = std::max(0, currentStock - 5); i < std::min(gameLength, currentStock + 10); i++)
            picStocks[i]->setGeometry(midPlace - stockWidth / 2 + (i - currentStock) * (stockWidth + interval), picStocks[i]->pos().y(), picStocks[i]->width(), picStocks[i]->height());

        for (int i = std::max(0, currentRevSpur - 5); i < std::min(revSpurNum, currentRevSpur + 10); i++)
            revSpurs[i]->setGeometry(midPlace - stockWidth / 2 + (revSpursPlace[i] - currentStock) * (stockWidth + interval), revSpurs[i]->pos().y(), revSpurs[i]->width(), revSpurs[i]->height());

        switch (Stocks[currentStock].height){
        case 1:
            picStocks[currentStock]->setPixmap(pixPass1);
            break;
        case 2:
            picStocks[currentStock]->setPixmap(pixPass2);
            break;
        case 3:
            picStocks[currentStock]->setPixmap(pixPass3);
            break;
        default:
            picStocks[currentStock]->setPixmap(pixPass0);
            break;
        }
        percent->setText(QString("%1%").arg(floor((double(currentStock) / (gameLength - 1)) * 100)));
        percent->adjustSize();
        percent->setGeometry(20, 10, percent->width(), percent->height());

        if (currentStock == gameLength - 1)
        {
            stopTimerandMedia();
            emit success(LEVEL);
            return;
        }

        if (jump == 0){
            nextStock = currentStock + 1;
            nextHeight = Stocks[nextStock].height;
            if (Stocks[nextStock].height <= Stocks[currentStock].height)
                nextHeight = Stocks[nextStock].height;
            else
                failed = 1;

            jumpHeight = leapHeight;
            speedTimes = 1;
        }
        else{
            if (currentStock == gameLength - 2)
            {
                nextStock = currentStock + 1;
                nextHeight = Stocks[nextStock].height;
                jumpHeight = leapHeight;//the last two must be (0 0) and (0 0)
                speedTimes = 1;
            }

            else{
                if (Stocks[currentStock].height < Stocks[currentStock + 1].height){
                    nextStock = currentStock + 1;
                    jumpHeight = leapHeight + stockHeight;
                    nextHeight = Stocks[nextStock].height;
                    speedTimes = 1;
                    playJumpupSound();
                }

                else{
                    nextStock = currentStock + 2;
                    jumpHeight = leapHeight;
                    nextHeight = Stocks[nextStock].height;
                    if (nextHeight > Stocks[currentStock].height)
                        failed = 1;
                    speedTimes = 2;
                    if (Stocks[currentStock + 1].type == 2){
                        failed = 1;
                        jumpHeight = stockHeight;
                    }
                    playJumpoverSound();
                }
            }
        }
        jump = 0;
        forsmallPoint = QPoint(0, -jumpHeight);
        forStocks = QPoint(-(stockWidth + interval) * speedTimes / 2, 0);
    }
    else{
        if (Stocks[nextStock].type == 1){
            failed = 1;
        }
        forsmallPoint = QPoint(0, picStocks[nextStock]->pos().y() + 15 - smallPointSize - smallPoint->pos().y());
        forStocks = QPoint(-(stockWidth + interval) * speedTimes / 2, 0);
    }


    aniSmallPoint = new QPropertyAnimation;
    aniSmallPoint->setTargetObject(smallPoint);
    aniSmallPoint->setPropertyName("pos");
    if (phase == 0)
        aniSmallPoint->setEasingCurve(QEasingCurve::OutQuad);
    else
        aniSmallPoint->setEasingCurve(QEasingCurve::InQuad);
    aniSmallPoint->setDuration(beatDuration / 2);
    aniSmallPoint->setStartValue(smallPoint->pos());
    aniSmallPoint->setEndValue(smallPoint->pos() + forsmallPoint);
    aniSmallPoint->start();

    for (int i = std::max(0, currentStock - 5); i < std::min(gameLength, currentStock + 10); i++){
        aniStocks[i] = new QPropertyAnimation;
        aniStocks[i]->setTargetObject(picStocks[i]);
        aniStocks[i]->setPropertyName("pos");
        aniStocks[i]->setEasingCurve(QEasingCurve::Linear);
        aniStocks[i]->setDuration(beatDuration / 2);
        aniStocks[i]->setStartValue(picStocks[i]->pos());
        aniStocks[i]->setEndValue(picStocks[i]->pos() + forStocks);
        aniStocks[i]->start();
    }

    for (int i = std::max(0, currentRevSpur - 5); i < std::min(revSpurNum, currentRevSpur + 10); i++){

        aniRevSpur[i] = new QPropertyAnimation;
        aniRevSpur[i]->setTargetObject(revSpurs[i]);
        aniRevSpur[i]->setPropertyName("pos");
        aniRevSpur[i]->setEasingCurve(QEasingCurve::Linear);
        aniRevSpur[i]->setDuration(beatDuration / 2);
        aniRevSpur[i]->setStartValue(revSpurs[i]->pos());
        aniRevSpur[i]->setEndValue(revSpurs[i]->pos() + forStocks);
        aniRevSpur[i]->start();
    }

}
