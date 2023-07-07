#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include "clickablelabel.h"


namespace Ui {
class GUI;
}

class GUI : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent* event);
    bool eventFilter(QObject * watched, QEvent *e);

public:
    explicit GUI(QWidget *parent = nullptr);
    ~GUI();

private:
    Ui::GUI *ui;
    int currentLevel;
    QPropertyAnimation *animation;

    clickableLabel * levels[9];
    QLabel * levelNames[9];
    QLabel * smallPoint;

private slots:
    void close_mainwidget();
    void do_changePlace(int levelNum);
    void emit_turnToSet();
    void emit_newGame();


signals:
    void myClose();
    void turnToSet();
    void newGame(int gameLevel);
};

#endif // GUI_H
