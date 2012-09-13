#-------------------------------------------------
#
# Project created by QtCreator 2012-08-19T21:32:44
#
#-------------------------------------------------

QT       += core gui

TARGET = Saulo_QtOpenCV
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filtros.cpp \
    dialogde.cpp \

HEADERS  += mainwindow.h \
    filtros.h \
    dialogde.h

FORMS    += mainwindow.ui \
    dialogde.ui


INCLUDEPATH += /usr/local/include/
INCLUDEPATH += /usr/local/include/opencv2/
INCLUDEPATH += /usr/local/include/opencv/

LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_features2d -lopencv_calib3d


unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

win32 {
        INCLUDEPATH += 	"../SupportLib/OpenCV_svn/modules/core/include/" \
                                        "../SupportLib/OpenCV_svn/modules/imgproc/include/" \
                                        "../SupportLib/OpenCV_svn/modules/highgui/include/"

        CONFIG(debug)
        {
                message(--- Debug configuration ---)
                LIBS += "../SupportLib/OpenCV_svn/Build_MinGW32/lib/libopencv_core211d.dll.a" \
                                "../SupportLib/OpenCV_svn/Build_MinGW32/lib/libopencv_imgproc211d.dll.a" \
                        "../SupportLib/OpenCV_svn/Build_MinGW32/lib/libopencv_highgui211d.dll.a"

                TARGET += debug
        }

        CONFIG(release)
        {
                message(--- Release configuration ---)
                LIBS += "../SupportLib/OpenCV_svn/Build_MinGW32/lib/libopencv_core211.dll.a" \
                                "../SupportLib/OpenCV_svn/Build_MinGW32/lib/libopencv_imgproc211.dll.a" \
                        "../SupportLib/OpenCV_svn/Build_MinGW32/lib/libopencv_highgui211.dll.a"

                TARGET += release
        }
}
