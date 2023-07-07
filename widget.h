#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "banner.h"
#include "producedBy.h"
#include "gui.h"
#include "settings.h"
#include "game.h"
#include "succeedwidget.h"
#include "failwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

private slots:
    void fromBannerToProduced();
    void fromProducedByToGUI();
    void turnToGUI();
    void turnToSet();
    void newGame(int gameLevel);
    void turnToSuccessWidget(int levelNum);
    void turnToFailWidget(int h, int w, int levelNum);
    void setMSState(bool musicS, bool soundS);

private:
    banner * ban;
    producedBy * pro;
    GUI * gui;
    Settings * settings;
    Game * game;
    SucceedWidget * success;
    FailWidget * fail;
    bool gameShown = 0;
};
#endif // WIDGET_H
