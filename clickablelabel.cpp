#include "clickablelabel.h"
#include <QtMultimedia>

clickableLabel::clickableLabel(QWidget *parent): QLabel(parent)
{

}

bool clickableLabel::soundS = 1;
bool clickableLabel::musicS = 1;

void clickableLabel::mousePressEvent(QMouseEvent *me)
{
    Q_UNUSED(me);

    if (soundS){
        QMediaPlayer * playerBtn = new QMediaPlayer(this);
        QAudioOutput * audioOutput = new QAudioOutput(this);
        playerBtn->setAudioOutput(audioOutput);
        QUrl * source = new QUrl("qrc:/sound/Sound/GUI/Button.mp3");
        playerBtn->setSource(*source);
        playerBtn->play();
    }

    emit clicked();
}
