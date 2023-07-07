#ifndef SUCCEEDWIDGET_H
#define SUCCEEDWIDGET_H

#include <QWidget>
#include <QLabel>
#include "clickablelabel.h"
#include <QTimer>
#include <QPropertyAnimation>

namespace Ui {
class SucceedWidget;
}

class SucceedWidget : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent * event);

public:
    explicit SucceedWidget(int levelNum, QWidget *parent = nullptr);
    ~SucceedWidget();

private:
    Ui::SucceedWidget *ui;
    int LEVEL;
    QLabel * smallpoint;
    QTimer * timer;
    QLabel * successLabel;
    clickableLabel * retry;
    clickableLabel * menu;
    QPropertyAnimation * aniSmallpoint;
    bool phase = 1;

private slots:
    void changePhase();


signals:
    void reTry(int levelNum);
    void meNu();

private slots:
    void emit_retry();
    void emit_menu();
};

#endif // SUCCEEDWIDGET_H
