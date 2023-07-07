#include "succeedwidget.h"
#include "ui_succeedwidget.h"

#include <QtMultimedia>
#include <ctime>

const int midPlace = 256;
const int smallpointSize = 70;
const int bottom = 100;
const int retrySize = 70;
const int menuSize = 70;
const int beatduration = 2784 / 8;

void SucceedWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    int w = this->width();
    int h = this->height();

    QRect rect = QRect(0, 0, w, h);
    QImage image = QImage(":/background/images/background.bmp");
    painter.drawImage(rect, image);
}

SucceedWidget::SucceedWidget(int levelNum, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SucceedWidget)
{
    ui->setupUi(this);
    if (clickableLabel::soundS){
        QMediaPlayer * player = new QMediaPlayer(this);
        QAudioOutput * audioOutput = new QAudioOutput(this);
        QUrl * source = new QUrl("qrc:/sound/Sound/end/Success.mp3");
        player->setAudioOutput(audioOutput);
        player->setSource(*source);
        player->play();
    }

    LEVEL = levelNum;

    smallpoint = new QLabel(this);
    QPixmap pixSmallPoint = QPixmap(":/images/images/smallpoint.png").scaled(smallpointSize, smallpointSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    smallpoint->setPixmap(pixSmallPoint);
    smallpoint->setText("");
    smallpoint->adjustSize();
    smallpoint->setGeometry(midPlace - smallpointSize / 2, this->height() - bottom - smallpoint->height(), smallpoint->width(), smallpoint->height());
    timer = new QTimer(this);
    timer->stop();
    timer->setTimerType(Qt::PreciseTimer);
    timer->setSingleShot(false);
    timer->setInterval(beatduration / 2);
    connect(timer, SIGNAL(timeout()), this, SLOT(changePhase()));
    timer->start();

    successLabel = new QLabel(this);
    successLabel->setText("SUCCEED!");
    QFont font = successLabel->font();
    font.setPointSize(40);
    font.setItalic(true);
    font.setBold(true);
    successLabel->setFont(font);
    QPalette pal = successLabel->palette();
    pal.setColor(QPalette::WindowText, Qt::green);
    successLabel->setPalette(pal);
    successLabel->adjustSize();
    successLabel->setGeometry(600 - successLabel->width() / 2, 75, successLabel->width(), successLabel->height());

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

    aniSmallpoint = nullptr;
}

SucceedWidget::~SucceedWidget()
{
    delete ui;    
}

void SucceedWidget::changePhase()
{
    phase = !phase;

    static int maxTimes = 10;
    if (clickableLabel::soundS){
        if (phase == 1 && maxTimes > 0){
            maxTimes--;
            std::srand((unsigned)time(NULL));
            int times = std::rand() % 3;
            switch(times){
            case 1:{
                QMediaPlayer * soundEffect = new QMediaPlayer;
                QAudioOutput * audioOutput = new QAudioOutput(this);
                soundEffect->setAudioOutput(audioOutput);
                QUrl * source = new QUrl("qrc:/fireworks/Sound/fireworks/1.mp3");
                soundEffect->setSource(*source);
                soundEffect->play();
                break;
            }

            case 2:{
                QMediaPlayer * soundEffect1 = new QMediaPlayer;
                QAudioOutput * audioOutput = new QAudioOutput(this);
                soundEffect1->setAudioOutput(audioOutput);
                QUrl * source = new QUrl("qrc:/fireworks/Sound/fireworks/1.mp3");
                soundEffect1->setSource(*source);
                soundEffect1->play();

                QMediaPlayer * soundEffect2 = new QMediaPlayer;
                soundEffect2->setAudioOutput(audioOutput);
                QUrl * source2 = new QUrl("qrc:/fireworks/Sound/fireworks/2.mp3");
                soundEffect2->setSource(*source2);
                soundEffect2->play();
                break;
            }

            default:
                break;
            }
        }
    }

    if (phase == 0)
        smallpoint->setGeometry(midPlace - smallpointSize / 2, this->height() - bottom - smallpoint->height(), smallpoint->width(), smallpoint->height());

    if (aniSmallpoint)
        delete aniSmallpoint;
    aniSmallpoint = new QPropertyAnimation;
    aniSmallpoint->setPropertyName("pos");
    aniSmallpoint->setTargetObject(smallpoint);
    aniSmallpoint->setDuration(beatduration / 2);

    if (phase == 0)
        aniSmallpoint->setEasingCurve(QEasingCurve::OutQuad);
    else
        aniSmallpoint->setEasingCurve(QEasingCurve::InQuad);

    QPoint point(0, smallpointSize);

    aniSmallpoint->setStartValue(smallpoint->pos());
    if (phase == 0)
        aniSmallpoint->setEndValue(smallpoint->pos() - point);
    else
        aniSmallpoint->setEndValue(smallpoint->pos() + point);

    aniSmallpoint->start();
}

void SucceedWidget::emit_retry()
{
    emit reTry(LEVEL);
}

void SucceedWidget::emit_menu()
{
    emit meNu();
}
