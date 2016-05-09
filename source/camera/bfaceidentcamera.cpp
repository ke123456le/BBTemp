
#include "bfaceidentcamera.h"

#include <QDateTime>

#include <QDebug>

BFaceIdentCamera::BFaceIdentCamera() : dataBuffer(NULL),
    BUsbCamera(640, 480, 0x3610, 0x0ac8, QString("yuv"), I_FACE_VIDEO)
{

}

BFaceIdentCamera::~BFaceIdentCamera()
{

}


int BFaceIdentCamera::imageDataSize()
{
    return imageWidth ()*imageHeight ();
}


void BFaceIdentCamera::func()
{
    qDebug()<<__func__;
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

    CameraCtrl_t faceCtrl;
    faceCtrl._ctrlDirection = CTRL_OUT;
    faceCtrl._ctrlType      = CTRL_EXPOSURE;
    faceCtrl._ctrlValue     = 40;
    initCameraExposure (40);
    if (__BT_SUCC != control (faceCtrl)){
        qDebug()<<__func__<<"Face Control fail";
    }

    int len = 0;

    while (!QThread::currentThread ()->isInterruptionRequested ()){
        BT_RET ret = captureData (dataBuffer, &len);

        //qDebug()<<__func__<<"====>>"<<"len:"<<len<<"ret:"<<ret<<"DateTime:"<<
        //          QDateTime::currentDateTime ().toString ("yyyy-MM-dd hh:mm:ss.zzz");

        if (QThread::currentThread ()->isInterruptionRequested ())
            break;
        if (__BT_SUCC==ret && len>0){
            unsigned char * decodeData = dataBuffer + len;
            unsigned char * srcPtr = dataBuffer;
            unsigned char * dstPtr = decodeData;

            while (srcPtr < decodeData){
                *dstPtr++ = *srcPtr++;
                srcPtr++;
            }

            emit sendImageData (decodeData, iWidth*iHeight, iWidth, iHeight);

            if (showWidget){
                unsigned char * showData = decodeData + iWidth*iHeight;
                QSize _dstSize = showWidget->size ();
                procShowimage(QSize(iWidth, iHeight), decodeData, _dstSize, showData);

                QImage _image(showData, _dstSize.width (), _dstSize.height (),
                              QImage::Format_Grayscale8);

                //_image.save (QString("dgd------.jpg"));

                emit sendIamge (_image);
            }

            int expValue = 0;

            autoControlExp (decodeData, iWidth*iHeight, &expValue);
        }

        if (QThread::currentThread ()->isInterruptionRequested ())
            break;
        QThread::msleep (10);
    }

    qDebug()<<"BFaceIdentCamera============================ -*END*- =============================\n\n";
}
