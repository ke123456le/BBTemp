#include <QDebug>

#include "bfaceshowcamera.h"
#include "../common/bcommon.h"

BFaceShowCamera::BFaceShowCamera() : dataBuffer(NULL),
  BCsiCamera("/dev/video0", 640, 480, QString("yuv"), V_FACE_VIDEO)
{

}


BFaceShowCamera::~BFaceShowCamera()
{
}


int BFaceShowCamera::imageDataSize()
{
    return imageWidth ()*imageHeight ();
}




void BFaceShowCamera::func()
{
    int iWidth = imageWidth ();
    int iHeight = imageHeight ();

    if (iWidth<=0 || iHeight<=0){
        sendFailureCode (__BT_CAMERA_INFO_FAIL);
        return;
    }

    if (dataBuffer) delete[] dataBuffer;
    dataBuffer = new unsigned char[iWidth*iHeight*5];
    if (!dataBuffer){
        sendFailureCode (__BT_ALLOC_BUF_FAIL);
        return;
    }
    memset(dataBuffer, 0, iWidth*iHeight*5);
    int len = 0;

    while (!QThread::currentThread ()->isInterruptionRequested ()){
        //qDebug()<<"BIrisIdentCamera"<<__func__<<"count:"<<count;
        BT_RET ret = captureData (dataBuffer, &len);

        //qDebug()<<__func__<<"====>>"<<"len:"<<len<<"ret:"<<ret<<"DateTime:"<<\
                  QDateTime::currentDateTime ().toString ("yyyy-MM-dd hh:mm:ss.zzz");

        if (QThread::currentThread ()->isInterruptionRequested ())
            break;
        if (__BT_SUCC==ret && len>0){
            unsigned char * rgbData = dataBuffer + len;

            doYuvToRgb (rgbData, dataBuffer, iWidth, iHeight);

            if (showWidget){
                QImage _image(rgbData, iWidth, iHeight,
                              QImage::Format_RGB888);

                emit sendIamge (_image);
            }

        }

        QThread::msleep (10);
    }

    qDebug()<<"BFaceShowCamera============================ -*END*- =============================\n\n";
}



