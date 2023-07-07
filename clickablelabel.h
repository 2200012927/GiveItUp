#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>

class clickableLabel : public QLabel
{
    Q_OBJECT
public:
    clickableLabel(QWidget *parent = nullptr);
    static bool soundS;
    static bool musicS;

protected:
    void mousePressEvent(QMouseEvent *me);

signals:
    void clicked();
};



#endif // CLICKABLELABEL_H
