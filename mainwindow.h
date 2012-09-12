#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtGui/QDialog>
#include <QTimer>

#include <QImage>
#include <QTime>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <filtros.h>

using namespace cv;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:

    void FiltrosAplic_Cv();
    //void FiltrosAplic_Qt();
    //=============================

    void on_LoadImageButton_clicked();

    void on_FiltroButton_clicked();

    void on_CameraButton_clicked();
    void on_CameraTimerTimeout();
    void on_FiltroComboBox_currentIndexChanged(int index);

    void on_actionDistancia_Euclidiana_triggered();

private:
    Mat 			ImagemOriginal;
    Mat 			ImagemTemp;
    bool			CameraAtiva;

    VideoCapture                Captura;
    QTimer			CameraTimer;

    QTime			Time;
    double			FPS;

    int index;
    QString img_nome;

    int Px;
    int Py;

public slots:

signals:

};

#endif // MAINWINDOW_H
