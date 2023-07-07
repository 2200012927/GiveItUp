#ifndef FAILWIDGET_H
#define FAILWIDGET_H

#include <QWidget>
#include <QLabel>
#include "clickablelabel.h"
#include <QPropertyAnimation>

namespace Ui {
class FailWidget;
}

class FailWidget : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent * event);

public:
    explicit FailWidget(int h, int p, int levelNum, QWidget *parent = nullptr);
    ~FailWidget();

private:
    Ui::FailWidget *ui;
    QLabel * splashedSmallpoint;
    QLabel * percent;
    clickableLabel * retry;
    clickableLabel * menu;
    QPropertyAnimation * aniSplash;
    int LEVEL;

signals:
    void reTry(int levelNum);
    void meNu();

private slots:
    void emit_retry();
    void emit_menu();
};

#endif // FAILWIDGET_H
