#ifndef PRODUCEDBY_H
#define PRODUCEDBY_H

#include <QWidget>

namespace Ui {
class producedBy;
}

class producedBy : public QWidget
{
    Q_OBJECT

public:
    explicit producedBy(QWidget *parent = nullptr);
    ~producedBy();

private:
    Ui::producedBy *ui;

};

#endif // PRODUCEDBY_H
