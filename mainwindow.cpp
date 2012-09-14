#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialogde.h"

#include "stdio.h"

#include <vector>
#include <QString>
#include <QInputDialog>
#include <QLineEdit>

#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  , CameraAtiva(false)
{
    ui->setupUi(this);

    index=0;

    ui->ThresholdSpinBox->setEnabled( false );
    ui->fpsLabel->setText( "<i><b>Caregue uma Imagem.</b></i>" );

    Time.start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//===========================================================================

//posicao do mause na imagem
//void on_ImagemFrame_clicked(const QPoint &pos)
//{
// Px=pos.x();
// Py=pos.y();

// qDebug()<<"Px: "<<Px<<"Py: "<<Py;
//}

void MainWindow::on_LoadImageButton_clicked()
{
    ImagemOriginal.release(); // Reiniciando a Imagem

    // Caregando a Imagem Original
    bool ok;
    img_nome = QInputDialog::getText(this,
                                     "Carrega Imagem",
                                     "Imagem Path:",
                                     QLineEdit::Normal,
                                     "Imagens/lena.jpg",
                                     &ok);
    if(img_nome.size())
    {
        ImagemOriginal = imread( img_nome.toStdString().c_str() );
        cvtColor( ImagemOriginal, ImagemOriginal, CV_BGR2RGB);//organizando as matrizes (RGB)
        ImagemOriginal.copyTo(ImagemTemp);

        QImage tmp( (uchar*)ImagemTemp.data, ImagemTemp.cols, ImagemTemp.rows, ImagemTemp.step,
                    QImage::Format_RGB888 );

        ui->ImagemFrame->setPixmap( QPixmap::fromImage( tmp ) );
        ui->fpsLabel->setText( "<i><b>Imagem Caregada:</b> "+img_nome+"</i>");
    }
}

void MainWindow::on_FiltroButton_clicked()
{
    if( ImagemTemp.data )
    {
        FiltrosAplic_Cv();
    }
}

void MainWindow::on_CameraButton_clicked()
{
    if( !CameraAtiva )
    {
        Captura.open( CV_CAP_ANY );
        if( !Captura.isOpened() )
            return;

        bool res = Captura.set( CV_CAP_PROP_FRAME_WIDTH, 640.0 );
        res = Captura.set( CV_CAP_PROP_FRAME_HEIGHT, 480.0 );
        res = Captura.set( CV_CAP_PROP_FPS, 100.0 );

        CameraAtiva = true;

        CameraTimer.start( 20 ); // 50 fps (richiesti)
        connect( &CameraTimer, SIGNAL( timeout() ),
                 this, SLOT( on_CameraTimerTimeout() ) );

        ui->CameraButton->setText( "Parar Camera" );
        ui->LoadImageButton->setEnabled( false );
        ui->FiltroButton->setEnabled( false );
    }
    else
    {
        if( !Captura.isOpened() )
        {
            return;
        }

        CameraTimer.stop();

        Captura>>ImagemTemp;

        IplImage* img = new IplImage(ImagemTemp);
        cvSaveImage("Imagens/Teste00.bmp",img);

        Captura.release();

        CameraAtiva = false;
        ui->CameraButton->setText( "Ligar Camera" );
        ui->LoadImageButton->setEnabled( true );
        ui->FiltroButton->setEnabled( true );

        ImagemTemp.release();
        ImagemOriginal.release();

        ImagemOriginal = imread( "Imagens/Teste00.bmp");
        cvtColor( ImagemOriginal, ImagemOriginal, CV_BGR2RGB);
        ImagemOriginal.copyTo(ImagemTemp);
    }
}

void MainWindow::on_CameraTimerTimeout()
{
    if( CameraAtiva && Captura.isOpened() )
    {
        Captura >> ImagemOriginal; // Novo frame da camera
        cvtColor( ImagemOriginal, ImagemOriginal, CV_BGR2RGB);
        ImagemTemp = ImagemOriginal;

        // Calcula e exibe o FPS
        int time = Time.elapsed();
        Time.restart();
        FPS = (1.0/(double)time)*1000.0;
        QString str = QString( "<b>FPS:</b> %1" ).arg( FPS );
        ui->fpsLabel->setText( str );
        //--------------------------

        FiltrosAplic_Cv();//filtros e transformacoes sendo daaplicacao

        QImage tmp;

        tmp =QImage( (uchar*)ImagemTemp.data, ImagemTemp.cols, ImagemTemp.rows,
                     ImagemTemp.step,
                     QImage::Format_RGB888 );
        ui->ImagemFrame->setPixmap( QPixmap::fromImage( tmp ) );
    }
}


void MainWindow::on_FiltroComboBox_currentIndexChanged(int index)
{
    this->index=index;

    if(index==2)
    {
        ui->ThresholdSpinBox->setEnabled( true );
        ui->BitCheckBox->setEnabled(true);
        ui->Levellabel->setEnabled(true);
    }else
    {
        ui->ThresholdSpinBox->setEnabled( false );
        ui->BitCheckBox->setEnabled(false);
        ui->Levellabel->setEnabled(false);
    }

    if(index==3)
    {
        ui->RGBcomboBox->setEnabled( true );
    }else
    {
        ui->RGBcomboBox->setEnabled( false );
    }

    if(index==4 || index==5 || index==6 || index==7 || index==8 || index==9)
    {
     ui->ZOONspinBox->setEnabled(true);
     ui->Zoon_label->setEnabled(true);
    }else
    {
        ui->ZOONspinBox->setEnabled(false);
        ui->Zoon_label->setEnabled(false);
    }
}

void MainWindow::on_actionDistancia_Euclidiana_triggered()
{
    DialogDE *d=new DialogDE();
    d->show();
}


//=======================================================================================
void MainWindow::FiltrosAplic_Cv()
{
    QImage tmp;

    Filtros f;

    Mat ImagemTemp = this->ImagemTemp;
    IplImage* img;

    index = ui->FiltroComboBox->currentIndex();

    if(index==0)
    {
        if( CameraAtiva==false )
        {
            ImagemOriginal.copyTo(ImagemTemp);
        }
    }else
    if(index==1)
        {
        ImagemOriginal.copyTo(ImagemTemp);

        //Funcoes de RGBtoGRAY=========================================
        ImagemTemp=f.RGBtoGRAY_CvMat_MediaRGB(ImagemTemp);
        //=============================================================

     }else
    if(index==2)
    {
        int Threshold  = ui->ThresholdSpinBox->value();
        bool bit = ui->BitCheckBox->checkState();

        ImagemOriginal.copyTo(ImagemTemp);

        //Binarização=======================================
        ImagemTemp=f.Binarizacao_CvMat_MediaRGB(ImagemTemp,Threshold,bit);
        //=============================================================

       }else
    if(index==3)
    {
                ImagemOriginal.copyTo(ImagemTemp);

                //Matriz RGB=======================================
                ImagemTemp=f.Matriz_CvMat_RGB(ImagemTemp,ui->RGBcomboBox->currentText().toStdString().c_str()[0]);
                //=============================================================
    }else

        if(index==4)
        {
            if( CameraAtiva==false )
            {
                ImagemOriginal.copyTo(ImagemTemp);

                int zoon = ui->ZOONspinBox->value();

                ImagemTemp=f.Zoon_IN_CvMat(ImagemTemp,zoon);
            }
        }

    if(index==5)
    {
        if( CameraAtiva==false )
        {
            ImagemOriginal.copyTo(ImagemTemp);

            int zoon = ui->ZOONspinBox->value();

            ImagemTemp=f.Zoon_OUT_CvMat(ImagemTemp,zoon);

        }
    }

    if(index==6)
    {
        if( CameraAtiva==false )
        {
            ImagemOriginal.copyTo(ImagemTemp);

            int zoon = ui->ZOONspinBox->value();

            ImagemTemp=f.Reduz_Vert_CvMat(ImagemTemp,zoon);
        }
    }

    if(index==7)
    {
        if( CameraAtiva==false )
        {
            ImagemOriginal.copyTo(ImagemTemp);

            int zoon = ui->ZOONspinBox->value();

            ImagemTemp=f.Expand_Vert_CvMat(ImagemTemp,zoon);
        }
    }

    if(index==8)
    {
        if( CameraAtiva==false )
        {
            ImagemOriginal.copyTo(ImagemTemp);

            int zoon = ui->ZOONspinBox->value();

            ImagemTemp=f.Reduz_Hor_CvMat(ImagemTemp,zoon);
        }
    }

    if(index==9)
    {
        if( CameraAtiva==false )
        {
            ImagemOriginal.copyTo(ImagemTemp);

            int zoon = ui->ZOONspinBox->value();

            ImagemTemp=f.Expand_Hor_CvMat(ImagemTemp,zoon);
        }
    }


    cvtColor( ImagemTemp, ImagemTemp, CV_BGR2RGB);

    img = new IplImage(ImagemTemp);
    cvSaveImage("Imagens/Teste01.bmp",img);

    cvtColor( ImagemTemp, ImagemTemp, CV_BGR2RGB);

    tmp=QImage((uchar*)ImagemTemp.data, ImagemTemp.cols, ImagemTemp.rows,
               ImagemTemp.step, QImage::Format_RGB888 );
    ui->ImagemFrame->setPixmap( QPixmap::fromImage( tmp ) );
}

//========================================================================================
//void MainWindow::FiltrosAplic_Qt()
//{
//    index = ui->FiltroComboBox->currentIndex();

//    switch(index)
//    {
//    case 0:
//        ImagemTemp = filtro.Mat2QImage(ImagemOriginal);
//        break;

//    case 1:
//        ImagemTemp = filtro.RGBtoGRAY_MediaRGB(ImagemTemp);
//        break;

//    case 2:
//        int threshold  = ui->ThresholdSpinBox->value();
//        bool bit = ui->BitCheckBox->checkState();

//        ImagemTemp = filtro.Binarizacao_MediaRGB(ImagemTemp,threshold,bit);
//        break;

////    case 3:

////        break;

////    case 4:

////        break;


//    }

//    ui->ImagemFrame->setPixmap( QPixmap::fromImage( ImagemTemp ) );
//    ImagemTemp.save("Imagens/Teste01.bmp","BMP");

//    ImagemTemp= filtro.Mat2QImage(ImagemOriginal);
//}
//========================================================================================

