#ifndef FILTROS_H
#define FILTROS_H

#include <QImage>
#include <QTime>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Filtros
{
public:
    Filtros();

    //==================================================
//    QImage Mat2QImage(Mat img_in);
//    QImage RGBtoGRAY_MediaRGB(QImage img_in);
//    QImage Binarizacao_MediaRGB(QImage img_in,int threshold,bool bit);
    //==================================================

    Mat RGBtoGRAY_CvMat_MediaRGB(Mat in_img);
    Mat Binarizacao_CvMat_MediaRGB(Mat in_img,int nivel,bool bit);
    Mat Matriz_CvMat_RGB(Mat in_img, char cor);

    Mat Zoon_IN_CvMat(Mat in_img, int x);
    Mat Zoon_OUT_CvMat(Mat in_img, int x);
    Mat Reduz_Vert_CvMat(Mat in_img, int x);
    Mat Expand_Vert_CvMat(Mat in_img, int x);
    Mat Reduz_Hor_CvMat(Mat in_img, int x);
    Mat Expand_Hor_CvMat(Mat in_img, int x);
};

#endif // FILTROS_H
