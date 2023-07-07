#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include "clickablelabel.h"

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *event);

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();
    bool getMusicState();
    bool getSoundState();

private:
    Ui::Settings *ui;

    clickableLabel * menu;
    QLabel * proBy;
    clickableLabel * music;
    clickableLabel * sound;
    QLabel * musicName;
    QLabel * soundName;

    bool musicState = 1;
    bool soundState = 1;

private slots:
    void emit_turnToGUI();
    void turn_musicState();
    void turn_soundState();

signals:
    void turnToGUI();
    void changeMusicSoundState(bool musicS, bool soundS);
};

#endif // SETTINGS_H
