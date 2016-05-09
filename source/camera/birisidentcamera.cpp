#include "birisidentcamera.h"

#include <QFile>

#include <QDebug>
#include <QDateTime>

#include "../common/bcommon.h"





BIrisIdentCamera::BIrisIdentCamera() : jpegDeCode(NULL),dataBuffer(NULL),
    BUsbCamera(1920, 1080, 0x8455, 0x114d, QString("jpg"), I_IRIS_VIDEO)
{
    if (!jpegDeCode)
        jpegDeCode = new SoftDeCode();

    setDeCode (jpegDeCode);
}


BIrisIdentCamera::~BIrisIdentCamera()
{
    if (jpegDeCode)
        delete jpegDeCode;
}



int BIrisIdentCamera::imageDataSize()
{
    return imageWidth ()*imageHeight ();
}


/*
BT_RET BIrisIdentCamera::setShowWidget(BCameraWidget *_showWidget)
{
    if (!_showWidget)
        return __BT_DATA_INVILD;

    bool __is_running = false;
    if (isRunning ()){
        stopCamera ();
        __is_running = true;
    }

    showWidget = _showWidget;

    if (__is_running)
        startCamera ();

    return __BT_SUCC;
}
*/


void BIrisIdentCamera::func()
{
    //qDebug()<<"BIrisIdentCamera"<<__func__;

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

    CameraCtrl_t irisCtrl;
    irisCtrl._ctrlDirection = CTRL_OUT;
    irisCtrl._ctrlType      = CTRL_EXPOSURE;
    irisCtrl._ctrlValue     = 300;

    initCameraExposure (300);

    if (__BT_SUCC != control (irisCtrl)){
        qDebug()<<__func__<<"Iris Control fail";
    }

    int len = 0;

    while (!QThread::currentThread ()->isInterruptionRequested ()){
        //qDebug()<<"BIrisIdentCamera"<<__func__<<"count:"<<count;
        BT_RET ret = captureData (dataBuffer, &len);

        //qDebug()<<__func__<<"====>>"<<"len:"<<len<<"ret:"<<ret<<"DateTime:"<<
        //          QDateTime::currentDateTime ().toString ("yyyy-MM-dd hh:mm:ss.zzz");

        if (QThread::currentThread ()->isInterruptionRequested ())
            break;
        if (__BT_SUCC==ret && len>0){
            unsigned char * decodeData = dataBuffer + len;
            int codeLen = jpegDeCode->mJpgDeCode (dataBuffer, len, decodeData);
            if (codeLen > 0){
                /**/
                emit sendImageData(decodeData, codeLen, iWidth, iHeight);
                /**/
                if (showWidget){
                    unsigned char * showData = decodeData + codeLen;
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
        }
        if (QThread::currentThread ()->isInterruptionRequested ())
            break;
        QThread::msleep (10);
    }

    qDebug()<<"BIrisIdentCamera============================ -*END*- =============================\n\n";
}
