#include "producedby.h"
#include "ui_producedby.h"

#include "macro.h"

producedBy::producedBy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::producedBy)
{
    ui->setupUi(this);
    setFixedSize(WID, HEI);

    ui->proBy->setGeometry(0, 0, WID, HEI);

    QFont font = ui->proBy->font();
    font.setPointSize(40);

    QPalette pal = ui->proBy->palette();
    pal.setColor(QPalette::Text, Qt::blue);

    ui->proBy->setFont(font);
    ui->proBy->setPalette(pal);

    ui->proBy->setFixedSize(this->width(), this->height());
    ui->proBy->setBackgroundVisible(1);


}

producedBy::~producedBy()
{
    delete ui;
}
