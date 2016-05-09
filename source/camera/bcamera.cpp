#include "bcamera.h"
#include <QDebug>

#include "../common/bcommon.h"

BCamera::BCamera(): /*_cameraCtrl(NULL),func(NULL),*/
    _jpgDeCode(NULL),cameraState(NO_CAMERA),buffer(NULL),showWidget(0)
{
    yuvToRgb = new CYuvToRgb();

    QObject::connect (this, SIGNAL(sendIamge(QImage)), this,
                      SLOT(updateImage(QImage)),Qt::BlockingQueuedConnection);
    QObject::connect (this, SIGNAL(finished()), this, SLOT(releaseData()));
}

BT_RET BCamera::setDeCode(DeCode *_decode)
{
    if (_decode)
        _jpgDeCode = _decode;
    else
        return __BT_DATA_INVILD;

    return __BT_SUCC;
}


/*
BT_RET BCamera::setCameraCtrl(BCameraCtrlInterFace *_ctrl)
{
    if (_ctrl)
        _cameraCtrl = _ctrl;
    else
        return __BT_DATA_INVILD;

    return __BT_SUCC;
}


BT_RET BCamera::setCameraFunc(proFunc _func)
{
    if (_func)
        func = _func;
    else
        return __BT_DATA_INVILD;

    return __BT_SUCC;
}*/


BT_RET BCamera::updateCameraState(CameraState _state)
{
    cameraState = _state;

    //if (!isRunning ())
    //    start ();

    return __BT_SUCC;
}

/*
BT_RET BCamera::setCamera (BCameraInfo *_camera)
{
    if (_camera)
        camera = _camera;
    else
        return __BT_DATA_INVILD;

    return __BT_SUCC;
}
*/

BT_RET BCamera::setBuffer(unsigned char *_buf)
{
    if (_buf)
        buffer = _buf;
    else
        return __BT_DATA_INVILD;

    return __BT_SUCC;
}


BT_RET BCamera::startCamera()
{
    if (isRunning ()) {
        return __BT_CAMERA_BUSY;
    }else{
        start ();
    }

    return __BT_SUCC;
}

BT_RET BCamera::stopCamera()
{
    if (isRunning ()){
        requestInterruption ();
        //wait (50);
    }

    return __BT_SUCC;
}

BT_RET BCamera::setShowWidget(BCameraWidget *_showWidget)
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

BT_RET BCamera::procShowimage(QSize srcSize, unsigned char *srcData,
                       QSize dstSize, unsigned char *dstData)
{
    if (!srcData || !dstData)
        return __BT_DATA_INVILD;

    return BCommon::ImageResize(srcData, srcSize.height (), srcSize.width (),
                         dstData, dstSize.height (), dstSize.width ());
}




//------------------slot-----------

void BCamera::updateImage(const QImage _image)
{
    //qDebug()<<__func__<<"-----------------------------";
    if (showWidget){
        //QVideoFrame _myVideo(_image);
        showWidget->presentImage (_image, false);
    }
}


void BCamera::releaseData()
{
    showWidget = NULL;
    if (buffer){
        delete[] buffer;
    }
}




void BCamera::run()
{
    //if (_cameraCtrl){
        //qDebug()<<__func__<<"_cameraCtrl";
        if (NO_CAMERA == cameraState){
            //qDebug()<<__func__<<"openCamera";
            if (__BT_SUCC == openCamera ())
                updateCameraState(CAMERA_OPEN);
            //qDebug()<<__func__<<"openCamera==>>"<<"ret:"<<ret;
        }

        if (CAMERA_OPEN == cameraState){
            //qDebug()<<__func__<<"openCameraStream";

            if (__BT_SUCC == openCameraStream ()){
                updateCameraState(CAMERA_STREAM_ON);
            }
        }



        if (CAMERA_STREAM_ON == cameraState){
            func();
        }

        if (CAMERA_STREAM_ON == cameraState){
            //qDebug()<<__func__<<"closeCameraStream";
            if (__BT_SUCC == closeCameraStream ()){
                updateCameraState (CAMERA_OPEN);
            }
        }
    //}
}


void BCamera::doYuvToRgb(unsigned char *rgbPtr, unsigned char *yuvPtr,
                       int iWidth, int iHight)
{
    if (yuvToRgb)
        yuvToRgb->DoYUV (rgbPtr, yuvPtr, iWidth, iHight);
}
