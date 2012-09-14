#include "filtros.h"

#include "QDebug"


#include "cv.h"
#include "highgui.h"

#include "qmath.h"

Filtros::Filtros()
{
}

// (CvMat) Converção RGB para GRAY usando a Media_RGB
Mat Filtros::RGBtoGRAY_CvMat_MediaRGB(Mat in_img)
{
    IplImage* out_img =new IplImage(in_img) ;
    CvScalar s;

    for(int i =0; i<out_img->height;i++)
    {
        for(int j=0;j<out_img->width;j++){

            s.val[0]=(cvGet2D(out_img,i,j).val[0]+(cvGet2D(out_img,i,j).val[1]+(cvGet2D(out_img,i,j).val[2])))/3;
            s.val[1]=s.val[0];
            s.val[2]=s.val[0];

            cvSet2D(out_img,i,j,s);
        }
    }
    return out_img;//out_img;
}

// (QImage) Binarização usando a Media_RGB

// (CvMat) Binarizaçao usando a Media_RGB
Mat Filtros::Binarizacao_CvMat_MediaRGB(Mat in_img,int nivel,bool bit=true)
{
    IplImage* out_img =new IplImage(RGBtoGRAY_CvMat_MediaRGB(in_img));
    CvScalar s;


    for(int i =0; i<out_img->height;i++)
    {
        for(int j=0;j<out_img->width;j++){

            if(cvGet2D(out_img,i,j).val[0]>=nivel)
            {

                if(bit ==true)
                {
                    s.val[0]=0;
                    s.val[1]=0;
                    s.val[2]=0;
                }
                else
                {
                    s.val[0]=255;
                    s.val[1]=255;
                    s.val[2]=255;
                }

                cvSet2D(out_img,i,j,s);
            }
            else
            {
                CvScalar s;
                if(bit ==true)
                {
                    s.val[0]=255;
                    s.val[1]=255;
                    s.val[2]=255;
                }
                else
                {
                    s.val[0]=0;
                    s.val[1]=0;
                    s.val[2]=0;
                }
                cvSet2D(out_img,i,j,s);
            }
        }
    }

    return out_img;
}



// (CvMat) Matriz de componente RGB da imagem
// Esta com um bug estranho <<===============
Mat Filtros::Matriz_CvMat_RGB(Mat in_img, char cor)
{
    IplImage* out_img =new IplImage(in_img);

    //qDebug()<<" "<<cvGet2D(out_img,0,0).val[0]<<" "<<cvGet2D(out_img,0,0).val[1]<<" "<<cvGet2D(out_img,0,0).val[2];

    CvScalar s;

    for(int i =0; i<out_img->height;i++)
    {
        for(int j=0;j<out_img->width;j++){

            if(cor=='R'||cor=='r')
            {
                s.val[0]=cvGet2D(out_img,i,j).val[0];
                s.val[1]=0;
                s.val[2]=0;
            }else
                if(cor=='G'||cor=='g')
                {
                    s.val[0]=0;
                    s.val[1]=cvGet2D(out_img,i,j).val[1];
                    s.val[2]=0;
                }else
                    if(cor=='B'||cor=='b')
                    {
                        s.val[0]=0;
                        s.val[1]=0;
                        s.val[2]=cvGet2D(out_img,i,j).val[2];
                    }
            cvSet2D(out_img,i,j,s);
        }
    }

    return out_img;
}

Mat Filtros::Zoon_IN_CvMat(Mat in_img, int x)
{


    IplImage* img =new IplImage(in_img);

    IplImage* out_img =cvCreateImage(cvSize(img->width*x,img->height*x),IPL_DEPTH_8U,3);

    CvScalar s;

    for(int i =0; i<out_img->height;i++)
    {
        for(int j=0;j<out_img->width;j++)
        {

           s=cvGet2D(img,(int)i/x,(int)j/x);

            cvSet2D(out_img,i,j,s);
        }
    }

 return out_img;
}

Mat Filtros::Zoon_OUT_CvMat(Mat in_img, int x)
{


    IplImage* img =new IplImage(in_img);

    IplImage* out_img =cvCreateImage(cvSize((int)(img->width/x),(int)(img->height/x)),IPL_DEPTH_8U,3);

    CvScalar s;

    for(int i =0; i<img->height-x+1;i=i+x)
    {
        for(int j=0;j<img->width-x+1;j=j+x)
        {

          s=cvGet2D(img,i,j);

           cvSet2D(out_img,(int)(i/x),(int)(j/x),s);
        }
    }

 return out_img;
}


Mat Filtros::Reduz_Vert_CvMat(Mat in_img, int x)
{
    IplImage* img =new IplImage(in_img);

    IplImage* out_img =cvCreateImage(cvSize(img->width,img->height/x),IPL_DEPTH_8U,3);

    CvScalar s;

    for(int i =0; i<img->height-x+1;i=i+x)
    {
        for(int j=0;j<img->width;j++)
        {

          s=cvGet2D(img,i,j);

           cvSet2D(out_img,i/x,j,s);
        }
    }

 return out_img;
}



Mat Filtros::Expand_Vert_CvMat(Mat in_img, int x)
{
    IplImage* img =new IplImage(in_img);

    IplImage* out_img =cvCreateImage(cvSize(img->width,img->height*x),IPL_DEPTH_8U,3);

    CvScalar s;

    for(int i =0; i<out_img->height;i++)
    {
        for(int j=0;j<out_img->width;j++)
        {

          s=cvGet2D(img,i/x,j);

           cvSet2D(out_img,i,j,s);
        }
    }

 return out_img;
}


Mat Filtros::Reduz_Hor_CvMat(Mat in_img, int x)
{
    IplImage* img =new IplImage(in_img);

    IplImage* out_img =cvCreateImage(cvSize(img->width/x,img->height),IPL_DEPTH_8U,3);

    CvScalar s;

    for(int i =0; i<img->height;i++)
    {
        for(int j=0;j<img->width-x+1;j=j+x)
        {

          s=cvGet2D(img,i,j);

           cvSet2D(out_img,i,j/x,s);
        }
    }

 return out_img;
}

Mat Filtros::Expand_Hor_CvMat(Mat in_img, int x)
{
    IplImage* img =new IplImage(in_img);

    IplImage* out_img =cvCreateImage(cvSize(img->width*x,img->height),IPL_DEPTH_8U,3);

    CvScalar s;

    for(int i =0; i<out_img->height;i++)
    {
        for(int j=0;j<out_img->width;j++)
        {

          s=cvGet2D(img,i,j/x);

           cvSet2D(out_img,i,j,s);
        }
    }

 return out_img;
}


//faser a subitracao de imagens


// fazer a rotacao no eixo e em um outo ponto qualquer

//representacoes de imagens:

// faser o filtro rgb para hsv e inversso

// faser o filtro rgb para HLS e inversso

// faser o filtro rgb para YUV e inversso

// faser o filtro rgb para XYZ e inversso

// faser o filtro rgb para YCrCb e inversso

// faser o filtro rgb para Lab e inversso

// faser o filtro rgb para Luv e inversso




//===================================================================
//===================================================================
//QImage Filtros::Mat2QImage(Mat img_in)
//{
//    QImage img_out( (uchar*)img_in.data, img_in.cols, img_in.rows, img_in.step,
//                    QImage::Format_RGB888 );
//    return img_out;
//}

//QImage Filtros::RGBtoGRAY_MediaRGB(QImage img_in)
//{
//    QImage img_out=img_in;

//    for(int i =0; i<img_out.height() ;i++)
//    {
//        for(int j=0;j<img_out.width() ;j++)
//        {

//            QRgb pixel = img_in.pixel(i,j);

//            int gray= (qRed(pixel)+qGreen(pixel)+qBlue(pixel))/3;

//            img_out.setPixel(i,j,qRgb(gray,gray,gray));
//        }
//    }
//    return img_out;
//}

//QImage Filtros::Binarizacao_MediaRGB(QImage img_in,int threshold,bool bit=true)
//{

//    QImage img_out=RGBtoGRAY_MediaRGB(img_in);


//    for(int i =0; i<img_out.height() ;i++)
//    {
//        for(int j=0;j<img_out.width() ;j++)
//        {
//            QRgb pixel = img_out.pixel(i,j);

//            if(qRed(pixel)>=threshold)
//            {

//                if(bit ==true)
//                {
//                    img_out.setPixel(i,j,qRgb(0,0,0));
//                }
//                else
//                {
//                    img_out.setPixel(i,j,qRgb(255,255,255));
//                }
//            }
//            else
//            {
//                if(bit ==true)
//                {
//                    img_out.setPixel(i,j,qRgb(255,255,255));
//                }
//                else
//                {
//                    img_out.setPixel(i,j,qRgb(0,0,0));
//                }
//            }
//        }
//    }

//    return img_out;
//}
//===============================================================



