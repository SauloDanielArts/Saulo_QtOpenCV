#ifndef DIALOGDE_H
#define DIALOGDE_H

#include <QDialog>

namespace Ui {
class DialogDE;
}

class DialogDE : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogDE(QWidget *parent = 0);
    ~DialogDE();
    
private slots:
    void on_X1spinBox_valueChanged(int arg1);
    void on_Y1spinBox_valueChanged(int arg1);
    void on_X2spinBox_valueChanged(int arg1);
    void on_Y2spinBox_valueChanged(int arg1);

private:
    Ui::DialogDE *ui;
    void DistEuclidiana();
};

#endif // DIALOGDH_H
