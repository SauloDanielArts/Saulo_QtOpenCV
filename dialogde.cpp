#include "dialogde.h"
#include "ui_dialogde.h"

#include "qmath.h"

#include "QString"

DialogDE::DialogDE(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDE)
{
    ui->setupUi(this);
}

DialogDE::~DialogDE()
{
    delete ui;
}

void DialogDE::DistEuclidiana()
{
    int x1=ui->X1spinBox->value();
    int y1=ui->Y1spinBox->value();
    int x2=ui->X2spinBox->value();
    int y2=ui->Y2spinBox->value();

    double r=(double)sqrt(pow(x1-x2,2)+pow(y1-y2,2));

    ui->DistanciaText->setText( QString::number(r));
}

void DialogDE::on_X1spinBox_valueChanged(int arg1)
{
DistEuclidiana();
}

void DialogDE::on_Y1spinBox_valueChanged(int arg1)
{
DistEuclidiana();
}

void DialogDE::on_X2spinBox_valueChanged(int arg1)
{
DistEuclidiana();
}

void DialogDE::on_Y2spinBox_valueChanged(int arg1)
{
DistEuclidiana();
}
